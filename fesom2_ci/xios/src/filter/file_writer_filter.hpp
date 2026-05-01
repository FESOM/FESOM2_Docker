#ifndef __XIOS_CFileWriterFilter__
#define __XIOS_CFileWriterFilter__

#include "input_pin.hpp"
#include "file.hpp"
#include "duration.hpp"

namespace xios
{
  class CField;

  /*!
   * A terminal filter which transmits the packets it receives to a field for writting in a file.
   */
  class CFileWriterFilter : public CInputPin
  {
    public:
      int tag;
      Time start_graph;
      Time end_graph;
      CField* field; //<! The associated field
      int filterID;
      int distance;

      /*!
       * Constructs the filter (with one input slot) associated to the specified field
       * and a garbage collector.
       *
       * \param gc the associated garbage collector
       * \param field the associated field
       */
      CFileWriterFilter(CGarbageCollector& gc, CField* field);

      inline StdString GetName(void) {return "File writer filter";};


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

    protected:
      /*!
       * Callbacks a field to write a packet to a file.
       *
       * \param data a vector of packets corresponding to each slot
       */
      void virtual onInputReady(std::vector<CDataPacketPtr> data);
      void virtual buildGraph(std::vector<CDataPacketPtr> data);

    private:
      std::map<Time, CDataPacketPtr> packets; //<! The stored packets
  }; // class CFileWriterFilter
} // namespace xios

#endif //__XIOS_CFileWriterFilter__
