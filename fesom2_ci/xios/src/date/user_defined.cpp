#include "user_defined.hpp"
#include "calendar_util.hpp"

namespace xios
{
  /// ////////////////////// Définitions ////////////////////// ///

  CUserDefinedCalendar::CUserDefinedCalendar(int dayLength, const CArray<int,1>& monthLengths)
    : CCalendar("user_defined")
    , dayLength(dayLength)
    , monthLengths(monthLengths)
    , yearLength(sum(monthLengths) * dayLength)
    , leapYearMonth(0)
    , leapYearDrift(0.0)
    , leapYearDriftOffset(0.0)
  {
    if (dayLength <= 0)
      ERROR("CUserDefinedCalendar::CUserDefinedCalendar(int dayLength, const CArray<int,1>& monthLengths)",
            << "The day length must be strictly positive.");
    if (monthLengths.numElements() == 0)
      ERROR("CUserDefinedCalendar::CUserDefinedCalendar(int dayLength, const CArray<int,1>& monthLengths)",
            << "The month lengths must be specified.");
    if (min(monthLengths) <= 0)
      ERROR("CUserDefinedCalendar::CUserDefinedCalendar(int dayLength, const CArray<int,1>& monthLengths)",
            << "All month lengths must be strictly positive.");
    // Ensure that the month lengths array is always 0-indexed
    this->monthLengths.reindexSelf(TinyVector<int, 1>(0));
  }

  CUserDefinedCalendar::CUserDefinedCalendar(int dayLength, int yearLength)
    : CCalendar("user_defined")
    , dayLength(dayLength)
    , yearLength(yearLength)
    , leapYearMonth(0)
    , leapYearDrift(0.0)
    , leapYearDriftOffset(0.0)
  {
    if (dayLength <= 0)
      ERROR("CUserDefinedCalendar::CUserDefinedCalendar(int dayLength, int yearLength)",
            << "The day length must be strictly positive.");
    if (yearLength <= 0)
      ERROR("CUserDefinedCalendar::CUserDefinedCalendar(int dayLength, int yearLength)",
            << "The year length must be strictly positive.");
  }

  CUserDefinedCalendar::~CUserDefinedCalendar(void)
  { /* Nothing to do here */ }

  ///--------------------------------------------------------------

  void CUserDefinedCalendar::configureLeapYear(int leapYearMonth, double leapYearDrift, double leapYearDriftOffset /*= 0.0*/)
  {
    if (monthLengths.numElements() == 0)
      ERROR("void CUserDefinedCalendar::configureLeapYear(int leapYearMonth, double leapYearDrift, double leapYearDriftOffset /*= 0.0*/)",
            << "Impossible to define leap years on a calendar without months.");
    if (leapYearMonth < 1 || leapYearMonth > monthLengths.numElements())
      ERROR("void CUserDefinedCalendar::configureLeapYear(int leapYearMonth, double leapYearDrift, double leapYearDriftOffset /*= 0.0*/)",
            << "The month chosen for the additional day must be in the range [1, " << monthLengths.numElements() << "].");
    if (leapYearDrift < 0.0 || leapYearDrift >= 1.0)
      ERROR("void CUserDefinedCalendar::configureLeapYear(int leapYearMonth, double leapYearDrift, double leapYearDriftOffset /*= 0.0*/)",
            << "The year drift must be in the range [0.0, 1.0).");
    if (leapYearDriftOffset < 0.0 || leapYearDriftOffset >= 1.0)
      ERROR("void CUserDefinedCalendar::configureLeapYear(int leapYearMonth, double leapYearDrift, double leapYearDriftOffset /*= 0.0*/)",
            << "The year drift offset must be in the range [0.0, 1.0).");

    this->leapYearMonth = leapYearMonth;
    this->leapYearDrift = leapYearDrift;
    this->leapYearDriftOffset = leapYearDriftOffset;
  }

  ///--------------------------------------------------------------

  StdString CUserDefinedCalendar::getType(void) const { return StdString("user_defined"); }

  /*! Returns the duration of the date's month in days. */
  int CUserDefinedCalendar::getMonthLength(const CDate& date) const
  {
    int monthLength = 0;
    if (monthLengths.numElements() > 0)
    {
      monthLength = monthLengths(date.getMonth() - 1);
      if (date.getMonth() == leapYearMonth && isLeapYear(date.getYear()))
        monthLength++;
    }
    return monthLength;
  }

  /*! Returns the duration of the date's year in seconds. */
  int CUserDefinedCalendar::getYearTotalLength(const CDate& date) const
  {
    return isLeapYear(date.getYear()) ? yearLength + dayLength : yearLength;
  }

