#include "filter.hpp"

namespace xios
{
  CFilter::CFilter(CGarbageCollector& gc, size_t inputSlotsCount, IFilterEngine* engine)
    : CInputPin(gc, inputSlotsCount)
    , COutputPin(gc, false)
    , engine(engine)
    , inputSlotCount(inputSlotCount)
  { /* Nothing to do */ }

  StdString CFilter::GetName(void)    { return StdString("Filter"); }

  void CFilter::onInputReady(std::vector<CDataPacketPtr> data)
  {
    CDataPacketPtr outputPacket = engine->apply(data);
    if (outputPacket)
      onOutputReady(outputPacket);
  }

  void CFilter::setInputTrigger(size_t inputSlot, COutputPin* trigger)
  {
    // Was the filter already triggerable? If not, we need to inform
    // all downstream filters.
    bool wasTriggerable = canBeTriggered();

    CInputPin::setInputTrigger(inputSlot, trigger);

    if (!wasTriggerable)
      setOutputTriggers();
  }

  void CFilter::trigger(Time timestamp)
  {
    CInputPin::trigger(timestamp);

    COutputPin::trigger(timestamp);
  }

  bool CFilter::canBeTriggered() const
  {
    return (CInputPin::canBeTriggered() || COutputPin::canBeTriggered());
  }

  bool CFilter::mustAutoTrigger() const
  {
    return COutputPin::mustAutoTrigger();
  }

  bool CFilter::isDataExpected(const CDate& date) const
  {
    return COutputPin::isDataExpected(date);
  }
} // namespace xios
