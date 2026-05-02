#ifndef __XIOS_FILTER_EXPR_NODE_HPP__
#define __XIOS_FILTER_EXPR_NODE_HPP__

#include <string>
#include <boost/smart_ptr/scoped_ptr.hpp>
#include "scalar_expr_node.hpp"

#include "duration.hpp"

namespace xios
{
  class COutputPin;
  class CGarbageCollector;
  class CField;

  /*!
   * Interface implemented by all the nodes of a tree representing an expression
   * which can be transformed into a filter graph representation.
   */
  struct IFilterExprNode 
  {
    /*!
     * Builds a filter graph corresponding to the expression tree.
     *
     * \param gc the garbage collector to associated with the filter graph
     * \param thisField the field to which the expression is attached
     * \return the output pin of the filter producing the result of the expression 
     */
    virtual std::shared_ptr<COutputPin> reduce(CGarbageCollector& gc, CField& thisField, Time start_graph=-1, Time end_graph=-1) const = 0;
  };

  /*!
   * Expression node corresponding to a field.
   */
  class CFilterFieldExprNode : public IFilterExprNode
  {
    public:
      /*!
       * Constructs an expression node corresponding
       * to the field whose id is provided.
       *
       * \param fieldId the identifier of the field
       */
      CFilterFieldExprNode(const std::string& fieldId);

      virtual std::shared_ptr<COutputPin> reduce(CGarbageCollector& gc, CField& thisField, Time start_graph=-1, Time end_graph=-1) const;

    private:
      std::string fieldId; //!< The identifier of the field
  };

  /*!
   * Expression node corresponding to a field for which the result of
   * the temporal operation is requested instead of the instant value.
   */
  class CFilterTemporalFieldExprNode : public IFilterExprNode
  {
    public:
      /*!
       * Constructs an expression node corresponding
       * to the field whose id is provided.
       *
       * \param fieldId the identifier of the field
       */
      CFilterTemporalFieldExprNode(const std::string& fieldId);

      virtual std::shared_ptr<COutputPin> reduce(CGarbageCollector& gc, CField& thisField, Time start_graph=-1, Time end_graph=-1) const;

    private:
      std::string fieldId; //!< The identifier of the field
  };

  /*!
   * Expression node corresponding to a unary operation on a field.
   */
  class CFilterUnaryOpExprNode : public IFilterExprNode
  {
    public:
      /*!
       * Constructs an expression node corresponding to the specified unary operation
       * applied to the provided child node.
       * Note that the child node will be destroyed automatically when the parent node
       * is destroyed.
       *
       * \param opId the identifier of the operator
       * \param child the child node to which the operator is applied
       */
      CFilterUnaryOpExprNode(const std::string& opId, IFilterExprNode* child);

      virtual std::shared_ptr<COutputPin> reduce(CGarbageCollector& gc, CField& thisField, Time start_graph=-1, Time end_graph=-1) const;

    private:
      std::string opId; //!< The identifier of the field
      boost::scoped_ptr<IFilterExprNode> child; //!< The child node to which the operator is applied
  };

  /*!
   * Expression node corresponding to a binary operation on a scalar and a field.
   */
  class CFilterScalarFieldOpExprNode : public IFilterExprNode
  {
    public:
      /*!
       * Constructs an expression node corresponding to the specified binary operation
       * applied to the provided scalar and field child nodes.
       * Note that the child nodes will be destroyed automatically when the parent node
       * is destroyed.
       *
       * \param child1 the scalar child node to which the operator is applied
       * \param opId the identifier of the operator
       * \param child2 the field child node to which the operator is applied
       */
      CFilterScalarFieldOpExprNode(IScalarExprNode* child1, const std::string& opId, IFilterExprNode* child2);

      virtual std::shared_ptr<COutputPin> reduce(CGarbageCollector& gc, CField& thisField, Time start_graph=-1, Time end_graph=-1) const;

    private:
      std::string opId; //!< The identifier of the field
      boost::scoped_ptr<IScalarExprNode> child1; //!< The scalar child node to which the operator is applied
      boost::scoped_ptr<IFilterExprNode> child2; //!< The field child node to which the operator is applied
  };

  /*!
   * Expression node corresponding to a binary operation on a field and a scalar.
   */
  class CFilterFieldScalarOpExprNode : public IFilterExprNode
  {
    public:
      /*!
       * Constructs an expression node corresponding to the specified binary operation
       * applied to the provided field and scalar child nodes.
       * Note that the child nodes will be destroyed automatically when the parent node
       * is destroyed.
       *
       * \param child1 the field child node to which the operator is applied
       * \param opId the identifier of the operator
       * \param child2 the scalar child node to which the operator is applied
       */
      CFilterFieldScalarOpExprNode(IFilterExprNode* child1, const std::string& opId, IScalarExprNode* child2);

      virtual std::shared_ptr<COutputPin> reduce(CGarbageCollector& gc, CField& thisField, Time start_graph=-1, Time end_graph=-1) const;

    private:
      std::string opId; //!< The identifier of the field
      boost::scoped_ptr<IFilterExprNode> child1; //!< The field child node to which the operator is applied
      boost::scoped_ptr<IScalarExprNode> child2; //!< The scalar child node to which the operator is applied
  };