  /*! Returns the duration of a day in hours. Note that this value is
      not necessarily exact since it can be rounded but it is always
      the smallest integer number of hours that can hold a day. */
  int CUserDefinedCalendar::getDayLength(void) const { return int(ceil(double(dayLength) / (getHourLength() * getMinuteLength()))); }

  /*! Returns the duration of a year in months. */
  int CUserDefinedCalendar::getYearLength(void) const { return monthLengths.numElements(); }

  /*! Returns the day length expressed in seconds. */
  int CUserDefinedCalendar::getDayLengthInSeconds(void) const { return dayLength; }

  /*! Test if the calendar can have leap year. */
  bool CUserDefinedCalendar::hasLeapYear() const{ return (leapYearDrift != 0.0); }

  /*!
    Test if the specified year is a leap year.
    \param year the year to be tested
    \return true if and only the specified year is a leap year
  */
  bool CUserDefinedCalendar::isLeapYear(int year) const
  {
    double intPart; // dummy variable
    return (hasLeapYear() &&
            (abs(1.0 - (modf(leapYearDriftOffset + (year - getTimeOrigin().getYear()) * leapYearDrift, &intPart) + leapYearDrift)) < 1e-14));
  }

  CDuration& CUserDefinedCalendar::resolve(CDuration& dur, bool noNegativeTime /*= false*/) const
  {
    if (monthLengths.numElements() > 0) // normal case, we can rely on the generic function
      return CCalendar::resolve(dur, noNegativeTime);

    if (dur.month)
      ERROR("CDuration& CUserDefinedCalendar::resolve(CDuration& dur, bool noNegativeTime /*= false*/) const",
            << "month = " << dur.month << " but the user defined calendar has no month.");

    const int hourLengthInSeconds = getHourLength() * getMinuteLength();

    // Convert everything in seconds
    Time t = Time(dur.year * yearLength + dur.day * dayLength
                    + (dur.hour * getHourLength() + dur.minute) * getMinuteLength() + dur.second);

    // Then convert back to years
    dur.year = int(t / yearLength);
    t %= yearLength;

    // days
    dur.day = int(t / dayLength);
    t %= dayLength;

    // Do we allow hour, minute, second to be negative?
    if (noNegativeTime)
    {
      // If we don't, we remove some days or years until the time is positive
      double& val = (dayLength < yearLength) ? dur.day : dur.year;
      int length  = (dayLength < yearLength) ? dayLength : yearLength;
      while (t < 0)
      {
        t += length;
        val -= 1.0;
      }
    }

    // hours
    dur.hour = int(t / hourLengthInSeconds);
    t %= hourLengthInSeconds;
    // minutes
    dur.minute = int(t / getMinuteLength());
    // secondes
    dur.second = int(t % getMinuteLength());

    return dur;
  }

  /*! Parse a date using the calendar's parser. */
  void CUserDefinedCalendar::parseDate(StdIStream& in, CDate& date) const
  {
    if (monthLengths.numElements() > 0) // normal case, we can rely on the generic function
    {
      CCalendar::parseDate(in, date);
      return;
    }

    char sep = '-'; // Le caractère c est utilisé pour "recueillir" les séparateurs "/" et ":".
    char c;

    // Default initialize the date
    int year = 00, month  = 01, day    = 01;
    int hour = 00, minute = 00, second = 00;

    // Read the year
    in >> year;
    // Read the day only if the day length is smaller than the year length
    c = in.get();
    if (c == sep && dayLength < yearLength)
    {
      in >> day;
      c = in.get();
    }
    // Read the time
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

    date.setDate(year, month, day, hour, minute, second);

    // Delay the verification until we get a calendar we can compare the date to
    if (!checkDate(date))
      ERROR("void CUserDefinedCalendar::parseDate(StdIStream& in, CDate& date) const",
            << "Bad date format or not conform to calendar");

    if (c == '+') // We will be adding a duration to the date
    {
      CDuration dur;
      in >> dur;
      date = date + dur;
    }
    else if (!in.eof())
      ERROR("void CUserDefinedCalendar::parseDate(StdIStream& in, CDate& date) const",
            << "Invalid date format: unexpected trailing character(s)");
  }

  /*! Test if a date is valid with regard to the current calendar. */
  bool CUserDefinedCalendar::checkDate(CDate& date) const
  {
    if (monthLengths.numElements() > 0) // normal case, we can rely on the generic function
      return CCalendar::checkDate(date);

    const int maxDay = (yearLength + dayLength - 1) / dayLength;

    bool isValid = true;

    // Vérification de la valeur du mois.
    if (date.getMonth() != 1)
    { isValid = false; date.setMonth(1); }

    // Vérification de la valeur du jour.
    if (date.getDay() < 1)
    { isValid = false; date.setDay(1); }
    else if (date.getDay() > maxDay)
    { isValid = false; date.setDay(maxDay); }

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

