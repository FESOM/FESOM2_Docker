#ifndef __XIOS_SCALAR_EXPR_NODE_HPP__
#define __XIOS_SCALAR_EXPR_NODE_HPP__

#include <string>
#include <boost/smart_ptr/scoped_ptr.hpp>

namespace xios
{
  /*!
   * Interface implemented by all the nodes of a tree representing an expression
   * which can be reduced to a scalar value.
   */
  struct IScalarExprNode 
  {
    /*!
     * Builds a filter graph corresponding to the expression tree.
     *
     * \return the output pin of the filter producing the result of the expression 
     */
    virtual double reduce() const = 0;
  };

  /*!
   * Expression node corresponding to a scalar value.
   */
  class CScalarValExprNode : public IScalarExprNode
  {
    public:
      /*!
       * Constructs an expression node corresponding to the specified scalar value.
       *
       * \param strVal the string representation of the scalar value
       */
      CScalarValExprNode(const std::string& strVal);

      double reduce() const;

    private:
      std::string strVal; //!< The string representation of the scalar value
  };

  /*!
   * Expression node corresponding to a scalar variable.
   */
  class CScalarVarExprNode : public IScalarExprNode
  {
    public:
      /*!
       * Constructs an expression node corresponding
       * to the scalar variable whose id is provided.
       *
       * \param varId the identifier of the scalar variable
       */
      CScalarVarExprNode(const std::string& varId);

      double reduce() const;

    private:
      std::string varId; //!< The identifier of the field
  };

  /*!
   * Expression node corresponding to a unary operation on a scalar.
   */
  class CScalarUnaryOpExprNode : public IScalarExprNode
  {
    public:
      /*!
       * Constructs an expression node corresponding to the specified unary operation
       * applied to the provided scalar node.
       * Note that the child node will be destroyed automatically when the parent node
       * is destroyed.
       *
       * \param opId the identifier of the operator
       * \param child the scalar child node to which the operator is applied
       */
      CScalarUnaryOpExprNode(const std::string& opId, IScalarExprNode* child);

      double reduce() const;

    private:
      std::string opId; //!< The identifier of the field
      boost::scoped_ptr<IScalarExprNode> child; //!< The scalar child node to which the operator is applied
  };

  /*!
   * Expression node corresponding to a binary operation on two scalars.
   */
  class CScalarBinaryOpExprNode : public IScalarExprNode
  {
    public:
      /*!
       * Constructs an expression node corresponding to the specified binary operation
       * applied to the provided scalar child nodes.
       * Note that the child nodes will be destroyed automatically when the parent node
       * is destroyed.
       *
       * \param opId the identifier of the operator
       * \param child1, child2 the scalar child nodes to which the operator is applied
       */
      CScalarBinaryOpExprNode(IScalarExprNode* child1, const std::string& opId, IScalarExprNode* child2);

      double reduce() const;

    private:
      std::string opId; //!< The identifier of the field
      boost::scoped_ptr<IScalarExprNode> child1, child2; //!< The scalar child nodes to which the operator is applied
  };

    class CScalarTernaryOpExprNode : public IScalarExprNode
  {
    public:
      /*!
       * Constructs an expression node corresponding to the specified ternary operation
       * applied to the provided scalar child nodes.
       * Note that the child nodes will be destroyed automatically when the parent node
       * is destroyed.
       *
       * \param opId the identifier of the operator
       * \param child1, child2 , child3 the scalar child nodes to which the operator is applied
       */
      CScalarTernaryOpExprNode(IScalarExprNode* child1, const std::string& opId, IScalarExprNode* child2, IScalarExprNode* child3);

      double reduce() const;

    private:
      std::string opId; //!< The identifier of the field
      boost::scoped_ptr<IScalarExprNode> child1, child2, child3; //!< The scalar child nodes to which the operator is applied
  };
}

#endif // __XIOS_SCALAR_EXPR_NODE_HPP__