  /*!
   * Expression node corresponding to a binary operation on two fields.
   */
  class CFilterFieldFieldOpExprNode : public IFilterExprNode
  {
    public:
      /*!
       * Constructs an expression node corresponding to the specified binary operation
       * applied to the provided field child nodes.
       * Note that the child nodes will be destroyed automatically when the parent node
       * is destroyed.
       *
       * \param opId the identifier of the operator
       * \param child1, child2 the field child nodes to which the operator is applied
       */
      CFilterFieldFieldOpExprNode(IFilterExprNode* child1, const std::string& opId, IFilterExprNode* child2);

      virtual std::shared_ptr<COutputPin> reduce(CGarbageCollector& gc, CField& thisField, Time start_graph=-1, Time end_graph=-1) const;

    private:
      std::string opId; //!< The identifier of the field
      boost::scoped_ptr<IFilterExprNode> child1, child2; //!< The field child nodes to which the operator is applied
  };



 /*!
   * Expression node corresponding to a ternary operation on a scalar-scalar-field.
   */
  class CFilterScalarScalarFieldOpExprNode : public IFilterExprNode
  {
    public:
      /*!
       * Constructs an expression node corresponding to the specified ternary operation
       * applied to the provided fields and scalars child nodes.
       * Note that the child nodes will be destroyed automatically when the parent node
       * is destroyed.
       *
       * \param child1 the scalar child node to which the operator is applied
       * \param opId the identifier of the operator
       * \param child2 the scalar child node to which the operator is applied
       * \param child3 the field child node to which the operator is applied
      */
      CFilterScalarScalarFieldOpExprNode(IScalarExprNode* child1, const std::string& opId, IScalarExprNode* child2, IFilterExprNode* child3);

      virtual std::shared_ptr<COutputPin> reduce(CGarbageCollector& gc, CField& thisField, Time start_graph=-1, Time end_graph=-1) const;

    private:
      std::string opId; //!< The identifier of the field
      boost::scoped_ptr<IScalarExprNode> child1; //!< The scalar child node to which the operator is applied
      boost::scoped_ptr<IScalarExprNode> child2; //!< The scalar child node to which the operator is applied
      boost::scoped_ptr<IFilterExprNode> child3; //!< The field child node to which the operator is applied
  };


  /*!
   * Expression node corresponding to a ternary operation on a scalar-field-scalar.
   */
  class CFilterScalarFieldScalarOpExprNode : public IFilterExprNode
  {
    public:
      /*!
       * Constructs an expression node corresponding to the specified ternary operation
       * applied to the provided fields and scalars child nodes.
       * Note that the child nodes will be destroyed automatically when the parent node
       * is destroyed.
       *
       * \param child1 the scalar child node to which the operator is applied
       * \param opId the identifier of the operator
       * \param child2 the field child node to which the operator is applied
       * \param child3 the scalar child node to which the operator is applied
      */
      CFilterScalarFieldScalarOpExprNode(IScalarExprNode* child1, const std::string& opId, IFilterExprNode* child2, IScalarExprNode* child3);

      virtual std::shared_ptr<COutputPin> reduce(CGarbageCollector& gc, CField& thisField, Time start_graph=-1, Time end_graph=-1) const;

    private:
      std::string opId; //!< The identifier of the field
      boost::scoped_ptr<IScalarExprNode> child1; //!< The scalar child node to which the operator is applied
      boost::scoped_ptr<IFilterExprNode> child2; //!< The field child node to which the operator is applied
      boost::scoped_ptr<IScalarExprNode> child3; //!< The scalar child node to which the operator is applied
  };


  /*!
   * Expression node corresponding to a ternary operation on a scalar-field-field.
   */
  class CFilterScalarFieldFieldOpExprNode : public IFilterExprNode
  {
    public:
      /*!
       * Constructs an expression node corresponding to the specified ternary operation
       * applied to the provided fields and scalars child nodes.
       * Note that the child nodes will be destroyed automatically when the parent node
       * is destroyed.
       *
       * \param child1 the scalar child node to which the operator is applied
       * \param opId the identifier of the operator
       * \param child2 the field child node to which the operator is applied
       * \param child3 the field child node to which the operator is applied
      */
      CFilterScalarFieldFieldOpExprNode(IScalarExprNode* child1, const std::string& opId, IFilterExprNode* child2, IFilterExprNode* child3);

      virtual std::shared_ptr<COutputPin> reduce(CGarbageCollector& gc, CField& thisField, Time start_graph=-1, Time end_graph=-1) const;

