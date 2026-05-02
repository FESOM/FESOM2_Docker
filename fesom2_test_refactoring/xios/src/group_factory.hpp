#ifndef __XIOS_CGroupFactory__
#define __XIOS_CGroupFactory__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "exception.hpp"
#include "object_factory.hpp"
#include "group_template.hpp"
#include "xml_parser.hpp"

namespace xios
{
   /// ////////////////////// Déclarations ////////////////////// ///
   class CGroupFactory
   {
      public :

         /// Mutateurs ///
         static void SetCurrentContextId(const StdString & context);

         template <typename U>
            static void AddGroup(std::shared_ptr<U> pgroup,
                                        std::shared_ptr<U> cgroup);

         template <typename U>
            static void AddChild(std::shared_ptr<U> group,
                                        std::shared_ptr<typename U::RelChild> child);

         /// Accesseurs ///
         static StdString & GetCurrentContextId(void);

         template <typename U>
            static std::shared_ptr<U>
               GetGroup(std::shared_ptr<U> group, const StdString & id);

         template <typename U>
            static std::shared_ptr<typename U::RelChild>
               GetChild(std::shared_ptr<U> group, const StdString & id);

         template <typename U>
            static int GetGroupNum(std::shared_ptr<U> group);
         template <typename U>
            static int GetGroupIdNum(std::shared_ptr<U> group);
         template <typename U>
            static int GetChildNum(std::shared_ptr<U> group);
         template <typename U>
            static int GetChildIdNum(std::shared_ptr<U> group);

         /// Tests ///
         template <typename U>
            static bool HasGroup(std::shared_ptr<U> group, const StdString & id);

         template <typename U>
            static bool HasChild(std::shared_ptr<U> group, const StdString & id);

         /// Instanciateur ///
         template <typename U>
            static std::shared_ptr<U>
               CreateGroup(std::shared_ptr<U> group, const StdString & id = StdString(""));

         template <typename U>
            static std::shared_ptr<typename U::RelChild>
               CreateChild(std::shared_ptr<U> group, const StdString & id = StdString(""));

      private :

         /// Propriétés statiques ///
         static StdString CurrContext;

   }; // class CGroupFactory
} // namespace xios

//#include "group_factory_impl.hpp"
//#include "group_parser.hpp"

#endif // __XIOS_CGroupFactory__
