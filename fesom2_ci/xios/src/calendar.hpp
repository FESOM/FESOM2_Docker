#ifndef __XIOS_CCalendar__
#define __XIOS_CCalendar__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "exception.hpp"
#include "date.hpp"

namespace xios
{
      /// ////////////////////// Déclarations ////////////////////// ///

      typedef enum _monthEnum
      {  JAN = 1, FEB = 2, MAR = 3, APR = 4 , MAY = 5 , JUN = 6 ,
         JUL = 7, AUG = 8, SEP = 9, OCT = 10, NOV = 11, DEC = 12  } MonthEnum;

      ///---------------------------------------------------------------

      class CDate;

      class CCalendar : public CObject
      {
            /// Typedef ///
            typedef CObject SuperClass;

         public :

            /// Destructeur ///
            virtual ~CCalendar(void);

         protected :

            /// Constructeurs ///
            CCalendar(void);
            CCalendar(const StdString& id);
            CCalendar(const StdString& id,
                      int yr, int mth, int d,
                      int hr = 0, int min = 0, int sec = 0);
            CCalendar(const StdString& id, const CDate& startDate);
            CCalendar(const StdString& id, const CDate& startDate, const CDate& timeOrigin);

            CCalendar(const CCalendar& calendar);       // Not implemented yet.
            CCalendar(const CCalendar* const calendar); // Not implemented yet.

         public :

            //------------------------------------------------------------

            /// Autres ///
            virtual StdString toString(void) const;
            virtual void fromString(const StdString& str);

            /// Mutateur ///
            void setTimeStep(const CDuration& timestep);
            void setInitDate(const CDate& initDate);
            void setTimeOrigin(const CDate& timeOrigin);

            /// Traitemants ///
            const CDate& update(int step);

            /// Accesseurs ///
            const CDuration& getTimeStep(void) const;
            const CDate& getInitDate(void) const;
            const CDate& getTimeOrigin(void) const;
            const CDate& getCurrentDate(void) const;

         public :

            //------------------------------------------------------------
            virtual StdString getType(void) const;

            int getStep(void) const;

            virtual int getMonthLength(const CDate& date) const;

            virtual int getYearTotalLength(const CDate& date) const; // Retourne la durée d'une année en seconde.

            virtual int getYearLength  (void) const; // Retourne la durée d'une année en mois.
            virtual int getDayLength   (void) const; // Retourne la durée d'un jour en heures.
            virtual int getHourLength  (void) const; // Retourne la durée d'une heure en minute.
            virtual int getMinuteLength(void) const; // Retourne la durée d'une minute en secondes.
            /*! Returns the day length expressed in seconds. */
            virtual int getDayLengthInSeconds(void) const;

            virtual StdString getMonthName(int monthId) const;
            virtual const StdString getMonthShortName(int monthId) const;

            /*! Test if the calendar can have leap year. */
            virtual bool hasLeapYear() const;

            void initializeDate(int yr, int mth, int d, int hr = 0, int min = 0, int sec = 0);
            void initializeDate(const StdString& dateStr);
            void initializeDate(const StdString& dateStr, const StdString& timeOrigin);

            /*! Simplify a duration based on the calendar information. */
            virtual CDuration& resolve(CDuration& dur, bool noNegativeTime = false) const;

            /*! Parse a date using a generic parser. */
            static void parseDateDefault(StdIStream& in, CDate& date);
            /*! Parse a date using the calendar's parser. */
            virtual void parseDate(StdIStream& in, CDate& date) const;

            /*! Test if a date is valid with regard to the current calendar. */
            virtual bool checkDate(CDate& date) const;

            //------------------------------------------------------------

         protected:

            //!< Associate the dates to the calendar and check their validity
            void initializeDate();

            //------------------------------------------------------------

         private :
            int step;

            /// Propriétés privées ///
            CDate initDate;
            CDate timeOrigin;
            CDate currentDate;
            CDuration timestep;

      }; // class CCalendar

} // namespace xios

#endif // __XIOS_CCalendar__
