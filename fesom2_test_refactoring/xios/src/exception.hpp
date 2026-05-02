#ifndef __XIOS_CException__
#define __XIOS_CException__

/// XIOS headers ///
#include "xios_spl.hpp"
#include "object.hpp"
#include <iomanip>
#include <stdexcept>

namespace xios
{
   /// ////////////////////// Déclarations ////////////////////// ///

   class CException
      : private CObject, public StdOStringStream
   {
         typedef CObject SuperClass;

      public :

         /// Constructeurs ///
         CException(void);
         explicit CException(const StdString & id);
         CException(const CException & exception);
         CException(const CException * const exception); // Not implemented.

         /// Accesseurs ///
         StdString getMessage(void) const;
         StdOStringStream & getStream(void);

         /// Destructeur ///
         virtual ~CException(void);

         /// Autre ///
         virtual StdString toString(void) const;
         virtual void fromString(const StdString & str);

         struct StackInfo
         {
           StdString file;
           StdString function;
           int line;
           StdString info;
         };

         std::list<StackInfo> stack;

      private :

         /// Propriétés ///
         bool desc_rethrow; // throw destructor
         StdOStringStream stream;

   }; // CException
} // namespace xios

/// //////////////////////////// Macros //////////////////////////// ///

#define FILE_NAME (std::strrchr("/" __FILE__, '/') + 1)

#define FUNCTION_NAME (StdString(BOOST_CURRENT_FUNCTION).length() > 100 ? \
                       StdString(BOOST_CURRENT_FUNCTION).substr(0,100).append("...)") : BOOST_CURRENT_FUNCTION)

#define INFO(x) \
   "In file \""<< FILE_NAME <<"\", function \"" << BOOST_CURRENT_FUNCTION <<"\",  line " << __LINE__ << " -> " x << std::endl;

#ifdef __XIOS_DEBUG
#  define DEBUG(x) std::clog << "> Debug " << INFO(x)
#else
#  define DEBUG(x)
#endif

#define ERROR(id, x)  \
{                     \
       xios::CException exc(id);                \
       exc.getStream() << INFO(x);              \
       error << exc.getMessage() << std::endl;  \
       throw exc;                               \
}

#ifdef __XIOS_EXCEPTION
  #define TRY                          \
    {                                  \
      int funcFirstLine = __LINE__;    \
      try
  #define CATCH                              \
      catch(CException& e)                   \
      {                                      \
        CException::StackInfo stk;           \
        stk.file = FILE_NAME;                \
        stk.function = FUNCTION_NAME;        \
        stk.line = funcFirstLine;            \
        e.stack.push_back(stk);              \
        if (CXios::xiosStack)                \
          throw;                             \
       else                                  \
         throw 0;                            \
      }                                      \
    }
  #define CATCH_DUMP_ATTR                    \
      catch(CException& e)                   \
      {                                      \
        CException::StackInfo stk;           \
        stk.info.append(StdString("Object id=\"" + this->getId()) + "\" object type=\"" + this->getName() + "\"\n"); \
        stk.info.append("*** XIOS attributes as defined in XML file(s) or via Fortran interface:\n");                \
        stk.info.append("[" + this->dumpXiosAttributes() + "]\n");     \
        stk.info.append("*** Additional information:\n");              \
        stk.info.append("[" + this->dumpClassAttributes() + "]\n");    \
        stk.file = FILE_NAME;                \
        stk.function = FUNCTION_NAME;        \
        stk.line = funcFirstLine;            \
        e.stack.push_back(stk);              \
        if (CXios::xiosStack)                \
          throw;                             \
       else                                  \
         throw 0;                            \
      }                                      \
    }
  #define CATCH_DUMP_STACK                                           \
      catch(CException& e)                                           \
      {                                                              \
        CException::StackInfo stk;                                   \
        int i = 1;                                                   \
        stk.file = FILE_NAME;                                        \
        stk.function = FUNCTION_NAME;                                \
        stk.line = funcFirstLine;                                    \
        e.stack.push_back(stk);                                      \
        for (auto itr = e.stack.crbegin(); itr!=e.stack.crend(); ++itr) \
        {                                                            \
          error << "("<< i <<") **************** ";                  \
          error << itr->function << std::endl;                       \
          error << itr->info << std::endl;                           \
          ++i;                                                       \
        }                                                            \
        error << left << "      ";                                   \
        error << left << std::setw(40) << "File " ;                  \
        error << left << std::setw(106) << "Function " ;             \
        error << std::setw(5)   << "Line " << std::endl;             \
        i = e.stack.size();                                          \
        for (auto itr = e.stack.begin(); itr!=e.stack.end(); itr++)  \
        {                                                            \
          StdOStringStream tmp;                                      \
          tmp <<  "("<< i <<")";                                     \
          error << left << std::setw(6) << tmp.str();                \
          error << left << std::setw(40)  << itr->file;              \
          error << left << std::setw(106) << itr->function;          \
          error << left << std::setw(5)   << itr->line << std::endl; \
          --i;                                                       \
        }                                                            \
        throw;                                                       \
      }                                                              \
    }
#else
  #define TRY
  #define CATCH
  #define CATCH_DUMP_ATTR
  #define CATCH_DUMP_STACK
#endif

#endif // __XIOS_CException__

