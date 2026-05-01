#include "input_pin.hpp"
#include "output_pin.hpp"
#include "garbage_collector.hpp"
#include "exception.hpp"
#include "workflow_graph.hpp"

namespace xios
{
  CInputPin::CInputPin(CGarbageCollector& gc, size_t slotsCount)
    : gc(gc)
    , slotsCount(slotsCount)
    , triggers(slotsCount)
    , hasTriggers(false)
  {  }

  StdString CInputPin::GetName(void)
  {
    return StdString("Input pin");
  }

  void CInputPin::setInput(size_t inputSlot, CDataPacketPtr packet)
  {
    if (inputSlot >= slotsCount)
      ERROR("void CInputPin::setInput(size_t inputSlot, CDataPacketPtr packet)",
            "The input slot " << inputSlot << " does not exist.");
    if (!packet)
      ERROR("void CInputPin::setInput(size_t inputSlot, CDataPacketPtr packet)",
            "The packet cannot be null.");

    std::map<Time, InputBuffer>::iterator it = inputs.find(packet->timestamp);
    if (it == inputs.end())
    {
      it = inputs.insert(std::make_pair(packet->timestamp, InputBuffer(slotsCount))).first;
      gc.registerObject(this, packet->timestamp);
    }
    it->second.slotsFilled++;
    it->second.packets[inputSlot] = packet;

    if (it->second.slotsFilled == slotsCount)
    {
      // Unregister before calling onInputReady in case the filter registers again
      gc.unregisterObject(this, packet->timestamp);
      onInputReady(it->second.packets);
      inputs.erase(it);
    }
  }

  void CInputPin::setInputTrigger(size_t inputSlot, COutputPin* trigger)
  {
    if (inputSlot >= slotsCount)
      ERROR("void CInputPin::setInputTrigger(size_t inputSlot, COutputPin* trigger)",
            "The input slot " << inputSlot << " does not exist.");
    if (triggers[inputSlot])
      ERROR("void CInputPin::setInputTrigger(size_t inputSlot, COutputPin* trigger)",
            "The trigger for input slot " << inputSlot << " has already been set.");

    triggers[inputSlot] = trigger;
    hasTriggers = true;
  }

  void CInputPin::trigger(Time timestamp)
  {
    if (hasTriggers) // Don't use canBeTriggered here, this function is virtual and can be overriden
    {
      std::map<Time, InputBuffer>::iterator it = inputs.find(timestamp);
      bool nothingReceived = (it == inputs.end());

      for (size_t s = 0; s < slotsCount; s++)
      {
        if (triggers[s] && (nothingReceived || !it->second.packets[s]))
          triggers[s]->trigger(timestamp);
      }
    }
  }

  bool CInputPin::canBeTriggered() const
  {
    return hasTriggers;
  }

  void CInputPin::invalidate(Time timestamp)
  {
    inputs.erase(inputs.begin(), inputs.lower_bound(timestamp));
  }
} // namespace xios
