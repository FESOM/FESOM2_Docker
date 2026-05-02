#include "date.hpp"
#include "calendar.hpp"
#include "calendar_type.hpp"
#include "calendar_util.hpp"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::posix_time;
using namespace boost::gregorian;

namespace xios
{
      /// ////////////////////// Définitions ////////////////////// ///
      CDate::CDate(void)
        : relCalendar(NULL)
        , year(0), month(1),  day(1)
        , hour(0), minute(0), second(0)
      {}

      CDate::CDate(const CCalendar& calendar)
         : relCalendar(&calendar)
         , year(0), month(1),  day(1)
         , hour(0), minute(0), second(0)
      {}

      CDate::CDate(const CCalendar& calendar,
                   int yr, int mth, int d,
                   int hr, int min, int sec)
         : relCalendar(&calendar)
         , year(yr), month(mth),  day(d)
         , hour(hr), minute(min), second(sec)
      {
         if (!this->checkDate())
         {
            DEBUG(<< "La date initialisée a été modifiée "
                  << "car elle était incorrecte par rapport au calendrier souhaité.");
         }
      }

      CDate::CDate(const CDate& date)
        : relCalendar(date.relCalendar)
        , year(date.year), month(date.month),   day(date.day)
        , hour(date.hour), minute(date.minute), second(date.second)
      {
        // Delay the verification until we get a calendar we can compare the date to
        if (relCalendar && !checkDate())
        {
          DEBUG(<< "La date initialisée a été modifiée "
                << "car elle était incorrecte par rapport au calendrier souhaité.");
        }
      }

      CDate::~CDate(void)
      { /* Ne rien faire de plus */ }

      ///---------------------------------------------------------------

      CDate& CDate::operator=(const CDate& date)
      {
         relCalendar = date.relCalendar;
         year = date.year; month  = date.month; day    = date.day;
         hour = date.hour; minute = date.minute; second = date.second;
         return (*this);
      }

      bool CDate::operator==(const CDate& date)
      {         
         return (&(*relCalendar) == &(*date.relCalendar) &&
                 year == date.year && month  == date.month  && day == date.day &&
                 hour == date.hour && minute == date.minute && second == date.second);
         
      }

      StdOStream& operator<<(StdOStream& out, const CDate& date)
      {
        std::streamsize s;
        char c;

        int width=4;
        double maxSize=10000;
        while (date.year>=maxSize)
        {
          maxSize*=10;
          width++;
        }
        s = out.width(width); c = out.fill('0'); out << date.year << '-';

        s = out.width(2); c = out.fill('0'); out << date.month << '-';
        s = out.width(2); c = out.fill('0'); out << date.day << ' ';
        s = out.width(2); c = out.fill('0'); out << date.hour << ':';
        s = out.width(2); c = out.fill('0'); out << date.minute << ':';
        s = out.width(2); c = out.fill('0'); out << date.second;

        return out;
      }

      StdIStream& operator>>(StdIStream& in, CDate& date)
      {
        if (date.relCalendar)
          date.relCalendar->parseDate(in, date);
        else
          CCalendar::parseDateDefault(in, date);

        return in;
      }

      CDate::operator Time(void) const // Non vérifiée, pas optimisée ...
      {
        // This will check that a calendar was correctly associated to the date
        const CCalendar& c = getRelCalendar();

        // Todo : Tester si la date courante est supérieure à la date initiale.
        Time t = getSecondOfYear() - c.getTimeOrigin().getSecondOfYear();

        if (c.hasLeapYear())
        {
          for (CDate d(c.getTimeOrigin()); d.getYear() < getYear(); d.setYear(d.getYear() + 1))
            t += c.getYearTotalLength(d);
        }
        else
          t += Time(getYear() - c.getTimeOrigin().getYear()) * c.getYearTotalLength(*this);

        return t;
      }

      //----------------------------------------------------------------

      bool CDate::checkDate(void)
      {
        // This will also check that a calendar was correctly associated to the date
        return getRelCalendar().checkDate(*this);
      }

      //----------------------------------------------------------------

      int CDate::getYear  (void) const { return (this->year  ); }
      int CDate::getMonth (void) const { return (this->month ); }
      int CDate::getDay   (void) const { return (this->day   ); }
      int CDate::getHour  (void) const { return (this->hour  ); }
      int CDate::getMinute(void) const { return (this->minute); }
      int CDate::getSecond(void) const { return (this->second); }

      //----------------------------------------------------------------

      const CCalendar& CDate::getRelCalendar(void) const
      {
        if (!this->relCalendar)
          ERROR("const CCalendar& CDate::getRelCalendar(void) const",
                "Invalid state: The date is not associated with any calendar.");
        return (*this->relCalendar);
      }

      bool CDate::hasRelCalendar(void) const
      { return (this->relCalendar != NULL); }

      //----------------------------------------------------------------

