#include "calendar.hpp"
#include "duration.hpp"
#include "date.hpp"
#include "calendar_util.hpp"

namespace xios
{
      /// ////////////////////// Définitions ////////////////////// ///
      CCalendar::CCalendar(void)
         : CObject()
         , step(0)
         , initDate(*this)
         , timeOrigin(*this)
         , currentDate(*this)
      {}

      CCalendar::CCalendar(const StdString& id)
               : CObject(id)
               , step(0)
               , initDate(*this)
               , timeOrigin(*this)
               , currentDate(*this)
      {}

      CCalendar::CCalendar(const StdString& id,
                           int yr, int mth, int d,
                           int hr /*= 0*/, int min /*= 0*/, int sec /*= 0*/)
               : CObject(id)
               , step(0)
               , initDate(*this)
               , timeOrigin(*this)
               , currentDate(*this)
      {
        initializeDate(yr, mth, d, hr, min, sec);
      }

      CCalendar::CCalendar(const StdString& id, const CDate& startDate)
               : CObject(id)
               , step(0)
               , initDate(startDate)
               , timeOrigin(startDate)
               , currentDate(startDate)
      {
        // Initialize the dates only in the derivated classes
        // since we want to use the overloaded virtual functions
      }

      CCalendar::CCalendar(const StdString& id, const CDate& startDate, const CDate& timeOrigin)
               : CObject(id)
               , step(0)
               , initDate(startDate)
               , timeOrigin(timeOrigin)
               , currentDate(startDate)
      {
        // Initialize the dates only in the derivated classes
        // since we want to use the overloaded virtual functions
      }

      void CCalendar::initializeDate()
      {
        if (!initDate.setRelCalendar(*this))
          ERROR("CCalendar::initializeDate()",
                "initDate: Bad format or date not conform to the calendar");
        if (!timeOrigin.setRelCalendar(*this))
          ERROR("CCalendar::initializeDate()",
                "timeOrigin: Bad format or date not conform to the calendar");
        if (!currentDate.setRelCalendar(*this))
          ERROR("CCalendar::initializeDate()",
                "currentDate: Bad format or date not conform to the calendar");
      }

      void CCalendar::initializeDate(int yr, int mth, int d,
                                     int hr /*= 0*/, int min /*= 0*/, int sec /*= 0*/)
      {
        initDate = CDate(*this, yr, mth, d, hr, min, sec);
        timeOrigin = initDate;
        currentDate = initDate;
      }

      void CCalendar::initializeDate(const StdString& dateStr)
      {
        initDate = CDate::FromString(dateStr, *this);
        timeOrigin = initDate;
        currentDate = initDate;
      }

      void CCalendar::initializeDate(const StdString& dateStr, const StdString& timeOriginStr)
      {
        initDate = CDate::FromString(dateStr, *this);
        timeOrigin = CDate::FromString(timeOriginStr, *this);
        currentDate = initDate;
      }

      CCalendar::~CCalendar(void)
      { /* Ne rien faire de plus */ }

      ///---------------------------------------------------------------

      StdString CCalendar::toString(void) const
      {
         StdOStringStream oss;
         oss <<   "[type: "   << this->getId()
             << ", start: "   << this->initDate
             << ", current: " << this->currentDate << "]";
         return (oss.str());
      }

      void CCalendar::fromString(const StdString& str)
      { ERROR("CCalendar::fromString(str)",
               << "[ str = " << str << "] Not implemented yet !"); }

      //-----------------------------------------------------------------

      void CCalendar::setTimeStep(const CDuration& timestep)
      {
        if (timestep.timestep)
          ERROR("CCalendar::setTimeStep(const CDuration& timestep)",
                << "Circular definition of the timestep: the timestep cannot refer to itself.");
        this->timestep = timestep;
      }

      int CCalendar::getStep(void) const
      {
        return step;
      }

      const CDate& CCalendar::update(int step)
      {
        info(20) << "update step : " << step << " timestep " << this->timestep << std::endl;
        this->step = step;
        return (this->currentDate = this->getInitDate() + step * this->timestep);
      }

      //-----------------------------------------------------------------

      void CCalendar::setInitDate(const CDate& initDate)
      {
        if (&initDate.getRelCalendar() != this)
          ERROR("CCalendar::setInitDate(const CDate& initDate)",
                << "The init date cannot be attached to another calendar.");
        this->initDate = initDate;
      }

      void CCalendar::setTimeOrigin(const CDate& timeOrigin)
      {
        if (&timeOrigin.getRelCalendar() != this)
          ERROR("CCalendar::setInitDate(const CDate& timeOrigin)",
                << "The time origin cannot be attached to another calendar.");
        this->timeOrigin = timeOrigin;
      }

      //-----------------------------------------------------------------

      const CDuration& CCalendar::getTimeStep(void) const { return this->timestep; }
      const CDate& CCalendar::getInitDate(void) const     { return this->initDate; }
      const CDate& CCalendar::getTimeOrigin(void) const   { return this->timeOrigin; }
      const CDate& CCalendar::getCurrentDate(void) const  { return this->currentDate; }

      //-----------------------------------------------------------------

