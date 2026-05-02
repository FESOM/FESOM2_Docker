#ifndef __XIOS_IFilterEngine__
#define __XIOS_IFilterEngine__

#include "data_packet.hpp"

namespace xios
{
  /*!
   * An engine filter processes the data handled by a filter.
   */
  class IFilterEngine
  {
    public:
      /*!
       * Processes the data and returns a new packet if needed.
       * Temporal filter engines will not return a new packet
       * for every call being that they accumulate data.
       * The filter engine is not allowed to modify the data
       * in place.
       *
       * \param data a vector of packets corresponding to each slot
       * \return a new data packet or null if the engine is accumulating data
       */
       CDataPacketPtr virtual apply(std::vector<CDataPacketPtr> data) = 0;
  }; // class IFilterEngine
} // namespace xios

#endif //__XIOS_IFilterEngine__