    private:
      std::string opId; //!< The identifier of the field
      boost::scoped_ptr<IScalarExprNode> child1; //!< The scalar child node to which the operator is applied
      boost::scoped_ptr<IFilterExprNode> child2; //!< The field child node to which the operator is applied
      boost::scoped_ptr<IFilterExprNode> child3; //!< The field child node to which the operator is applied
  };



/*!
   * Expression node corresponding to a ternary operation on a field-scalar-scalar.
   */
  class CFilterFieldScalarScalarOpExprNode : public IFilterExprNode
  {
    public:
      /*!
       * Constructs an expression node corresponding to the specified ternary operation
       * applied to the provided fields and scalars child nodes.
       * Note that the child nodes will be destroyed automatically when the parent node
       * is destroyed.
       *
       * \param child1 the field child node to which the operator is applied
       * \param opId the identifier of the operator
       * \param child2 the scalar child node to which the operator is applied
       * \param child3 the scalar child node to which the operator is applied
      */
      CFilterFieldScalarScalarOpExprNode(IFilterExprNode* child1, const std::string& opId, IScalarExprNode* child2, IScalarExprNode* child3);

      virtual std::shared_ptr<COutputPin> reduce(CGarbageCollector& gc, CField& thisField, Time start_graph=-1, Time end_graph=-1) const;

    private:
      std::string opId; //!< The identifier of the field
      boost::scoped_ptr<IFilterExprNode> child1; //!< The field child node to which the operator is applied
      boost::scoped_ptr<IScalarExprNode> child2; //!< The scalar child node to which the operator is applied
      boost::scoped_ptr<IScalarExprNode> child3; //!< The scalar child node to which the operator is applied
  };


/*!
   * Expression node corresponding to a ternary operation on a field-scalar-field.
   */
  class CFilterFieldScalarFieldOpExprNode : public IFilterExprNode
  {
    public:
      /*!
       * Constructs an expression node corresponding to the specified ternary operation
       * applied to the provided fields and scalars child nodes.
       * Note that the child nodes will be destroyed automatically when the parent node
       * is destroyed.
       *
       * \param child1 the field child node to which the operator is applied
       * \param opId the identifier of the operator
       * \param child2 the scalar child node to which the operator is applied
       * \param child3 the field child node to which the operator is applied
      */
      CFilterFieldScalarFieldOpExprNode(IFilterExprNode* child1, const std::string& opId, IScalarExprNode* child2, IFilterExprNode* child3);

      virtual std::shared_ptr<COutputPin> reduce(CGarbageCollector& gc, CField& thisField, Time start_graph=-1, Time end_graph=-1) const;

    private:
      std::string opId; //!< The identifier of the field
      boost::scoped_ptr<IFilterExprNode> child1; //!< The field child node to which the operator is applied
      boost::scoped_ptr<IScalarExprNode> child2; //!< The scalar child node to which the operator is applied
      boost::scoped_ptr<IFilterExprNode> child3; //!< The field child node to which the operator is applied
  };

  /*!
   * Expression node corresponding to a ternary operation on a field-field-scalar.
   */
  class CFilterFieldFieldScalarOpExprNode : public IFilterExprNode
  {
    public:
      /*!
       * Constructs an expression node corresponding to the specified ternary operation
       * applied to the provided fields and scalars child nodes.
       * Note that the child nodes will be destroyed automatically when the parent node
       * is destroyed.
       *
       * \param child1 the field child node to which the operator is applied
       * \param opId the identifier of the operator
       * \param child2 the field child node to which the operator is applied
       * \param child3 the scalar child node to which the operator is applied
      */
      CFilterFieldFieldScalarOpExprNode(IFilterExprNode* child1, const std::string& opId, IFilterExprNode* child2, IScalarExprNode* child3);

      virtual std::shared_ptr<COutputPin> reduce(CGarbageCollector& gc, CField& thisField, Time start_graph=-1, Time end_graph=-1) const;

    private:
      std::string opId; //!< The identifier of the field
      boost::scoped_ptr<IFilterExprNode> child1; //!< The field child node to which the operator is applied
      boost::scoped_ptr<IFilterExprNode> child2; //!< The field child node to which the operator is applied
      boost::scoped_ptr<IScalarExprNode> child3; //!< The scalar child node to which the operator is applied
  };


  /*!
   * Expression node corresponding to a ternary operation on a field-field-field.
   */
  class CFilterFieldFieldFieldOpExprNode : public IFilterExprNode
  {
    public:
      /*!
       * Constructs an expression node corresponding to the specified ternary operation
       * applied to the provided fields and scalars child nodes.
       * Note that the child nodes will be destroyed automatically when the parent node
       * is destroyed.
       *
       * \param child1 the field child node to which the operator is applied
       * \param opId the identifier of the operator
       * \param child2 the field child node to which the operator is applied
       * \param child3 the field child node to which the operator is applied
      */
      CFilterFieldFieldFieldOpExprNode(IFilterExprNode* child1, const std::string& opId, IFilterExprNode* child2, IFilterExprNode* child3);

      virtual std::shared_ptr<COutputPin> reduce(CGarbageCollector& gc, CField& thisField, Time start_graph=-1, Time end_graph=-1) const;

    private:
      std::string opId; //!< The identifier of the field
      boost::scoped_ptr<IFilterExprNode> child1; //!< The field child node to which the operator is applied
      boost::scoped_ptr<IFilterExprNode> child2; //!< The field child node to which the operator is applied
      boost::scoped_ptr<IFilterExprNode> child3; //!< The field child node to which the operator is applied
  };



}

#endif // __XIOS_FILTER_EXPR_NODE_HPP__
