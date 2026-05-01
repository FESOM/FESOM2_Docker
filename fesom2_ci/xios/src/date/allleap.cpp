#include "allleap.hpp"

namespace xios
{
      /// ////////////////////// Définitions ////////////////////// ///

      CAllLeapCalendar::CAllLeapCalendar(const CDate& startDate)
         : CCalendar("AllLeap", startDate)
      {
         // This will check that the dates are conform with the calendar.
         // We cannot call this from the parent constructor because we
         // want the methods of this class to be used
         initializeDate();
      }

      CAllLeapCalendar::CAllLeapCalendar(const CDate& startDate, const CDate& timeOrigin)
         : CCalendar("AllLeap", startDate, timeOrigin)
      {
         // This will check that the dates are conform with the calendar.
         // We cannot call this from the parent constructor because we
         // want the methods of this class to be used
         initializeDate();
      }

      CAllLeapCalendar::CAllLeapCalendar(int yr, int mth, int d,
                                         int hr, int min, int sec)
         : CCalendar("AllLeap")
      { initializeDate(yr, mth, d, hr, min, sec) ; }

      CAllLeapCalendar::~CAllLeapCalendar(void)
      { /* Ne rien faire de plus */ }

      ///--------------------------------------------------------------

      int CAllLeapCalendar::getYearTotalLength(const CDate & date) const
      { return (366 * 86400); }

      int CAllLeapCalendar::getMonthLength(const CDate & date) const
      {
         if (date.getMonth() == 2) return (29);
         return (CCalendar::getMonthLength(date));
      }

      StdString CAllLeapCalendar::getType(void) const
      { return (StdString("all_leap")); }

      ///--------------------------------------------------------------
} // namespace xios