      int CCalendar::getMonthLength(const CDate& date) const
      { // Retourne la durée du mois en jour.
        static const int NoLeapMonthLength[] =
          { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        return NoLeapMonthLength[date.getMonth() - 1];
      }

      StdString CCalendar::getType(void) const { return StdString(this->getId()); }

      int CCalendar::getYearTotalLength(const CDate& date) const { return (365 * 86400); }

      int CCalendar::getYearLength  (void) const { return 12; }
      int CCalendar::getDayLength   (void) const { return 24; }
      int CCalendar::getHourLength  (void) const { return 60; }
      int CCalendar::getMinuteLength(void) const { return 60; }
      int CCalendar::getDayLengthInSeconds(void) const { return getDayLength() * getHourLength() * getMinuteLength(); }

      bool CCalendar::hasLeapYear() const { return false; }

      StdString CCalendar::getMonthName(int monthId) const
      {
        static const StdString MonthNames[] =
          { "january", "february", "march",     "april" ,  "may",      "june",
            "july",    "august",   "september", "october", "november", "december" };
        return MonthNames[monthId - 1];
      }

      const StdString CCalendar::getMonthShortName(int monthId) const
      { StdString value = this->getMonthName(monthId); value.resize(3); return value; }

      CDuration& CCalendar::resolve(CDuration& dur, bool noNegativeTime /*= false*/) const
      {
        const int hourLengthInSeconds = getHourLength() * getMinuteLength();

        // Simplify the days, hours, minutes and seconds.
        // First convert them to seconds
        Time t = Time(modf(dur.day, &dur.day) * getDayLengthInSeconds()
                        + (dur.hour * getHourLength() + dur.minute) * getMinuteLength() + dur.second);
        // Then convert back to days
        dur.day += int(t / getDayLengthInSeconds());
        t %= getDayLengthInSeconds();

        // Do we allow hour, minute, second to be negative?
        if (noNegativeTime)
        {
          // If we don't, we remove some days until the time is positive
          while (t < 0)
          {
            t += getDayLengthInSeconds();
            dur.day -= 1.0;
          }
        }

        // hours
        dur.hour = int(t / hourLengthInSeconds);
        t %= hourLengthInSeconds;
        // minutes
        dur.minute = int(t / getMinuteLength());
        // secondes
        dur.second = int(t % getMinuteLength());

        // Nothing to do for the months yet since this depends on an actual date

        // Simplify the years
        dur.month  += modf(dur.year, &dur.year) * getYearLength();
        dur.year   += int(dur.month) / getYearLength(); dur.month = int(dur.month) % getYearLength();

        return dur;
      }

      /*! Parse a date using a generic parser. */
      void CCalendar::parseDateDefault(StdIStream& in, CDate& date)
      {
        char sep = '-'; // Le caractère c est utilisé pour "recueillir" les séparateurs "/" et ":".
        char c;

        // Default initialize the date
        int year = 00, month  = 01, day    = 01;
        int hour = 00, minute = 00, second = 00;

        in >> year >> c;
        if (c == sep)
        {
          in >> month >> c;
          if (c == sep)
          {
            in >> day;
            c = in.get();
            sep = ' ';
            if (c == sep)
            {
              in >> hour >> c;
              sep = ':';
              if (c == sep)
              {
                in >> minute >> c;
                if (c == sep)
                {
                  in >> second;
                  in >> c;
                }
              }
            }
          }
        }

        date.setDate(year, month, day, hour, minute, second);

        // Delay the verification until we get a calendar we can compare the date to
        if (date.hasRelCalendar() && !date.checkDate())
          ERROR("void parseDateDefault(StdIStream& in, CDate& date)",
                << "Bad date format or not conform to calendar");

        if (c == '+') // We will be adding a duration to the date
        {
          CDuration dur;
          in >> dur;
          date = date + dur;
        }
        else if (!in.eof())
          ERROR("void parseDateDefault(StdIStream& in, CDate& date)",
                << "Invalid date format: unexpected trailing character(s)");
      }

      /*! Parse a date using the calendar's parser. */
      void CCalendar::parseDate(StdIStream& in, CDate& date) const
      {
        parseDateDefault(in, date);
      }

      /*! Test if a date is valid with regard to the current calendar. */
      bool CCalendar::checkDate(CDate& date) const
      {
        bool isValid = true;

        // Vérification de la valeur du mois.
        if (date.getMonth() < 1)
        { isValid = false; date.setMonth(1); }
        else if (date.getMonth() > getYearLength())
        { isValid = false; date.setMonth(getYearLength()); }

        // Vérification de la valeur du jour.
        if (date.getDay() < 1)
        { isValid = false; date.setDay(1); }
        else if (date.getDay() > getMonthLength(*this))
        { isValid = false; date.setDay(getMonthLength(*this)); }

        // Vérification de la valeur de l'heure.
        if (date.getHour() < 0)
        { isValid = false; date.setHour(0); }
        else if (date.getHour() >= getDayLength())
        { isValid = false; date.setHour(getDayLength() - 1); }

        // Vérification de la valeur des minutes.
        if (date.getMinute() < 0)
        { isValid = false; date.setMinute(0); }
        else if (date.getMinute() >= getHourLength())
        { isValid = false; date.setMinute(getHourLength() - 1); }

        // Vérification de la valeur des secondes.
        if (date.getSecond() < 0)
        { isValid = false; date.setSecond(0); }
        else if (date.getSecond() >= getMinuteLength())
        { isValid = false; date.setSecond(getMinuteLength() - 1); }

        return isValid;
      }
} // namespace xios
