#include "d360.hpp"

namespace xios
{
      /// ////////////////////// Définitions ////////////////////// ///

      CD360Calendar::CD360Calendar(const CDate& startDate)
         : CCalendar("D360", startDate)
      {
         // This will check that the dates are conform with the calendar.
         // We cannot call this from the parent constructor because we
         // want the methods of this class to be used
         initializeDate();
      }

      CD360Calendar::CD360Calendar(const CDate& startDate, const CDate& timeOrigin)
         : CCalendar("D360", startDate, timeOrigin)
      {
         // This will check that the dates are conform with the calendar.
         // We cannot call this from the parent constructor because we
         // want the methods of this class to be used
         initializeDate();
      }

      CD360Calendar::CD360Calendar(int yr, int mth, int d,
                                   int hr, int min, int sec)
         : CCalendar("D360")
      { initializeDate(yr, mth, d, hr, min, sec) ; }

      CD360Calendar::~CD360Calendar(void)
      { /* Ne rien faire de plus */ }

      ///--------------------------------------------------------------

      int CD360Calendar::getYearTotalLength(const CDate & date) const
      { return (360 * 86400); }

      int CD360Calendar::getMonthLength(const CDate & date) const
      { return (30); }

      StdString CD360Calendar::getType(void) const
      { return (StdString("360_day")); }

      ///--------------------------------------------------------------
} // namespace xios

