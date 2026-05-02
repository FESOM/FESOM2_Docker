#include "gregorian.hpp"

namespace xios
{
      /// ////////////////////// Définitions ////////////////////// ///

      CGregorianCalendar::CGregorianCalendar(const CDate& startDate)
         : CCalendar("Gregorian", startDate)
      {
         // This will check that the dates are conform with the calendar.
         // We cannot call this from the parent constructor because we
         // want the methods of this class to be used
         initializeDate();
      }

      CGregorianCalendar::CGregorianCalendar(const CDate& startDate, const CDate& timeOrigin)
         : CCalendar("Gregorian", startDate, timeOrigin)
      {
         // This will check that the dates are conform with the calendar.
         // We cannot call this from the parent constructor because we
         // want the methods of this class to be used
         initializeDate();
      }

      CGregorianCalendar::CGregorianCalendar(int yr, int mth, int d,
                                             int hr, int min, int sec)
         : CCalendar("Gregorian")
      { initializeDate(yr, mth, d, hr, min, sec) ; }

      CGregorianCalendar::~CGregorianCalendar(void)
      { /* Ne rien faire de plus */ }

      ///--------------------------------------------------------------

      int CGregorianCalendar::getYearTotalLength(const CDate& date) const
      { // Retourne la durée d'une année en seconde.
         if ((date.getYear() % 4   == 0) &&
            ((date.getYear() % 100 != 0)  ||
             (date.getYear() % 400 == 0)  ))
            return (366 * 86400);
         return (365 * 86400);
      }

      int CGregorianCalendar::getMonthLength(const CDate& date) const
      { // Retourne la durée du mois en jour.
         if (date.getMonth() == 2)
         { // Traitement du cas particulier en Février.
            if ((date.getYear() % 4   == 0) &&
               ((date.getYear() % 100 != 0) ||
                (date.getYear() % 400 == 0) ))
               return (29);
            return (28);
         }
         return (CCalendar::getMonthLength(date));
      }

      StdString CGregorianCalendar::getType(void) const
      { return (StdString("gregorian")); }

      bool CGregorianCalendar::hasLeapYear() const { return true; }

      ///--------------------------------------------------------------
} // namespace xios

