#ifndef __XIOS_CBinaryArithmeticFilter__
#define __XIOS_CBinaryArithmeticFilter__

#include "filter.hpp"
#include <string>
#include "operator_expr.hpp"
#include <unordered_map>
#include <tuple>

namespace xios
{
  /*!
   * A generic binary arithmetic filter wrapping any type of binary scalar-field operator.
   */
  class CScalarFieldArithmeticFilter : public CFilter, public IFilterEngine
  {
    public:
      /*!
       * Constructs an binary scalar-field arithmetic filter wrapping the specified operator.
       *
       * \param gc the associated garbage collector
       * \param op the string identifing the binary scalar-field operator
       * \param value the scalar value
       */
      CScalarFieldArithmeticFilter(CGarbageCollector& gc, const std::string& op, double value);
      StdString virtual GetName(void);


    protected:
      COperatorExpr::functionScalarField op; //!< The binary scalar-field operator attached to the binary arithmeric filter
      double value; //!< The scalar value associated with the binary arithmeric filter

      /*!
       * Applies the binary scalar-field operator to the input data and returns the result.
       *
       * \param data a vector of packets corresponding to each slot (one in this case)
       * \return the result of the binary operation
       */
      CDataPacketPtr virtual apply(std::vector<CDataPacketPtr> data);
      std::tuple<int, int, int> virtual buildGraph(std::vector<CDataPacketPtr> data);
      

  }; // class CScalarFieldArithmeticFilter

  /*!
   * A generic binary arithmetic filter wrapping any type of binary scalar-field operator.
   */
  class CFieldScalarArithmeticFilter : public CFilter, public IFilterEngine
  {
    public:
      /*!
       * Constructs an binary field-scalar arithmetic filter wrapping the specified operator.
       *
       * \param gc the associated garbage collector
       * \param op the string identifing the binary field-scalar operator
       * \param value the scalar value
       */
      CFieldScalarArithmeticFilter(CGarbageCollector& gc, const std::string& op, double value);
      StdString virtual GetName(void);


    protected:
      COperatorExpr::functionFieldScalar op; //!< The binary field-scalar operator attached to the binary arithmeric filter
      double value; //!< The scalar value associated with the binary arithmeric filter

      /*!
       * Applies the binary field-scalar operator to the input data and returns the result.
       *
       * \param data a vector of packets corresponding to each slot (one in this case)
       * \return the result of the binary operation
       */
      CDataPacketPtr virtual apply(std::vector<CDataPacketPtr> data);
      std::tuple<int, int, int> virtual buildGraph(std::vector<CDataPacketPtr> data);
  }; // class CFieldScalarArithmeticFilter

  /*!
   * A generic binary arithmetic filter wrapping any type of binary scalar-field operator.
   */
  class CFieldFieldArithmeticFilter : public CFilter, public IFilterEngine
  {
    public:
      /*!
       * Constructs an binary field-field arithmetic filter wrapping the specified operator.
       *
       * \param gc the associated garbage collector
       * \param op the string identifing the binary field-field operator
       */
      CFieldFieldArithmeticFilter(CGarbageCollector& gc, const std::string& op);
      StdString virtual GetName(void);


    protected:
      COperatorExpr::functionFieldField op; //!< The binary field-field operator attached to the binary arithmeric filter

      /*!
       * Applies the binary field-field operator to the input data and returns the result.
       *
       * \param data a vector of packets corresponding to each slot (one in this case)
       * \return the result of the binary operation
       */
      CDataPacketPtr virtual apply(std::vector<CDataPacketPtr> data);
      std::tuple<int, int, int> virtual buildGraph(std::vector<CDataPacketPtr> data);
  }; // class CFieldFieldArithmeticFilter
} // namespace xios

#endif //__XIOS_CBinaryArithmeticFilter__
