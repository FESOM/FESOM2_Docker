#include "julian.hpp"

namespace xios
{
      /// ////////////////////// Définitions ////////////////////// ///

      CJulianCalendar::CJulianCalendar(const CDate& startDate)
         : CCalendar("Julian", startDate)
      {
         // This will check that the dates are conform with the calendar.
         // We cannot call this from the parent constructor because we
         // want the methods of this class to be used
         initializeDate();
      }

      CJulianCalendar::CJulianCalendar(const CDate& startDate, const CDate& timeOrigin)
         : CCalendar("Julian", startDate, timeOrigin)
      {
         // This will check that the dates are conform with the calendar.
         // We cannot call this from the parent constructor because we
         // want the methods of this class to be used
         initializeDate();
      }

      CJulianCalendar::CJulianCalendar(int yr, int mth, int d,
                                       int hr, int min, int sec)
         : CCalendar("Julian")
      { initializeDate(yr, mth, d, hr, min, sec) ; }

      CJulianCalendar::~CJulianCalendar(void)
      { /* Ne rien faire de plus */ }

      ///--------------------------------------------------------------

      int CJulianCalendar::getYearTotalLength(const CDate& date) const
      { // Retourne la durée d'une année en seconde.
         if (date.getYear() % 4 == 0) return (366 * 86400);
         return (365 * 86400);
      }

      int CJulianCalendar::getMonthLength(const CDate& date) const
      { // Retourne la durée du mois en jour.
         if (date.getMonth() == 2)
         {
            if (date.getYear()%4 == 0) return 29;
               return 28;
         }
         return (CCalendar::getMonthLength(date));
      }

      StdString CJulianCalendar::getType(void) const
      { return (StdString("julian")); }

      bool CJulianCalendar::hasLeapYear() const { return true; }

      ///--------------------------------------------------------------
} // namespace xios
