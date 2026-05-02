#ifndef __XIOS_CCalendarWrapper__
#define __XIOS_CCalendarWrapper__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "attribute_enum.hpp"
#include "attribute_enum_impl.hpp"
#include "attribute_array.hpp"
#include "declare_attribute.hpp"
#include "object_template.hpp"

#include "calendar.hpp"

namespace xios {

  /// ////////////////////// Déclarations ////////////////////// ///
  class CCalendarWrapperAttributes;
  class CCalendarWrapper;
  ///--------------------------------------------------------------

  // Declare/Define CFileAttribute
  BEGIN_DECLARE_ATTRIBUTE_MAP(CCalendarWrapper)
#include "calendar_wrapper_attribute.conf"
  END_DECLARE_ATTRIBUTE_MAP(CCalendarWrapper)

  ///--------------------------------------------------------------
  /*!
    \class CCalendarWrapper
    This class a simple wrapper for the calendar
  */
  class CCalendarWrapper
    : public CObjectTemplate<CCalendarWrapper>
    , public CCalendarWrapperAttributes
  {
    public :

      /// typedef ///
      typedef CObjectTemplate<CCalendarWrapper> SuperClass;
      typedef CCalendarWrapperAttributes SuperClassAttribute;

      //---------------------------------------------------------

    public :

      /// Constructeurs ///
      CCalendarWrapper(void);
      explicit CCalendarWrapper(const StdString& id);

      /// Destructeur ///
      virtual ~CCalendarWrapper(void);

      /// Accesseurs statiques ///
      static StdString GetName(void);
      static StdString GetDefName(void);
      static ENodeType GetType(void);

      //---------------------------------------------------------

    public :
      // Parse xml calendar node
      virtual void parse(xml::CXMLNode& node);
      // Try to create the calendar from the current attributes
      void createCalendar(void);
      // Try to update the timestep of the calendar with the corresponding attribute
      void updateTimestep(void);

    public :
      /// Accesseurs ///
      std::shared_ptr<CCalendar> getCalendar(bool checkValid = false) const;

      const CDate& getInitDate() const;
      const CDate& getTimeOrigin() const;

      /// Mutateurs ///
      void setInitDate(const CDate& initDate);
      void setTimeOrigin(const CDate& timeOrigin);

    private:
      // Calendar of context
      std::shared_ptr<CCalendar> calendar;

  }; // class CCalendarWrapper

  typedef CCalendarWrapper CCalendarWrapperDefinition;
} // namespace xios

#endif // __XIOS_CCalendarWrapper__
