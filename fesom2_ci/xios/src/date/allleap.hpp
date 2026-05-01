#ifndef __XIOS_CAllLeapCalendar__
#define __XIOS_CAllLeapCalendar__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "calendar.hpp"

namespace xios
{
      /// ////////////////////// Déclarations ////////////////////// ///
      class CAllLeapCalendar : public CCalendar
      {
            /// Typedef ///
            typedef CCalendar SuperClass;

         public :

            /// Constructeur ///
//            CAllLeapCalendar(void);                                   // Not implemented yet.
            CAllLeapCalendar(const CDate& startDate);
            CAllLeapCalendar(const CDate& startDate, const CDate& timeOriginStr);
            CAllLeapCalendar(int yr = 0, int mth = 1, int d   = 1,
                             int hr = 0, int min = 0, int sec = 0);
            CAllLeapCalendar(const CAllLeapCalendar& calendar);       // Not implemented yet.
            CAllLeapCalendar(const CAllLeapCalendar* calendar);       // Not implemented yet.

            /// Accesseurs ///
            virtual int getYearTotalLength(const CDate & date) const;
            virtual int getMonthLength(const CDate & date) const;
            virtual StdString getType(void) const;

            /// Destructeur ///
            virtual ~CAllLeapCalendar(void);

      }; // class CAllLeapCalendar

} // namespace xios

#endif // __XIOS_CAllLeapCalendar__
