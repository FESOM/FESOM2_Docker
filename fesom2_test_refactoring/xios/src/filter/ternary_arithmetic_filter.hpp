#ifndef __XIOS_CTernaryArithmeticFilter__
#define __XIOS_CTernaryArithmeticFilter__

#include "filter.hpp"
#include <string>
#include "operator_expr.hpp"
#include <tuple>

namespace xios
{
  /*!
   * A generic ternary arithmetic filter wrapping any type of ternary scalar-scalar-field operator.
   */
  class CScalarScalarFieldArithmeticFilter : public CFilter, public IFilterEngine
  {
    public:
      /*!
       * Constructs an ternary scalar-field arithmetic filter wrapping the specified operator.
       *
       * \param gc the associated garbage collector
       * \param op the string identifing the ternary scalar-scalar-field operator
       * \param value1 the scalar value
       * \param value2 the scalar value
       */
      CScalarScalarFieldArithmeticFilter(CGarbageCollector& gc, const std::string& op, double value1, double value2);

    protected:
      COperatorExpr::functionScalarScalarField op; //!< The ternary scalar-scalar-field operator attached to the ternary arithmeric filter
      double value1; //!< The scalar value 1 associated with the ternary arithmeric filter
      double value2; //!< The scalar value 2 associated with the ternary arithmeric filter

      /*!
       * Applies the ternary scalar-scalar-field operator to the input data and returns the result.
       *
       * \param data a vector of packets corresponding to each slot (one in this case)
       * \return the result of the ternary operation
       */
      CDataPacketPtr virtual apply(std::vector<CDataPacketPtr> data);
      std::tuple<int, int, int> virtual buildGraph(std::vector<CDataPacketPtr> data);
  }; // class CScalarScalarFieldArithmeticFilter

 
   /*!
   * A generic ternary arithmetic filter wrapping any type of ternary scalar-field-scalar operator.
   */
  class CScalarFieldScalarArithmeticFilter : public CFilter, public IFilterEngine
  {
    public:
      /*!
       * Constructs an ternary scalar-field arithmetic filter wrapping the specified operator.
       *
       * \param gc the associated garbage collector
       * \param op the string identifing the ternary scalar-field-scalar operator
       * \param value1 the scalar value
       * \param value2 the scalar value
       */
      CScalarFieldScalarArithmeticFilter(CGarbageCollector& gc, const std::string& op, double value1, double value2);

    protected:
      COperatorExpr::functionScalarFieldScalar op; //!< The ternary scalar-field-scalar operator attached to the ternary arithmeric filter
      double value1; //!< The scalar value 1 associated with the ternary arithmeric filter
      double value2; //!< The scalar value 2 associated with the ternary arithmeric filter

      /*!
       * Applies the ternary scalar-field-scalar operator to the input data and returns the result.
       *
       * \param data a vector of packets corresponding to each slot (one in this case)
       * \return the result of the ternary operation
       */
      CDataPacketPtr virtual apply(std::vector<CDataPacketPtr> data);
      std::tuple<int, int, int> virtual buildGraph(std::vector<CDataPacketPtr> data);
  }; // class CScalarScalarFieldArithmeticFilter

  /*!
   * A generic ternary arithmetic filter wrapping any type of ternary scalar-field-field operator.
   */
  class CScalarFieldFieldArithmeticFilter : public CFilter, public IFilterEngine
  {
    public:
      /*!
       * Constructs an ternary scalar-field arithmetic filter wrapping the specified operator.
       *
       * \param gc the associated garbage collector
       * \param op the string identifing the ternary scalar-field-field operator
       * \param value the scalar value
       */
      CScalarFieldFieldArithmeticFilter(CGarbageCollector& gc, const std::string& op, double value);

    protected:
      COperatorExpr::functionScalarFieldField op; //!< The ternary scalar-field-scalar operator attached to the ternary arithmeric filter
      double value; //!< The scalar value 1 associated with the ternary arithmeric filter

      /*!
       * Applies the ternary scalar-field-field operator to the input data and returns the result.
       *
       * \param data a vector of packets corresponding to each slot (one in this case)
       * \return the result of the ternary operation
       */
      CDataPacketPtr virtual apply(std::vector<CDataPacketPtr> data);
      std::tuple<int, int, int> virtual buildGraph(std::vector<CDataPacketPtr> data);
  }; // class CScalarScalarFieldArithmeticFilter



 /*!
   * A generic ternary arithmetic filter wrapping any type of ternary field-scalar-scalar operator.
   */
  class CFieldScalarScalarArithmeticFilter : public CFilter, public IFilterEngine
  {
    public:
      /*!
       * Constructs an ternary field-scalar-scalar arithmetic filter wrapping the specified operator.
       *
       * \param gc the associated garbage collector
       * \param op the string identifing the ternary field-scalar-scalar operator
       * \param value1 the scalar value
       * \param value2 the scalar value
       */
      CFieldScalarScalarArithmeticFilter(CGarbageCollector& gc, const std::string& op, double value1, double value2);

