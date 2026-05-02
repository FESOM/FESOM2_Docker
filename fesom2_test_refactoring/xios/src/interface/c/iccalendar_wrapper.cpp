/* ************************************************************************** *
 *      Copyright © IPSL/LSCE, xios, Avril 2010 - Octobre 2011         *
 * ************************************************************************** */

#include <boost/multi_array.hpp>

#include <memory>

#include "xios.hpp"

#include "attribute_template.hpp"
#include "object_template.hpp"
#include "group_template.hpp"

#include "icutil.hpp"
#include "icdate.hpp"
#include "timer.hpp"
#include "calendar_wrapper.hpp"

extern "C"
{
// /////////////////////////////// Définitions ////////////////////////////// //

  // ----------------------- Redéfinition de type ----------------------------

  typedef xios::CCalendarWrapper *XCalendarWrapperPtr;

  // ------------------------ Création des handle -----------------------------

  void cxios_calendar_wrapper_handle_create(XCalendarWrapperPtr* _ret, const char* _id, int _id_len)
  TRY
  {
    std::string id;
    if (!cstr2string(_id, _id_len, id)) return;
    CTimer::get("XIOS").resume();
    *_ret = CCalendarWrapper::get(id);
    CTimer::get("XIOS").suspend();
  }
  CATCH_DUMP_STACK

  void cxios_get_current_calendar_wrapper(XCalendarWrapperPtr* _ret)
  TRY
  {
    CTimer::get("XIOS").resume();
    *_ret = CCalendarWrapper::get(CCalendarWrapper::GetDefName());
    CTimer::get("XIOS").suspend();
  }
  CATCH_DUMP_STACK

  // -------------------- Vérification des identifiants -----------------------

  void cxios_calendar_wrapper_valid_id(bool* _ret, const char* _id, int _id_len)
  TRY
  {
    std::string id;
    if (!cstr2string(_id, _id_len, id)) return;
    CTimer::get("XIOS").resume();
    *_ret = CCalendarWrapper::has(id);
    CTimer::get("XIOS").suspend();
  }
  CATCH_DUMP_STACK

  // ----------------------- Custom getters and setters -----------------------

  void cxios_set_calendar_wrapper_date_start_date(XCalendarWrapperPtr calendarWrapper_hdl, cxios_date start_date_c)
  TRY
  {
    CTimer::get("XIOS").resume();
    CDate start_date(*calendarWrapper_hdl->getCalendar(true),
                     start_date_c.year,
                     start_date_c.month,
                     start_date_c.day,
                     start_date_c.hour,
                     start_date_c.minute,
                     start_date_c.second);
    calendarWrapper_hdl->setInitDate(start_date);
    CTimer::get("XIOS").suspend();
  }
  CATCH_DUMP_STACK

  void cxios_get_calendar_wrapper_date_start_date(XCalendarWrapperPtr calendarWrapper_hdl, cxios_date* start_date_c)
  TRY
  {
    CTimer::get("XIOS").resume();
    const CDate& start_date = calendarWrapper_hdl->getInitDate();
    start_date_c->year = start_date.getYear();
    start_date_c->month = start_date.getMonth();
    start_date_c->day = start_date.getDay();
    start_date_c->hour = start_date.getHour();
    start_date_c->minute = start_date.getMinute();
    start_date_c->second = start_date.getSecond();
    CTimer::get("XIOS").suspend();
  }
  CATCH_DUMP_STACK

  void cxios_set_calendar_wrapper_date_time_origin(XCalendarWrapperPtr calendarWrapper_hdl, cxios_date time_origin_c)
  TRY
  {
    CTimer::get("XIOS").resume();
    CDate time_origin(*calendarWrapper_hdl->getCalendar(true),
                      time_origin_c.year,
                      time_origin_c.month,
                      time_origin_c.day,
                      time_origin_c.hour,
                      time_origin_c.minute,
                      time_origin_c.second);
    calendarWrapper_hdl->setTimeOrigin(time_origin);
    CTimer::get("XIOS").suspend();
  }
  CATCH_DUMP_STACK

  void cxios_get_calendar_wrapper_date_time_origin(XCalendarWrapperPtr calendarWrapper_hdl, cxios_date* time_origin_c)
  TRY
  {
    CTimer::get("XIOS").resume();
    const CDate& time_origin = calendarWrapper_hdl->getTimeOrigin();
    time_origin_c->year = time_origin.getYear();
    time_origin_c->month = time_origin.getMonth();
    time_origin_c->day = time_origin.getDay();
    time_origin_c->hour = time_origin.getHour();
    time_origin_c->minute = time_origin.getMinute();
    time_origin_c->second = time_origin.getSecond();
    CTimer::get("XIOS").suspend();
  }
  CATCH_DUMP_STACK

  // ----------------------- Calendar creation and update ----------------------

  void cxios_create_calendar(XCalendarWrapperPtr calendarWrapper_hdl)
  TRY
  {
    CTimer::get("XIOS").resume();
    calendarWrapper_hdl->createCalendar();
    CTimer::get("XIOS").suspend();
  }
  CATCH_DUMP_STACK

  void cxios_update_calendar_timestep(XCalendarWrapperPtr calendarWrapper_hdl)
  TRY
  {
    CTimer::get("XIOS").resume();
    calendarWrapper_hdl->updateTimestep();
    CTimer::get("XIOS").suspend();
  }
  CATCH_DUMP_STACK
} // extern "C"
