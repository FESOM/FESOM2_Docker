#include "noleap.hpp"
#include "calendar.hpp"

namespace xios
{
      /// ////////////////////// Définitions ////////////////////// ///

      CNoLeapCalendar::CNoLeapCalendar(const CDate& startDate)
         : CCalendar("NoLeap", startDate)
      {
         // This will check that the dates are conform with the calendar.
         // We cannot call this from the parent constructor because we
         // want the methods of this class to be used
         initializeDate();
      }

      CNoLeapCalendar::CNoLeapCalendar(const CDate& startDate, const CDate& timeOrigin)
         : CCalendar("NoLeap", startDate, timeOrigin)
      {
         // This will check that the dates are conform with the calendar.
         // We cannot call this from the parent constructor because we
         // want the methods of this class to be used
         initializeDate();
      }

      CNoLeapCalendar::CNoLeapCalendar(int yr, int mth, int d,
                                       int hr, int min, int sec)
         : CCalendar("NoLeap")
      { initializeDate(yr, mth, d, hr, min, sec) ; }


      CNoLeapCalendar::~CNoLeapCalendar(void)
      { /* Ne rien faire de plus */ }

      ///--------------------------------------------------------------

      StdString CNoLeapCalendar::getType(void) const
      { return (StdString("noleap")); }

      ///--------------------------------------------------------------
} // namespace xios

