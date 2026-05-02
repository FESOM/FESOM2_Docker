#ifndef __XIOS_CSourceFilter__
#define __XIOS_CSourceFilter__

#include <map>

#include "output_pin.hpp"

namespace xios
{
  class CGrid;

  /*!
   * A source filter is the entry point of the data in the graph of filters.
   */
  class CSourceFilter : public COutputPin
  {
    public:
      /*!
       * Constructs a source filter accepting data attached to the specified grid.
       *
       * \param gc the garbage collector associated with this filter
       * \param grid the grid to which the data is attached
       * \param compression
       * \param mask
       * \param offset the offset applied to the timestamp of all packets
       * \param manualTrigger whether the output should be triggered manually
       * \param hasMissingValue whether data has missing value
       * \param defaultValue missing value to detect
       */
      CSourceFilter(CGarbageCollector& gc, CGrid* grid,
                    bool compression = true,
                    bool mask = false,
                    const CDuration offset = NoneDu, bool manualTrigger = false,
                    bool hasMissingValue = false,
                    double defaultValue = 0.0);

      inline StdString GetName(void) {return StdString("Source filter");};

      /*!
       * Transforms the data received from the model into a packet and send it
       * in the filter graph. The array containing the data can safely be reused
       * immediately after this method returns.
       *
       * \param date the date associated to the data
       * \param data an array containing the data
       */
      template <int N>
      void streamData(CDate date, const CArray<double, N>& data, bool isTiled = false);

      template <int N>
      void streamTile(CDate date, const CArray<double, N>& data, int ntile);

      void virtual buildGraph(CDataPacketPtr packet);

      /*!
       * Transforms the data received from the server into a packet and send it
       * in the filter graph. The array containing the data can safely be reused
       * immediately after this method returns.
       *
       * \param date the date associated to the data
       * \param data an array containing the data
       */
      void streamDataFromServer(CDate date, const std::map<int, CArray<double, 1> >& data);

      /*!
       * Signals the filter graph that the end of stream was reached.
       *
       * \param date the date at which the end of stream occurred
       */
      void signalEndOfStream(CDate date);
      int filterID;

    private:
      CGrid* grid;             //!< The grid attached to the data the filter can accept
      const CDuration offset;  //!< The offset applied to the timestamp of all packets
      const bool hasMissingValue;
      const double defaultValue;
      const bool compression ; //!< indicates if data need to be compressed : on client side : true, on server side : false
      const bool mask ;        //!< indicates whether grid mask should be applied (true for clients, false for servers)
      int ntiles ;
      CArray<double, 1> storedTileData;

    public:
      // Per-rank aggregates. Cheap integer adds; reported only at log level >100.
      static long totalSourceFilterInstances; //!< # of CSourceFilter constructed on this rank
      static long totalStreamDataCalls;       //!< # of streamData() invocations on this rank
      static void reportInstanceStats();
  }; // class CSourceFilter
} // namespace xios

#endif //__XIOS_CSourceFilter__
