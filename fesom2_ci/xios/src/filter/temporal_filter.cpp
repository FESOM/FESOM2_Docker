#include "temporal_filter.hpp"
#include "functor_type.hpp"
#include "calendar_util.hpp"
#include "workflow_graph.hpp"
#include "file.hpp"
#include "timer.hpp"

namespace xios
{
  // Per-rank aggregates. Cheap integer adds in the steady-state path; values
  // only emitted to the log at level >100, so they are silent in production.
  long CTemporalFilter::totalInstances           = 0;
  long CTemporalFilter::totalApplyCalls          = 0;
  long CTemporalFilter::totalSingleSampleWindows = 0;
  long CTemporalFilter::totalMultiSampleWindows  = 0;
  // Debug-only aggregates. Populated only when log level >100.
  double CTemporalFilter::totalSingleSampleFunctorTime = 0.0;
  double CTemporalFilter::totalMultiSampleFunctorTime  = 0.0;
  long   CTemporalFilter::totalIdenticalSamples        = 0;
  long   CTemporalFilter::totalDifferingSamples        = 0;
  long   CTemporalFilter::totalConstantValueWindows    = 0;
  long   CTemporalFilter::totalNonConstantWindows      = 0;

  static func::CFunctor* createFunctor(const std::string& opId, bool ignoreMissingValue, CArray<double, 1>& tmpData);

  CTemporalFilter::CTemporalFilter(CGarbageCollector& gc, const std::string& opId,
                                   const CDate& initDate, const CDuration samplingFreq, const CDuration samplingOffset, const CDuration opFreq,
                                   bool ignoreMissingValue /*= false*/)
    : CFilter(gc, 1, this)
    , functor(createFunctor(opId, ignoreMissingValue, tmpData))
    , isOnceOperation(functor->timeType() == func::CFunctor::once)
    , isInstantOperation(functor->timeType() == func::CFunctor::instant)
    , samplingFreq(samplingFreq)
    , samplingOffset(samplingOffset)
    , opFreq(opFreq)
    , offsetMonth(0, this->samplingOffset.month, 0, 0, 0, 0, 0)
    , offsetAllButMonth(this->samplingOffset.year, 0 , this->samplingOffset.day,
                        this->samplingOffset.hour, this->samplingOffset.minute,
                        this->samplingOffset.second, this->samplingOffset.timestep)
    , initDate(initDate)
    , nextSamplingDate(initDate + offsetMonth + ( offsetAllButMonth + initDate.getRelCalendar().getTimeStep()))
    , nbOperationDates(1)
    , nbSamplingDates(0)
//    , nextOperationDate(initDate + opFreq + this->samplingOffset)
    , isFirstOperation(true)
    , samplesInCurrentWindow_(0)
    , functorTimeInCurrentWindow_(0.0)
    , hasPreviousData_(false)
    , identicalSamplesInWindow_(0)
    , differingSamplesInWindow_(0)
    , temp_op(opId)
  {
    totalInstances += 1;
  }

  // Per-rank temporal-filter window classification, emitted only at log
  // level >100 to keep production logs clean.
  void CTemporalFilter::reportWindowStats()
  {
    report(100) << " Performance report : Temporal filter window classification :"
                << " single-sample windows = " << totalSingleSampleWindows
                << " (functor time " << totalSingleSampleFunctorTime << " s),"
                << " multi-sample windows = "  << totalMultiSampleWindows
                << " (functor time " << totalMultiSampleFunctorTime  << " s)" << endl;
    report(100) << " Performance report : Temporal filter sample-equality :"
                << " identical-to-previous samples = " << totalIdenticalSamples
                << ", differing samples = "            << totalDifferingSamples
                << ", constant-value windows = "       << totalConstantValueWindows
                << ", non-constant windows = "         << totalNonConstantWindows << endl;
    report(100) << " Performance report : Temporal filter instances on this rank = "
                << totalInstances
                << ", total apply() calls (non-EOS) = " << totalApplyCalls << endl;
  }

  



