#ifndef __XIOS_CJulianCalendar__
#define __XIOS_CJulianCalendar__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "calendar.hpp"

namespace xios
{
      /// ////////////////////// Déclarations ////////////////////// ///
      class CJulianCalendar : public CCalendar
      {
            /// Typedef ///
            typedef CCalendar SuperClass;

         public :

            /// Constructeur ///
//            CJulianCalendar(void);                                   // Not implemented yet.
            CJulianCalendar(const CDate& startDate);
            CJulianCalendar(const CDate& startDate, const CDate& timeOrigin);
            CJulianCalendar(int yr = 0, int mth = 1, int d   = 1,
                            int hr = 0, int min = 0, int sec = 0);
            CJulianCalendar(const CJulianCalendar& calendar);       // Not implemented yet.
            CJulianCalendar(const CJulianCalendar* calendar);       // Not implemented yet.

            /// Accesseurs ///
            virtual int getYearTotalLength(const CDate & date) const;
            virtual int getMonthLength(const CDate & date) const;
            virtual StdString getType(void) const;

            virtual bool hasLeapYear() const;

            /// Destructeur ///
            virtual ~CJulianCalendar(void);

      }; // class CJulianCalendar

} // namespace xios

#endif // __XIOS_CJulianCalendar__
