#ifndef __XIOS_CGregorianCalendar__
#define __XIOS_CGregorianCalendar__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "calendar.hpp"

namespace xios
{
      /// ////////////////////// Déclarations ////////////////////// ///
      class CGregorianCalendar : public CCalendar
      {
            /// Typedef ///
            typedef CCalendar SuperClass;

         public :

            /// Constructeur ///
//            CGregorianCalendar(void);                                   // Not implemented yet.
            CGregorianCalendar(const CDate& startDate);
            CGregorianCalendar(const CDate& startDate, const CDate& timeOrigin);
            CGregorianCalendar(int yr = 0, int mth = 1, int d   = 1,
                               int hr = 0, int min = 0, int sec = 0);
            CGregorianCalendar(const CGregorianCalendar& calendar);       // Not implemented yet.
            CGregorianCalendar(const CGregorianCalendar* calendar);       // Not implemented yet.

            /// Accesseurs ///
            virtual int getYearTotalLength(const CDate & date) const;
            virtual int getMonthLength(const CDate & date) const;
            virtual StdString getType(void) const;

            virtual bool hasLeapYear() const;

            /// Destructeur ///
            virtual ~CGregorianCalendar(void);

      }; // class CGregorianCalendar

} // namespace xios

#endif // __XIOS_CGregorianCalendar__
