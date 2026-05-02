#ifndef __XIOS_CUnaryArithmeticFilter__
#define __XIOS_CUnaryArithmeticFilter__

#include "filter.hpp"
#include <string>
#include "operator_expr.hpp"

namespace xios
{
  /*!
   * A generic unary arithmetic filter wrapping any type of unary operator
   * which can be applied on fields.
   */
  class CUnaryArithmeticFilter : public CFilter, public IFilterEngine
  {
    public:
      /*!
       * Constructs an unary arithmetic filter wrapping the specified operator.
       *
       * \param gc the associated garbage collector
       * \param op the string identifing the unary operator
       */
      CUnaryArithmeticFilter(CGarbageCollector& gc, const std::string& op);

    protected:
      COperatorExpr::functionField op; //!< The unary operator attached to the unary arithmeric filter


      /*!
       * Applies the unary operator to the input data and returns the result.
       *
       * \param data a vector of packets corresponding to each slot (one in this case)
       * \return the result of the unary operation
       */
      CDataPacketPtr virtual apply(std::vector<CDataPacketPtr> data);
      std::tuple<int, int, int> virtual buildGraph(std::vector<CDataPacketPtr> data);
  }; // class CUnaryArithmeticFilter
} // namespace xios

#endif //__XIOS_CUnaryArithmeticFilter__
