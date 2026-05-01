#include "file_writer_filter.hpp"
#include "exception.hpp"
#include "field.hpp"
#include "utils.hpp"
#include "workflow_graph.hpp"
#include "graphviz.hpp"

namespace xios
{
  CFileWriterFilter::CFileWriterFilter(CGarbageCollector& gc, CField* field)
    : CInputPin(gc, 1)
    , field(field)
  {
    if (!field)
      ERROR("CFileWriterFilter::CFileWriterFilter(CField* field)",
            "The field cannot be null.");
  }

  void CFileWriterFilter::buildGraph(std::vector<CDataPacketPtr> data)
  {
    bool building_graph = this->tag ? data[0]->timestamp >= this->start_graph && data[0]->timestamp <= this->end_graph: false;
    
    if(building_graph)
    {
      this->filterID = InvalidableObject::filterIdGenerator++;
      int edgeID = InvalidableObject::edgeIdGenerator++;

      CWorkflowGraph::allocNodeEdge();
      StdString namestring = to_string(this->field->name);
      namestring.erase(0, 6);
      namestring.erase(namestring.length()-1, 1);
      
      CWorkflowGraph::addNode(this->filterID, namestring + "\\n(file ID : "+this->field->file->getId()+")", 6, 0, 1, data[0]);

      (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].attributes = this->field->record4graphXiosAttributes();
      (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].attributes += "</br>file attributes : </br>" +this->field->file->record4graphXiosAttributes();
      (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].clusterID =1;
      (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].distance = data[0]->distance+1;

      if(CXios::isClient && CWorkflowGraph::build_begin) 
      {

        CWorkflowGraph::addEdge(edgeID, this->filterID, data[0]);

        (*CWorkflowGraph::mapFilters_ptr_with_info)[data[0]->src_filterID].filter_filled = 0 ;
      }
      else CWorkflowGraph::build_begin=true;
    }
  }

  void CFileWriterFilter::onInputReady(std::vector<CDataPacketPtr> data)
  {
    buildGraph(data);
    
    const bool detectMissingValue = ( !field->default_value.isEmpty() &&
                               ( (!field->detect_missing_value.isEmpty() || field->detect_missing_value == true)
                                 || field->hasGridMask()) );

    CArray<double, 1> dataArray = (detectMissingValue) ? data[0]->data.copy() : data[0]->data;

    if (detectMissingValue)
    {
      const double missingValue = field->default_value;
      const size_t nbData = dataArray.numElements();
      for (size_t idx = 0; idx < nbData; ++idx)
      {
        if (NumTraits<double>::isNan(dataArray(idx)))
          dataArray(idx) = missingValue;
      }
    }

    field->sendUpdateData(dataArray);
  }

  bool CFileWriterFilter::mustAutoTrigger() const
  {
    return true;
  }

  bool CFileWriterFilter::isDataExpected(const CDate& date) const
  {
    return true;
  }
} // namespace xios
