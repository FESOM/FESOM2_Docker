#ifndef __XIOS_CFilter__
#define __XIOS_CFilter__

#include "input_pin.hpp"
#include "output_pin.hpp"
#include "filter_engine.hpp"

namespace xios
{
  /*!
   * A generic filter with an input pin and an output pin.
   * A filter can delegate the internal work to an engine
   * which may be shared by multiple filter instances.
   */
  class CFilter : public CInputPin, public COutputPin
  {
    public:
      /*!
       * Constructs a filter with the specified number of input slots
       * and the specified engine.
       *
       * \param gc the associated garbage collector
       * \param inputSlotsCount the number of input slots
       * \param engine the filter engine
       */
      CFilter(CGarbageCollector& gc, size_t inputSlotsCount, IFilterEngine* engine);

      StdString virtual GetName(void);

      /*!
       * Sets the trigger for a specific input slot.
       *
       * \param inputSlot the input slot number
       * \param trigger the corresponding trigger
       */
      void virtual setInputTrigger(size_t inputSlot, COutputPin* trigger);

      /*!
       * Triggers the filter for the specified timestamp.
       *
       * \param timestamp the timestamp for which we are triggering the filter
       */
      void virtual trigger(Time timestamp);

      /*!
       * Tests if the filter can be triggered.
       *
       * \return true if the filter can be triggered
       */
      bool virtual canBeTriggered() const;

      /*!
       * Tests if the filter must auto-trigger.
       *
       * \return true if the filter must auto-trigger
       */
      bool virtual mustAutoTrigger() const;

      /*!
       * Tests whether data is expected for the specified date.
       *
       * \param date the date associated to the data
       */
      bool virtual isDataExpected(const CDate& date) const;

      
      

      int filterID;
      StdString expression;

    protected:
      IFilterEngine* engine; //!< The filter engine, might be the filter itself
      size_t inputSlotCount; //!< Number of slot on filter

      /*!
       * Generic implementation of the input pin notification function, processes
       * the data using the filter engine and passes the resulting packet (if any)
       * to the downstreams filters.
       *
       * \param data a vector of packets corresponding to each slot
       */
      void virtual onInputReady(std::vector<CDataPacketPtr> data);
  }; // class CFilter
} // namespace xios

#endif //__XIOS_CFilter__
