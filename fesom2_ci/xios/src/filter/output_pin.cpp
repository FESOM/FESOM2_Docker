#include "output_pin.hpp"
#include "exception.hpp"
#include "workflow_graph.hpp"

namespace xios
{
  COutputPin::COutputPin(CGarbageCollector& gc, bool manualTrigger /*= false*/)
    : gc(gc)
    , manualTrigger(manualTrigger)
  {  }

  StdString COutputPin::GetName(void)
  {
    return StdString("Output pin");
  }

  void COutputPin::connectOutput(std::shared_ptr<CInputPin> inputPin, size_t inputSlot)
  {
    if (!inputPin)
      ERROR("void COutputPin::connectOutput(CInputPin* inputPin, size_t inputSlot)",
            "The input pin cannot be null.");

    outputs.push_back(std::make_pair(inputPin, inputSlot));

    if (canBeTriggered())
      inputPin->setInputTrigger(inputSlot, this);
  }

  void COutputPin::onOutputReady(CDataPacketPtr packet)
  {
    if (!packet)
      ERROR("void COutputPin::onOutputReady(CDataPacketPtr packet)",
            "The packet cannot be null.");

    if (manualTrigger) // Don't use canBeTriggered here, this function is virtual and can be overriden
    {
      outputPackets[packet->timestamp] = packet;
      gc.registerObject(this, packet->timestamp);
    }
    else
      deliverOuput(packet);
  }

  void COutputPin::deliverOuput(CDataPacketPtr packet)
  {
    if (!packet)
      ERROR("void COutputPin::deliverOuput(CDataPacketPtr packet)",
            "The packet cannot be null.");

    std::vector<std::pair<std::shared_ptr<CInputPin>, size_t> >::iterator it, itEnd;
    for (it = outputs.begin(), itEnd = outputs.end(); it != itEnd; ++it)
      it->first->setInput(it->second, packet);
  }

  void COutputPin::trigger(Time timestamp)
  {
    if (manualTrigger) // Don't use canBeTriggered here, this function is virtual and can be overriden
    {
      std::map<Time, CDataPacketPtr>::iterator it = outputPackets.find(timestamp);
      if (it != outputPackets.end())
      {
        gc.unregisterObject(this, timestamp);
        deliverOuput(it->second);
        outputPackets.erase(it);
      }
    }
  }

  bool COutputPin::canBeTriggered() const
  {
    return manualTrigger;
  }

  bool COutputPin::mustAutoTrigger() const
  {
    std::vector<std::pair<std::shared_ptr<CInputPin>, size_t> >::const_iterator it, itEnd;
    for (it = outputs.begin(), itEnd = outputs.end(); it != itEnd; ++it)
    {
      if (it->first->mustAutoTrigger())
        return true;
    }

    return false;
  }

  void COutputPin::setOutputTriggers()
  {
    std::vector<std::pair<std::shared_ptr<CInputPin>, size_t> >::iterator it, itEnd;
    for (it = outputs.begin(), itEnd = outputs.end(); it != itEnd; ++it)
      it->first->setInputTrigger(it->second, this);
  }

  bool COutputPin::isDataExpected(const CDate& date) const
  {
    std::vector<std::pair<std::shared_ptr<CInputPin>, size_t> >::const_iterator it, itEnd;
    for (it = outputs.begin(), itEnd = outputs.end(); it != itEnd; ++it)
    {
      if (it->first->isDataExpected(date))
        return true;
    }

    return false;
  }

  void COutputPin::invalidate(Time timestamp)
  {
    outputPackets.erase(outputPackets.begin(), outputPackets.lower_bound(timestamp));
  }

  void COutputPin::setParentFiltersTag()
  {
    for(int i=0; i<parent_filters.size(); i++)
    {

      if(parent_filters[i]->start_graph<0) parent_filters[i]->start_graph = start_graph;
      else parent_filters[i]->start_graph = min(parent_filters[i]->start_graph, start_graph);


      if(parent_filters[i]->end_graph<0) parent_filters[i]->end_graph = end_graph;  
      else parent_filters[i]->end_graph = max(parent_filters[i]->end_graph, end_graph);
      
      
      parent_filters[i]->tag += tag;
      parent_filters[i]->setParentFiltersTag();
    }
  }




} // namespace xios
