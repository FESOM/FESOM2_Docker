#include "file_server_writer_filter.hpp"
#include "exception.hpp"
#include "field.hpp"

namespace xios
{
  CFileServerWriterFilter::CFileServerWriterFilter(CGarbageCollector& gc, CField* field)
    : CInputPin(gc, 1)
    , field(field)
  {
    if (!field)
      ERROR("CFileServerWriterFilter::CFileServerWriterFilter(CField* field)",
            "The field cannot be null.");
  }

  void CFileServerWriterFilter::onInputReady(std::vector<CDataPacketPtr> data)
  {
    field->writeUpdateData(data[0]->data);
  }

  bool CFileServerWriterFilter::mustAutoTrigger() const
  {
    return true;
  }

  bool CFileServerWriterFilter::isDataExpected(const CDate& date) const
  {
    return true;
  }
} // namespace xios