  bool CTemporalFilter::buildGraph(std::vector<CDataPacketPtr> data)
  {
    bool building_graph=this->tag ? data[0]->timestamp >= this->start_graph && data[0]->timestamp <= this->end_graph : false;
   
    if(building_graph)
    {
      if(this->filterIDoutputs.size()==0) this->filterID = InvalidableObject::filterIdGenerator++;
      int edgeID = InvalidableObject::edgeIdGenerator++;
      
      // std::cout<<"CTemporalFilter::apply filter tag = "<<this->tag<<" start = "<<this->start_graph<<" end = "<<this->end_graph<<std::endl;

      CWorkflowGraph::allocNodeEdge();

      if(this->filterIDoutputs.size()==0)
      {
        CWorkflowGraph::addNode(this->filterID, "Temporal Filter\\n("+this->temp_op+")", 5, 1, 0, data[0]);   
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].transform_type = this->temp_op;   
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].inputs_complete = false ;
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].clusterID = 1 ;
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].distance = (data[0]->distance);


        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].attributes = this->field->record4graphXiosAttributes();
        if(this->field->file) (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].attributes += "</br>file attributes : </br>" +this->field->file->record4graphXiosAttributes();
      }

      if(CWorkflowGraph::build_begin)
      {

        CWorkflowGraph::addEdge(edgeID, this->filterID, data[0]);

        (*CWorkflowGraph::mapFilters_ptr_with_info)[data[0]->src_filterID].filter_filled = 0 ;
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].expected_entry_nb += 1 ;
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].distance = max(data[0]->distance+1, (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].distance);
      }


      this->filterIDoutputs.push_back(data[0]->src_filterID); 
    }

    return building_graph;
  }


  CDataPacketPtr CTemporalFilter::apply(std::vector<CDataPacketPtr> data)
  {
    CTimer::get("Temporal filter : apply").resume();
    bool BG = buildGraph(data);

    CDataPacketPtr packet=0;

    if (data[0]->status != CDataPacket::END_OF_STREAM)
    {
      totalApplyCalls += 1;
      bool usePacket, outputResult, copyLess;
      if (isOnceOperation)
        usePacket = outputResult = copyLess = isFirstOperation;
      else
      {
        usePacket = (data[0]->date >= nextSamplingDate);
        outputResult = (data[0]->date  > initDate + nbOperationDates*opFreq - samplingFreq + offsetMonth + offsetAllButMonth);
        copyLess = (isInstantOperation && usePacket && outputResult);
      }

      if (usePacket)
      {
        nbSamplingDates ++;
        samplesInCurrentWindow_ ++;
        if (!copyLess)
        {
          if (!tmpData.numElements())
            tmpData.resize(data[0]->data.numElements());

          // Debug: byte-compare current input to previous to detect
          // identical-value resamples (held-buffer pattern). O(N) per call.
          if (info.getLevel() > 100)
          {
            const int n = data[0]->data.numElements();
            bool isIdentical = false;
            if (hasPreviousData_ && previousData_.numElements() == n)
            {
              isIdentical = true;
              const double* a = previousData_.dataFirst();
              const double* b = data[0]->data.dataFirst();
              for (int i = 0; i < n; ++i)
              {
                if (a[i] != b[i]) { isIdentical = false; break; }
              }
            }
            if (isIdentical) identicalSamplesInWindow_ += 1;
            else             differingSamplesInWindow_ += 1;
            if (!isIdentical)
            {
              if (previousData_.numElements() != n) previousData_.resize(n);
              previousData_ = data[0]->data;
              hasPreviousData_ = true;
            }
          }

          CTimer::get("Temporal filter : functor").resume();
          if (info.getLevel() > 100)
          {
            const double t0 = CTimer::getTime();
            (*functor)(data[0]->data);
            functorTimeInCurrentWindow_ += (CTimer::getTime() - t0);
          }
          else
          {
            (*functor)(data[0]->data);
          }
          CTimer::get("Temporal filter : functor").suspend();
        }

        nextSamplingDate = ((initDate + offsetMonth) + nbSamplingDates * samplingFreq) + offsetAllButMonth + initDate.getRelCalendar().getTimeStep();
      }

      if (outputResult)
      {
        // Classify the just-closed window. Cheap counters; useful for
        // diagnosing whether XIOS-side averaging is actually doing real
        // work (multi-sample) or reducing to identity (single-sample).
        const int closedWindowSamples = samplesInCurrentWindow_;
        if      (closedWindowSamples == 1) totalSingleSampleWindows += 1;
        else if (closedWindowSamples >  1) totalMultiSampleWindows  += 1;
        samplesInCurrentWindow_ = 0;

        // Debug-only: roll up sample-equality counts into the per-window
        // classification (constant-value vs non-constant) and the running
        // functor-time totals.
        if (info.getLevel() > 100)
        {
          if      (closedWindowSamples == 1) totalSingleSampleFunctorTime += functorTimeInCurrentWindow_;
          else if (closedWindowSamples >  1) totalMultiSampleFunctorTime  += functorTimeInCurrentWindow_;
          totalIdenticalSamples += identicalSamplesInWindow_;
          totalDifferingSamples += differingSamplesInWindow_;
          if (differingSamplesInWindow_ == 1 && identicalSamplesInWindow_ >= 1)
            totalConstantValueWindows += 1;
          else if (differingSamplesInWindow_ >= 2)
            totalNonConstantWindows   += 1;
          identicalSamplesInWindow_   = 0;
          differingSamplesInWindow_   = 0;
          hasPreviousData_            = false;
          functorTimeInCurrentWindow_ = 0.0;
        }

        nbOperationDates ++;
        if (!copyLess)
        {
          functor->final();

          packet = CDataPacketPtr(new CDataPacket);
          packet->date = data[0]->date;
          packet->timestamp = data[0]->timestamp;
          packet->status = data[0]->status;
          packet->data.resize(tmpData.numElements());
          packet->data = tmpData;
        }
        else
          packet = data[0];

        isFirstOperation = false;
        
        packet->field = this->field;
        
        if(BG)
        {
          packet->src_filterID=this->filterID;
          packet->distance = data[0]->distance+1;
          this->filterIDoutputs.clear();
          CWorkflowGraph::build_begin=true;
          (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].inputs_complete = true ;
        }
      }
    }

    CTimer::get("Temporal filter : apply").suspend();
    return packet;
  }

  bool CTemporalFilter::mustAutoTrigger() const
  {
    return true;
  }

  bool CTemporalFilter::isDataExpected(const CDate& date) const
  {
//    return isOnceOperation ? isFirstOperation : (date >= nextSamplingDate || date + samplingFreq > nextOperationDate);
    return isOnceOperation ? isFirstOperation : (date >= nextSamplingDate || date > initDate + nbOperationDates*opFreq - samplingFreq + offsetMonth + offsetAllButMonth);
  }

  static func::CFunctor* createFunctor(const std::string& opId, bool ignoreMissingValue, CArray<double, 1>& tmpData)
  {
    func::CFunctor* functor = NULL;

    double defaultValue = std::numeric_limits<double>::quiet_NaN();

#define DECLARE_FUNCTOR(MType, mtype) \
    if (opId.compare(#mtype) == 0) \
    { \
      if (ignoreMissingValue) \
      { \
        functor = new func::C##MType(tmpData, defaultValue); \
      } \
      else \
      { \
        functor = new func::C##MType(tmpData); \
      } \
    }

#include "functor_type.conf"

    if (!functor)
      ERROR("createFunctor(const std::string& opId, ...)",
            << "\"" << opId << "\" is not a valid operation.");

    return functor;
  }
} // namespace xios