    protected:
      COperatorExpr::functionFieldScalarScalar op; //!< The ternary field-scalar-scalar operator attached to the ternary arithmeric filter
      double value1; //!< The scalar value 1 associated with the ternary arithmeric filter
      double value2; //!< The scalar value 2 associated with the ternary arithmeric filter

      /*!
       * Applies the ternary field-scalar-scalar operator to the input data and returns the result.
       *
       * \param data a vector of packets corresponding to each slot (one in this case)
       * \return the result of the ternary operation
       */
      CDataPacketPtr virtual apply(std::vector<CDataPacketPtr> data);
      std::tuple<int, int, int> virtual buildGraph(std::vector<CDataPacketPtr> data);
  }; // class CFieldScalarScalarArithmeticFilter


/*!
   * A generic ternary arithmetic filter wrapping any type of ternary field-scalar-field operator.
   */
  class CFieldScalarFieldArithmeticFilter : public CFilter, public IFilterEngine
  {
    public:
      /*!
       * Constructs an ternary field-scalar-field arithmetic filter wrapping the specified operator.
       *
       * \param gc the associated garbage collector
       * \param op the string identifing the ternary field-scalar-field operator
       * \param value the scalar value
       */
      CFieldScalarFieldArithmeticFilter(CGarbageCollector& gc, const std::string& op, double value);

    protected:
      COperatorExpr::functionFieldScalarField op; //!< The ternary field-scalar-field operator attached to the ternary arithmeric filter
      double value; //!< The scalar value associated with the ternary arithmeric filter

      /*!
       * Applies the ternary field-scalar-field operator to the input data and returns the result.
       *
       * \param data a vector of packets corresponding to each slot (one in this case)
       * \return the result of the ternary operation
       */
      CDataPacketPtr virtual apply(std::vector<CDataPacketPtr> data);
      std::tuple<int, int, int> virtual buildGraph(std::vector<CDataPacketPtr> data);
  }; // class CFieldScalarFieldArithmeticFilter


/*!
   * A generic ternary arithmetic filter wrapping any type of ternary field-field-scalar operator.
   */
  class CFieldFieldScalarArithmeticFilter : public CFilter, public IFilterEngine
  {
    public:
      /*!
       * Constructs an ternary field-field-scalar arithmetic filter wrapping the specified operator.
       *
       * \param gc the associated garbage collector
       * \param op the string identifing the ternary field-scalar-field operator
       * \param value the scalar value
       */
      CFieldFieldScalarArithmeticFilter(CGarbageCollector& gc, const std::string& op, double value);

    protected:
      COperatorExpr::functionFieldFieldScalar op; //!< The ternary field-field-scalar operator attached to the ternary arithmeric filter
      double value; //!< The scalar value associated with the ternary arithmeric filter

      /*!
       * Applies the ternary field-field-scalar operator to the input data and returns the result.
       *
       * \param data a vector of packets corresponding to each slot (one in this case)
       * \return the result of the ternary operation
       */
      CDataPacketPtr virtual apply(std::vector<CDataPacketPtr> data);
      std::tuple<int, int, int> virtual buildGraph(std::vector<CDataPacketPtr> data);
  }; // class CFieldFielScalardArithmeticFilter


/*!
   * A generic ternary arithmetic filter wrapping any type of ternary field-field-field operator.
   */
  class CFieldFieldFieldArithmeticFilter : public CFilter, public IFilterEngine
  {
    public:
      /*!
       * Constructs an ternary field-field-scalar arithmetic filter wrapping the specified operator.
       *
       * \param gc the associated garbage collector
       * \param op the string identifing the ternary field-scalar-field operator
       */
      CFieldFieldFieldArithmeticFilter(CGarbageCollector& gc, const std::string& op);

    protected:
      COperatorExpr::functionFieldFieldField op; //!< The ternary field-field-field operator attached to the ternary arithmeric filter

      /*!
       * Applies the ternary field-field-field operator to the input data and returns the result.
       *
       * \param data a vector of packets corresponding to each slot (one in this case)
       * \return the result of the ternary operation
       */
      CDataPacketPtr virtual apply(std::vector<CDataPacketPtr> data);
      std::tuple<int, int, int> virtual buildGraph(std::vector<CDataPacketPtr> data);
  }; // class CFieldFielFieldArithmeticFilter


} // namespace xios

#endif //__XIOS_CTernaryArithmeticFilter__

