#ifndef __XIOS_CUserDefinedCalendar__
#define __XIOS_CUserDefinedCalendar__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "calendar.hpp"
#include "array_new.hpp"

namespace xios
{
  /// ////////////////////// Déclarations ////////////////////// ///
  /*! A custom calendar that we can configured to be suitable for planets other than the Earth. */
  class CUserDefinedCalendar : public CCalendar
  {
    private:
      /// Typedef ///
      typedef CCalendar SuperClass;

    public:
      /// Constructor ///
      CUserDefinedCalendar(int dayLength, const CArray<int,1>& monthLengths);
      CUserDefinedCalendar(int dayLength, int yearLength);

      /// Destructor ///
      virtual ~CUserDefinedCalendar(void);

      /// Setters ///
      /*! Configure the leap year information. */
      void configureLeapYear(int leapYearMonth, double leapYearDrift, double leapYearDriftOffset = 0.0);

      /// Getters ///
      virtual StdString getType(void) const;

      /*! Returns the duration of the date's month in days. */
      virtual int getMonthLength(const CDate& date) const;
      /*! Returns the duration of the date's year in seconds. */
      virtual int getYearTotalLength(const CDate& date) const;
      /*! Returns the duration of a day in hours. Note that this value is
          not necessarily exact since it can be rounded but it is always
          the smallest integer number of hours that can hold a day. */
      virtual int getDayLength(void) const;
      /*! Returns the duration of a year in months. */
      virtual int getYearLength(void) const;
      /*! Returns the day length expressed in seconds. */
      virtual int getDayLengthInSeconds(void) const;
      /*! Test if the calendar can have leap year. */
      virtual bool hasLeapYear() const;

      /*! Simplify a duration based on the calendar information. */
      virtual CDuration& resolve(CDuration& dur, bool noNegativeTime = false) const;

      /*! Parse a date using the calendar's parser. */
      virtual void parseDate(StdIStream& in, CDate& date) const;

      /*! Test if a date is valid with regard to the current calendar. */
      virtual bool checkDate(CDate& date) const;

    private:
      int dayLength; //!< length of a day in seconds
      CArray<int,1> monthLengths; //!< length of each months in days
      int yearLength; //!< length of a year in seconds

      int leapYearMonth; //!< month to which an extra day should be added in case of a leap year
      double leapYearDrift; //!< yearly drift (fraction of a day, must be in range [0, 1))
      double leapYearDriftOffset; //!< initial drift (fraction of a day, must be in range [0, 1))

      /*! Test if the specified year is a leap year. */
      bool isLeapYear(int year) const;
  }; // class CUserDefinedCalendar

} // namespace xios

#endif // __XIOS_CUserDefinedCalendar__
