/* ************************************************************************** *
 *               Interface auto generated - do not modify                     *
 * ************************************************************************** */

#include <boost/multi_array.hpp>
#include "xios.hpp"
#include "attribute_template.hpp"
#include "object_template.hpp"
#include "group_template.hpp"
#include "icutil.hpp"
#include "icdate.hpp"
#include "timer.hpp"
#include "node_type.hpp"

extern "C"
{
  typedef xios::CCalendarWrapper* calendar_wrapper_Ptr;

  void cxios_set_calendar_wrapper_comment(calendar_wrapper_Ptr calendar_wrapper_hdl, const char * comment, int comment_size)
  {
    std::string comment_str;
    if (!cstr2string(comment, comment_size, comment_str)) return;
    CTimer::get("XIOS").resume();
    calendar_wrapper_hdl->comment.setValue(comment_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_calendar_wrapper_comment(calendar_wrapper_Ptr calendar_wrapper_hdl, char * comment, int comment_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(calendar_wrapper_hdl->comment.getInheritedValue(), comment, comment_size))
      ERROR("void cxios_get_calendar_wrapper_comment(calendar_wrapper_Ptr calendar_wrapper_hdl, char * comment, int comment_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_calendar_wrapper_comment(calendar_wrapper_Ptr calendar_wrapper_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = calendar_wrapper_hdl->comment.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_calendar_wrapper_day_length(calendar_wrapper_Ptr calendar_wrapper_hdl, int day_length)
  {
    CTimer::get("XIOS").resume();
    calendar_wrapper_hdl->day_length.setValue(day_length);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_calendar_wrapper_day_length(calendar_wrapper_Ptr calendar_wrapper_hdl, int* day_length)
  {
    CTimer::get("XIOS").resume();
    *day_length = calendar_wrapper_hdl->day_length.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_calendar_wrapper_day_length(calendar_wrapper_Ptr calendar_wrapper_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = calendar_wrapper_hdl->day_length.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_calendar_wrapper_leap_year_drift(calendar_wrapper_Ptr calendar_wrapper_hdl, double leap_year_drift)
  {
    CTimer::get("XIOS").resume();
    calendar_wrapper_hdl->leap_year_drift.setValue(leap_year_drift);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_calendar_wrapper_leap_year_drift(calendar_wrapper_Ptr calendar_wrapper_hdl, double* leap_year_drift)
  {
    CTimer::get("XIOS").resume();
    *leap_year_drift = calendar_wrapper_hdl->leap_year_drift.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_calendar_wrapper_leap_year_drift(calendar_wrapper_Ptr calendar_wrapper_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = calendar_wrapper_hdl->leap_year_drift.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_calendar_wrapper_leap_year_drift_offset(calendar_wrapper_Ptr calendar_wrapper_hdl, double leap_year_drift_offset)
  {
    CTimer::get("XIOS").resume();
    calendar_wrapper_hdl->leap_year_drift_offset.setValue(leap_year_drift_offset);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_calendar_wrapper_leap_year_drift_offset(calendar_wrapper_Ptr calendar_wrapper_hdl, double* leap_year_drift_offset)
  {
    CTimer::get("XIOS").resume();
    *leap_year_drift_offset = calendar_wrapper_hdl->leap_year_drift_offset.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_calendar_wrapper_leap_year_drift_offset(calendar_wrapper_Ptr calendar_wrapper_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = calendar_wrapper_hdl->leap_year_drift_offset.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_calendar_wrapper_leap_year_month(calendar_wrapper_Ptr calendar_wrapper_hdl, int leap_year_month)
  {
    CTimer::get("XIOS").resume();
    calendar_wrapper_hdl->leap_year_month.setValue(leap_year_month);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_calendar_wrapper_leap_year_month(calendar_wrapper_Ptr calendar_wrapper_hdl, int* leap_year_month)
  {
    CTimer::get("XIOS").resume();
    *leap_year_month = calendar_wrapper_hdl->leap_year_month.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_calendar_wrapper_leap_year_month(calendar_wrapper_Ptr calendar_wrapper_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = calendar_wrapper_hdl->leap_year_month.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_calendar_wrapper_month_lengths(calendar_wrapper_Ptr calendar_wrapper_hdl, int* month_lengths, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(month_lengths, shape(extent[0]), neverDeleteData);
    calendar_wrapper_hdl->month_lengths.reference(tmp.copy());
     CTimer::get("XIOS").suspend();
  }

  void cxios_get_calendar_wrapper_month_lengths(calendar_wrapper_Ptr calendar_wrapper_hdl, int* month_lengths, int* extent)
  {
    CTimer::get("XIOS").resume();
    CArray<int,1> tmp(month_lengths, shape(extent[0]), neverDeleteData);
    tmp=calendar_wrapper_hdl->month_lengths.getInheritedValue();
     CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_calendar_wrapper_month_lengths(calendar_wrapper_Ptr calendar_wrapper_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = calendar_wrapper_hdl->month_lengths.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_calendar_wrapper_start_date(calendar_wrapper_Ptr calendar_wrapper_hdl, const char * start_date, int start_date_size)
  {
    std::string start_date_str;
    if (!cstr2string(start_date, start_date_size, start_date_str)) return;
    CTimer::get("XIOS").resume();
    calendar_wrapper_hdl->start_date.setValue(start_date_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_calendar_wrapper_start_date(calendar_wrapper_Ptr calendar_wrapper_hdl, char * start_date, int start_date_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(calendar_wrapper_hdl->start_date.getInheritedValue(), start_date, start_date_size))
      ERROR("void cxios_get_calendar_wrapper_start_date(calendar_wrapper_Ptr calendar_wrapper_hdl, char * start_date, int start_date_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_calendar_wrapper_start_date(calendar_wrapper_Ptr calendar_wrapper_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = calendar_wrapper_hdl->start_date.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_calendar_wrapper_time_origin(calendar_wrapper_Ptr calendar_wrapper_hdl, const char * time_origin, int time_origin_size)
  {
    std::string time_origin_str;
    if (!cstr2string(time_origin, time_origin_size, time_origin_str)) return;
    CTimer::get("XIOS").resume();
    calendar_wrapper_hdl->time_origin.setValue(time_origin_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_calendar_wrapper_time_origin(calendar_wrapper_Ptr calendar_wrapper_hdl, char * time_origin, int time_origin_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(calendar_wrapper_hdl->time_origin.getInheritedValue(), time_origin, time_origin_size))
      ERROR("void cxios_get_calendar_wrapper_time_origin(calendar_wrapper_Ptr calendar_wrapper_hdl, char * time_origin, int time_origin_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_calendar_wrapper_time_origin(calendar_wrapper_Ptr calendar_wrapper_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = calendar_wrapper_hdl->time_origin.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_calendar_wrapper_timestep(calendar_wrapper_Ptr calendar_wrapper_hdl, cxios_duration timestep_c)
  {
    CTimer::get("XIOS").resume();
    calendar_wrapper_hdl->timestep.allocate();
    CDuration& timestep = calendar_wrapper_hdl->timestep.get();
    timestep.year = timestep_c.year;
    timestep.month = timestep_c.month;
    timestep.day = timestep_c.day;
    timestep.hour = timestep_c.hour;
    timestep.minute = timestep_c.minute;
    timestep.second = timestep_c.second;
    timestep.timestep = timestep_c.timestep;
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_calendar_wrapper_timestep(calendar_wrapper_Ptr calendar_wrapper_hdl, cxios_duration* timestep_c)
  {
    CTimer::get("XIOS").resume();
    CDuration timestep = calendar_wrapper_hdl->timestep.getInheritedValue();
    timestep_c->year = timestep.year;
    timestep_c->month = timestep.month;
    timestep_c->day = timestep.day;
    timestep_c->hour = timestep.hour;
    timestep_c->minute = timestep.minute;
    timestep_c->second = timestep.second;
    timestep_c->timestep = timestep.timestep;
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_calendar_wrapper_timestep(calendar_wrapper_Ptr calendar_wrapper_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = calendar_wrapper_hdl->timestep.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_calendar_wrapper_type(calendar_wrapper_Ptr calendar_wrapper_hdl, const char * type, int type_size)
  {
    std::string type_str;
    if (!cstr2string(type, type_size, type_str)) return;
    CTimer::get("XIOS").resume();
    calendar_wrapper_hdl->type.fromString(type_str);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_calendar_wrapper_type(calendar_wrapper_Ptr calendar_wrapper_hdl, char * type, int type_size)
  {
    CTimer::get("XIOS").resume();
    if (!string_copy(calendar_wrapper_hdl->type.getInheritedStringValue(), type, type_size))
      ERROR("void cxios_get_calendar_wrapper_type(calendar_wrapper_Ptr calendar_wrapper_hdl, char * type, int type_size)", << "Input string is too short");
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_calendar_wrapper_type(calendar_wrapper_Ptr calendar_wrapper_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = calendar_wrapper_hdl->type.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }


  void cxios_set_calendar_wrapper_year_length(calendar_wrapper_Ptr calendar_wrapper_hdl, int year_length)
  {
    CTimer::get("XIOS").resume();
    calendar_wrapper_hdl->year_length.setValue(year_length);
    CTimer::get("XIOS").suspend();
  }

  void cxios_get_calendar_wrapper_year_length(calendar_wrapper_Ptr calendar_wrapper_hdl, int* year_length)
  {
    CTimer::get("XIOS").resume();
    *year_length = calendar_wrapper_hdl->year_length.getInheritedValue();
    CTimer::get("XIOS").suspend();
  }

  bool cxios_is_defined_calendar_wrapper_year_length(calendar_wrapper_Ptr calendar_wrapper_hdl)
  {
     CTimer::get("XIOS").resume();
     bool isDefined = calendar_wrapper_hdl->year_length.hasInheritedValue();
     CTimer::get("XIOS").suspend();
     return isDefined;
  }
}
