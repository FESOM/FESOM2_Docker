#ifndef __XIOS_CNoLeapCalendar__
#define __XIOS_CNoLeapCalendar__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "calendar.hpp"

namespace xios
{
      /// ////////////////////// Déclarations ////////////////////// ///
      class CNoLeapCalendar : public CCalendar
      {
            /// Typedef ///
            typedef CCalendar SuperClass;

         public :

            /// Constructeur ///
//            CNoLeapCalendar(void);                                   // Not implemented yet.
            CNoLeapCalendar(const CDate& startDate);
            CNoLeapCalendar(const CDate& startDate, const CDate& timeOrigin);
            CNoLeapCalendar(int yr = 0, int mth = 1, int d   = 1,
                            int hr = 0, int min = 0, int sec = 0);
            CNoLeapCalendar(const CNoLeapCalendar& calendar);       // Not implemented yet.
            CNoLeapCalendar(const CNoLeapCalendar* calendar);       // Not implemented yet.

            /// Accesseurs ///
            virtual StdString getType(void) const;

            /// Destructeur ///
            virtual ~CNoLeapCalendar(void);

      }; // class CNoLeapCalendar

} // namespace xios

#endif // __XIOS_CNoLeapCalendar__

