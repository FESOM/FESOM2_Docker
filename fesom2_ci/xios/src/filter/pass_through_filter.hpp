#ifndef __XIOS_CPassThroughFilter__
#define __XIOS_CPassThroughFilter__

#include "filter.hpp"

namespace xios
{
  /*!
   * A simple pass-through filter with one input slot.
   * The pass-through filter is used to handle references on a field.
   */
  class CPassThroughFilter : public CFilter, public IFilterEngine
  {
    public:
      /*!
       * Constructs a pass-through filter with the one input slot.
       *
       * \param gc the associated garbage collector
       */
      CPassThroughFilter(CGarbageCollector& gc);

      inline StdString GetName(void) {return StdString("Pass through filter");};

    protected:
      /*!
       * Returns the input packet without making any modification to it.
       *
       * \param data a vector of packets corresponding to each slot
       * \return the untouched source data packet
       */
      CDataPacketPtr virtual apply(std::vector<CDataPacketPtr> data);
      void virtual buildGraph(std::vector<CDataPacketPtr> data);
  }; // class CPassThroughFilter
} // namespace xios

#endif //__XIOS_CPassThroughFilter__
