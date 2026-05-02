#ifndef __XIOS_CCalendar_util__
#define __XIOS_CCalendar_util__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "exception.hpp"
#include "calendar.hpp"

namespace xios
{
      /// ////////////////////// Déclarations ////////////////////// ///

      CDuration operator*(const double& scal,   const CDuration& ddr);
      CDuration operator-(const CDuration& ddr, const CDuration& dr);
      CDuration operator+(const CDuration& ddr, const CDuration& dr);
      CDuration operator*(const CDuration& ddr, const double& scal);
      CDuration operator-(const CDuration& ddr);

      bool operator>(const CDuration& ddr, const CDuration& dr);
      bool operator<(const CDuration& ddr, const CDuration& dr);
      
      CDate operator+(const CDate& dt, const CDuration& dr); // Non testée.
      CDate operator-(const CDate& dt, const CDuration& dr);

      CDuration operator-(const CDate& dt0, const CDate& dt1);

      /// Les opérateurs de comparaison. (Non testés pour le moment)
      bool operator==(const CDuration& ddr, const CDuration& dr);
      bool operator!=(const CDuration& ddr, const CDuration& dr);

      bool operator==(const CDate& dt0, const CDate& dt1);
      bool operator< (const CDate& dt0, const CDate& dt1);

      bool operator!=(const CDate& dt0, const CDate& dt1);
      bool operator> (const CDate& dt0, const CDate& dt1);
      bool operator>=(const CDate& dt0, const CDate& dt1);
      bool operator<=(const CDate& dt0, const CDate& dt1);

      ///---------------------------------------------------------------

      //!< Provides a fake "less" comparator for durations that can be used as a comparator for maps
      struct DurationFakeLessComparator {
        bool operator()(const CDuration& dur1, const CDuration& dur2) const;
      };
} // namespace xios

#endif //__XIOS_CCalendar_util__
