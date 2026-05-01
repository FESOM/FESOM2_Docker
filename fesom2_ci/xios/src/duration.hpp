#ifndef __XIOS_CDuration__
#define __XIOS_CDuration__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "exception.hpp"

namespace xios
{
      /// ////////////////////// Déclarations ////////////////////// ///
      typedef long long int Time;
      class CCalendar;

      ///---------------------------------------------------------------

      struct CDuration
      {
         public: /* static */
            static CDuration FromString(const StdString& str);

         public:
            CDuration(double year=0.0, double month=0.0, double day=0.0, double hour=0.0, double minute=0.0, double second=0.0, double timestep=0.0);

            /// Opérateurs ///
            CDuration& operator=(const CDuration& duration);
            bool operator==(const CDuration& duration);

            friend StdOStream& operator<<(StdOStream& out, const CDuration& duration);
            friend StdIStream& operator>>(StdIStream& in , CDuration& duration);

            /// Test ///
            bool isNone(void) const;

            /// Traitement ///
            CDuration& resolve(const CCalendar& calendar, bool noNegativeTime = false);
            CDuration& solveTimeStep(const CCalendar& c);
            /// Autres ///
            StdString toString(void) const;
            StdString toStringUDUnits(void) const;

            /// Propriétés publiques ///
            double year, month, day, hour, minute, second, timestep;
      };

      ///---------------------------------------------------------------

      const extern CDuration Year, Month,  Week,   Day,
                             Hour, Minute, Second, TimeStep, NoneDu;
} // namespace xios

#endif // __XIOS_CDuration__