      /*!
        Get the number of seconds since the beginning of the year.
        \return the number of seconds since the beginning of the year.
      */
      int CDate::getSecondOfYear() const
      {
        CDate yearStart(*this);
        const CCalendar& c = getRelCalendar();
        int nbDay = 0;

        for (yearStart.setMonth(1); yearStart.getMonth() < getMonth(); yearStart.setMonth(yearStart.getMonth() + 1))
          nbDay += c.getMonthLength(yearStart);

        // We need to use getDayLengthInSeconds instead of getDayLength since we might
        // have a non-integral number of hours per day for user defined calendars
        return ((nbDay + getDay() - 1) * c.getDayLengthInSeconds()
                  + (getHour() * c.getHourLength() + getMinute()) * c.getMinuteLength() + getSecond());
      }

      /*!
        Get the number of days (expressed as a real number) since the beginning of the year.
        \return the number of days (expressed as a real number) since the beginning of the year.
      */
      double CDate::getDayOfYear() const
      {
        return double(getSecondOfYear()) / getRelCalendar().getDayLengthInSeconds();
      }

      /*!
        Get the fraction of the current year as a real number between 0 and 1.
        \return the fraction of the current year.
      */
      double CDate::getFractionOfYear() const
      {
        return double(getSecondOfYear()) / getRelCalendar().getYearTotalLength(*this);
      }

      /*!
        Get the number of seconds since the beginning of the day.
        \return the number of seconds since the beginning of the day.
      */
      int CDate::getSecondOfDay() const
      {
        const CCalendar& c = getRelCalendar();
        return ((getHour() * c.getHourLength() + getMinute()) * c.getMinuteLength() + getSecond());
      }

      /*!
        Get the fraction of the current day as a real number between 0 and 1.
        \return the fraction of the current day.
      */
      double CDate::getFractionOfDay() const
      {
        return double(getSecondOfDay()) / getRelCalendar().getDayLengthInSeconds();
      }

      //----------------------------------------------------------------

      void CDate::setYear  (int newyear)   { this->year   = newyear; }
      void CDate::setMonth (int newmonth)  { this->month  = newmonth; }
      void CDate::setDay   (int newday)    { this->day    = newday; }
      void CDate::setHour  (int newhour)   { this->hour   = newhour; }
      void CDate::setMinute(int newminute) { this->minute = newminute; }
      void CDate::setSecond(int newsecond) { this->second = newsecond; }

      void CDate::setDate(int yr, int mth, int d, int hr, int min, int sec)
      {
        this->year   = yr;
        this->month  = mth;
        this->day    = d;
        this->hour   = hr;
        this->minute = min;
        this->second = sec;
      }

      //----------------------------------------------------------------

      void CDate::addMonth(int value)
      {// Value doit être égale à 1 ou -1.

        const CCalendar& c = getRelCalendar();
        int nbMonthsPerYear = c.getYearLength();

        this->month += value;

        if (this->month == nbMonthsPerYear + 1) { year++; this->month = 1; }
        if (this->month == 0)  { year--; this->month = nbMonthsPerYear; }
      }

      //----------------------------------------------------------------

      bool CDate::setRelCalendar(const CCalendar& relCalendar)
      {
        this->relCalendar = &relCalendar;
        return this->checkDate();
      }

      //----------------------------------------------------------------

      CDate CDate::FromString(const StdString& str, const CCalendar& calendar)
      {
        CDate dt(calendar);
        StdIStringStream iss(str);
        iss >> dt;
        return dt;
      }

      //----------------------------------------------------------------

      StdString CDate::getStryyyymmdd(void) const
      {
        std::streamsize s;
        char c;

        ostringstream oss;

        s = oss.width(4); c = oss.fill('0'); oss << year;
        s = oss.width(2); c = oss.fill('0'); oss << month;
        s = oss.width(2); c = oss.fill('0'); oss << day;

        return oss.str();
      }

      string CDate::getStr(const string& str) const
      {
        ostringstream oss;
        int level;

        level=0;
        for(string::const_iterator it=str.begin();it!=str.end();++it)
        {
          if (level==0)
          {
            if (*it=='%') level++;
            else oss<<*it;
          }
          else if (level==1)
          {
            switch (*it)
            {
              case 'y' :
                oss.width(4); oss.fill('0'); oss << year;
                level=0;
                break;
              case 'm' : // month or minute
                level++;
                break;
              case 'd' :
                oss.width(2); oss.fill('0'); oss << day;
                level=0;
                break;
              case 'h' :
                oss.width(2); oss.fill('0'); oss << hour;
                level=0;
                break;
              case 's' :
                oss.width(2); oss.fill('0'); oss << second;
                level=0;
                break;
              case 'S' : // seconds since time origin
                oss.width(0); oss << Time(*this);
                level=0;
                break;
              case 'D' : // days since time origin
                oss.width(0); oss << Time(*this) / getRelCalendar().getDayLengthInSeconds();
                level=0;
                break;
              default :
                oss<<'%'<<*it;
                level=0;
            }
          }
          else if (level==2)
          {
            switch (*it)
            {
              case 'o' : // month
                oss.width(2); oss.fill('0'); oss << month;
                level=0;
                break;
              case 'i' : //minute
                oss.width(2); oss.fill('0'); oss << minute;
                level=0;
                break;
              default :
                oss<<"%m"<<*it;
                level=0;
            }
          }
        }
        return oss.str();
      }

      StdString CDate::toString(void) const
      {
        StdOStringStream oss;
        oss << *this;
        return oss.str();
      }

      ///---------------------------------------------------------------

} // namespace xios
