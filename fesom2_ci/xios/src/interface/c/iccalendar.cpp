#include "xios.hpp"

#include "icdate.hpp"
#include "exception.hpp"
#include "timer.hpp"
#include "context.hpp"
#include "context_client.hpp"

extern "C"
{
  void cxios_update_calendar(int step)
  TRY
  {
    CTimer::get("XIOS").resume();
    xios::CContext* context = CContext::getCurrent();
    if (!context->hasServer && !context->client->isAttachedModeEnabled())
      context->checkBuffersAndListen();
    context->updateCalendar(step);
    context->sendUpdateCalendar(step);
    CTimer::get("XIOS").suspend();
  }
  CATCH_DUMP_STACK

  void cxios_get_current_date(cxios_date* current_date_c)
  TRY
  {
    CTimer::get("XIOS").resume();
    const xios::CContext* context = CContext::getCurrent();
    const std::shared_ptr<xios::CCalendar> cal = context->getCalendar();
    if (!cal)
      ERROR("void cxios_get_current_date(cxios_date* current_date_c)",
            << "Impossible to get the current date: no calendar was defined.");
    const CDate& currentDate = cal->getCurrentDate();
    current_date_c->year = currentDate.getYear();
    current_date_c->month = currentDate.getMonth();
    current_date_c->day = currentDate.getDay();
    current_date_c->hour = currentDate.getHour();
    current_date_c->minute = currentDate.getMinute();
    current_date_c->second = currentDate.getSecond();
    CTimer::get("XIOS").suspend();
  }
  CATCH_DUMP_STACK

  int cxios_get_year_length_in_seconds(int year)
  TRY
  {
    CTimer::get("XIOS").resume();
    const std::shared_ptr<xios::CCalendar> cal = CContext::getCurrent()->getCalendar();
    if (!cal)
      ERROR("int cxios_get_year_length_in_seconds(int year)",
            << "Impossible to get the year length: no calendar was defined.");
    int length = cal->getYearTotalLength(CDate(*cal, year, 01, 01));
    CTimer::get("XIOS").suspend();

    return length;
  }
  CATCH_DUMP_STACK

  int cxios_get_day_length_in_seconds()
  TRY
  {
    CTimer::get("XIOS").resume();
    const std::shared_ptr<xios::CCalendar> cal = CContext::getCurrent()->getCalendar();
    if (!cal)
      ERROR("int cxios_get_day_length_in_seconds()",
            << "Impossible to get the day length: no calendar was defined.");
    int length = cal->getDayLengthInSeconds();
    CTimer::get("XIOS").suspend();

    return length;
  }
  CATCH_DUMP_STACK
}