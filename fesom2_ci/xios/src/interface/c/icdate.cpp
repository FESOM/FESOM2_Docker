/* ************************************************************************** *
 *      Copyright © IPSL/LSCE, xios, Avril 2010 - Octobre 2011         *
 * ************************************************************************** */

#include <boost/multi_array.hpp>

#include "xios.hpp"

#include "attribute_template.hpp"
#include "object_template.hpp"
#include "group_template.hpp"

#include "calendar_type.hpp"

#include "icutil.hpp"
#include "icdate.hpp"
#include "exception.hpp"
#include "calendar_util.hpp"
#include "timer.hpp"
#include "context.hpp"
#include "context_client.hpp"

static const xios::CCalendar& getCalendar(const std::string& idFunc)
{
  const xios::CContext* context = CContext::getCurrent();
  if (!context)
    ERROR(idFunc, << "Impossible to do calendar operations: no current context available.");
  const std::shared_ptr<xios::CCalendar> cal = context->getCalendar();
  if (!cal)
    ERROR(idFunc, << "Impossible to do calendar operations: no calendar was defined.");
  return *cal;
}

extern "C"
{
  long long int cxios_date_convert_to_seconds(cxios_date date_c)
  TRY
  {
    xios::CDate date = xios::CDate(getCalendar("long long int cxios_date_convert_to_seconds(cxios_date date_c)"),
                                   date_c.year, date_c.month, date_c.day,
                                   date_c.hour, date_c.minute, date_c.second);
    return date;
  }
  CATCH_DUMP_STACK

  void cxios_date_convert_to_string(cxios_date date_c, char* str, int str_size)
  TRY
  {
    xios::CDate date = xios::CDate(getCalendar("void cxios_date_convert_to_string(cxios_date date_c, char* str, int str_size)"),
                                   date_c.year, date_c.month, date_c.day,
                                   date_c.hour, date_c.minute, date_c.second);

    if (!string_copy(date.toString(), str, str_size))
      ERROR("void cxios_date_convert_to_string(cxios_date date_c, char* str, int str_size)", << "Input string is too short");
  }
  CATCH_DUMP_STACK

  cxios_date cxios_date_convert_from_string(const char* str, int str_size)
  TRY
  {
    std::string date_str;
    xios::CDate date;

    if (cstr2string(str, str_size, date_str))
      date = xios::CDate::FromString(date_str,
                                     getCalendar("cxios_date cxios_date_convert_from_string(const char* str, int str_size)"));

    return { date.getYear(), date.getMonth(), date.getDay(), date.getHour(), date.getMinute(), date.getSecond() };
  }
  CATCH_DUMP_STACK

  cxios_date cxios_date_add_duration(cxios_date date_c, cxios_duration dur_c)
  TRY
  {
    xios::CDate date = xios::CDate(getCalendar("cxios_date cxios_date_add_duration(cxios_date date_c, cxios_duration dur_c)"),
                                   date_c.year, date_c.month, date_c.day,
                                   date_c.hour, date_c.minute, date_c.second);
    xios::CDuration dur( dur_c.year, dur_c.month, dur_c.day, dur_c.hour, dur_c.minute, dur_c.second, dur_c.timestep );
    xios::CDate res = date + dur;
    return { res.getYear(), res.getMonth(), res.getDay(), res.getHour(), res.getMinute(), res.getSecond() };
  }
  CATCH_DUMP_STACK

  cxios_date cxios_date_sub_duration(cxios_date date_c, cxios_duration dur_c)
  TRY
  {
    xios::CDate date = xios::CDate(getCalendar("cxios_date cxios_date_sub_duration(cxios_date date_c, cxios_duration dur_c)"),
                                   date_c.year, date_c.month, date_c.day,
                                   date_c.hour, date_c.minute, date_c.second);
    xios::CDuration dur( dur_c.year, dur_c.month, dur_c.day, dur_c.hour, dur_c.minute, dur_c.second, dur_c.timestep );

    xios::CDate res = date - dur;
    return { res.getYear(), res.getMonth(), res.getDay(), res.getHour(), res.getMinute(), res.getSecond() };
  }
  CATCH_DUMP_STACK

  cxios_duration cxios_date_sub(cxios_date date1_c, cxios_date date2_c)
  TRY
  {
    xios::CDate date1 = xios::CDate(getCalendar("cxios_duration cxios_date_sub(cxios_date date1_c, cxios_date date2_c)"),
                                    date1_c.year, date1_c.month, date1_c.day,
                                    date1_c.hour, date1_c.minute, date1_c.second);
    xios::CDate date2 = xios::CDate(getCalendar("cxios_duration cxios_date_sub(cxios_date date1_c, cxios_date date2_c)"),
                                    date2_c.year, date2_c.month, date2_c.day,
                                    date2_c.hour, date2_c.minute, date2_c.second);
    xios::CDuration res = date1 - date2;
    return { res.year, res.month, res.day, res.hour, res.minute, res.second, res.timestep };
  }
  CATCH_DUMP_STACK

  bool cxios_date_eq(cxios_date date1_c, cxios_date date2_c)
  TRY
  {
    xios::CDate date1 = xios::CDate(getCalendar("bool cxios_date_eq(cxios_date date1_c, cxios_date date2_c)"),
                                    date1_c.year, date1_c.month, date1_c.day,
                                    date1_c.hour, date1_c.minute, date1_c.second);
    xios::CDate date2 = xios::CDate(getCalendar("bool cxios_date_eq(cxios_date date1_c, cxios_date date2_c)"),
                                    date2_c.year, date2_c.month, date2_c.day,
                                    date2_c.hour, date2_c.minute, date2_c.second);
    return (date1 == date2);
  }
  CATCH_DUMP_STACK

  bool cxios_date_neq(cxios_date date1_c, cxios_date date2_c)
  TRY
  {
    xios::CDate date1 = xios::CDate(getCalendar("bool cxios_date_eq(cxios_date date1_c, cxios_date date2_c)"),
                                    date1_c.year, date1_c.month, date1_c.day,
                                    date1_c.hour, date1_c.minute, date1_c.second);
    xios::CDate date2 = xios::CDate(getCalendar("bool cxios_date_eq(cxios_date date1_c, cxios_date date2_c)"),
                                    date2_c.year, date2_c.month, date2_c.day,
                                    date2_c.hour, date2_c.minute, date2_c.second);
    return (date1 != date2);
  }
  CATCH_DUMP_STACK

  bool cxios_date_lt(cxios_date date1_c, cxios_date date2_c)
  TRY
  {
    xios::CDate date1 = xios::CDate(getCalendar("bool cxios_date_eq(cxios_date date1_c, cxios_date date2_c)"),
                                    date1_c.year, date1_c.month, date1_c.day,
                                    date1_c.hour, date1_c.minute, date1_c.second);
    xios::CDate date2 = xios::CDate(getCalendar("bool cxios_date_eq(cxios_date date1_c, cxios_date date2_c)"),
                                    date2_c.year, date2_c.month, date2_c.day,
                                    date2_c.hour, date2_c.minute, date2_c.second);
    return (date1 < date2);
  }
  CATCH_DUMP_STACK

  bool cxios_date_le(cxios_date date1_c, cxios_date date2_c)
  TRY
  {
    xios::CDate date1 = xios::CDate(getCalendar("bool cxios_date_eq(cxios_date date1_c, cxios_date date2_c)"),
                                    date1_c.year, date1_c.month, date1_c.day,
                                    date1_c.hour, date1_c.minute, date1_c.second);
    xios::CDate date2 = xios::CDate(getCalendar("bool cxios_date_eq(cxios_date date1_c, cxios_date date2_c)"),
                                    date2_c.year, date2_c.month, date2_c.day,
                                    date2_c.hour, date2_c.minute, date2_c.second);
    return (date1 <= date2);
  }
  CATCH_DUMP_STACK

  bool cxios_date_gt(cxios_date date1_c, cxios_date date2_c)
  TRY
  {
    xios::CDate date1 = xios::CDate(getCalendar("bool cxios_date_eq(cxios_date date1_c, cxios_date date2_c)"),
                                    date1_c.year, date1_c.month, date1_c.day,
                                    date1_c.hour, date1_c.minute, date1_c.second);
    xios::CDate date2 = xios::CDate(getCalendar("bool cxios_date_eq(cxios_date date1_c, cxios_date date2_c)"),
                                    date2_c.year, date2_c.month, date2_c.day,
                                    date2_c.hour, date2_c.minute, date2_c.second);
    return (date1 > date2);
  }
  CATCH_DUMP_STACK

  bool cxios_date_ge(cxios_date date1_c, cxios_date date2_c)
  TRY
  {
    xios::CDate date1 = xios::CDate(getCalendar("bool cxios_date_eq(cxios_date date1_c, cxios_date date2_c)"),
                                    date1_c.year, date1_c.month, date1_c.day,
                                    date1_c.hour, date1_c.minute, date1_c.second);
    xios::CDate date2 = xios::CDate(getCalendar("bool cxios_date_eq(cxios_date date1_c, cxios_date date2_c)"),
                                    date2_c.year, date2_c.month, date2_c.day,
                                    date2_c.hour, date2_c.minute, date2_c.second);
    return (date1 >= date2);
  }
  CATCH_DUMP_STACK

  int cxios_date_get_second_of_year(cxios_date date_c)
  TRY
  {
    xios::CDate date = xios::CDate(getCalendar("int cxios_date_get_second_of_year(cxios_date date_c)"),
                                   date_c.year, date_c.month, date_c.day,
                                   date_c.hour, date_c.minute, date_c.second);
    return date.getSecondOfYear();
  }
  CATCH_DUMP_STACK

  double cxios_date_get_day_of_year(cxios_date date_c)
  TRY
  {
    xios::CDate date = xios::CDate(getCalendar("int cxios_date_get_day_of_year(cxios_date date_c)"),
                                   date_c.year, date_c.month, date_c.day,
                                   date_c.hour, date_c.minute, date_c.second);
    return date.getDayOfYear();
  }
  CATCH_DUMP_STACK

  double cxios_date_get_fraction_of_year(cxios_date date_c)
  TRY
  {
    xios::CDate date = xios::CDate(getCalendar("int cxios_date_get_fraction_of_year(cxios_date date_c)"),
                                   date_c.year, date_c.month, date_c.day,
                                   date_c.hour, date_c.minute, date_c.second);
    return date.getFractionOfYear();
  }
  CATCH_DUMP_STACK

  int cxios_date_get_second_of_day(cxios_date date_c)
  TRY
  {
    xios::CDate date = xios::CDate(getCalendar("int cxios_date_get_second_of_day(cxios_date date_c)"),
                                   date_c.year, date_c.month, date_c.day,
                                   date_c.hour, date_c.minute, date_c.second);
    return date.getSecondOfDay();
  }
  CATCH_DUMP_STACK

  double cxios_date_get_fraction_of_day(cxios_date date_c)
  TRY
  {
    xios::CDate date = xios::CDate(getCalendar("int cxios_date_get_fraction_of_day(cxios_date date_c)"),
                                   date_c.year, date_c.month, date_c.day,
                                   date_c.hour, date_c.minute, date_c.second);
    return date.getFractionOfDay();
  }
  CATCH_DUMP_STACK
} // extern "C"
