#include "scalar_expr_node.hpp"
#include "type.hpp"
#include "variable.hpp"
#include "operator_expr.hpp"

namespace xios
{
  CScalarValExprNode::CScalarValExprNode(const std::string& strVal)
    : strVal(strVal)
  { /* Nothing to do */ }

  double CScalarValExprNode::reduce() const
  {
    CType<double> val;
    val.fromString(strVal);
    return val;
  }

  CScalarVarExprNode::CScalarVarExprNode(const std::string& varId)
    : varId(varId)
  { /* Nothing to do */ }

  double CScalarVarExprNode::reduce() const
  {
    // $missing_value will be replaced with NaN
    if (varId == "missing_value")
    {
      return std::numeric_limits<double>::quiet_NaN();
    }
    else
    {
      if (!CVariable::has(varId)) 
        ERROR("double CScalarVarExprNode::reduce() const", << "The variable " << varId << " does not exist.");

      return CVariable::get(varId)->getData<double>();
    }
  }

  CScalarUnaryOpExprNode::CScalarUnaryOpExprNode(const std::string& opId, IScalarExprNode* child)
    : opId(opId)
    , child(child)
  {
    if (!child)
      ERROR("CScalarUnaryOpExprNode::CScalarUnaryOpExprNode(const std::string& opId, IScalarExprNode* child)",
            "Impossible to create the new expression node, an invalid child node was provided.");
  }

  double CScalarUnaryOpExprNode::reduce() const
  {
    COperatorExpr::functionScalar op = operatorExpr.getOpScalar(opId);
    return op(child->reduce());
  }

  CScalarBinaryOpExprNode::CScalarBinaryOpExprNode(IScalarExprNode* child1, const std::string& opId, IScalarExprNode* child2)
    : child1(child1)
    , opId(opId)
    , child2(child2)
  {
    if (!child1 || !child2)
      ERROR("CScalarBinaryOpExprNode::CScalarBinaryOpExprNode(IScalarExprNode* child1, const std::string& opId, IScalarExprNode* child2)",
            "Impossible to create the new expression node, an invalid child node was provided.");
  }

  double CScalarBinaryOpExprNode::reduce() const
  {
    COperatorExpr::functionScalarScalar op = operatorExpr.getOpScalarScalar(opId);
    return op(child1->reduce(), child2->reduce());
  }


  CScalarTernaryOpExprNode::CScalarTernaryOpExprNode(IScalarExprNode* child1, const std::string& opId, IScalarExprNode* child2, IScalarExprNode* child3)
    : child1(child1)
    , opId(opId)
    , child2(child2)
    , child3(child3)
  {
    if (!child1 || !child2 || !child3)
      ERROR("CScalarTernaryOpExprNode::CScalarTernaryOpExprNode(IScalarExprNode* child1, const std::string& opId, IScalarExprNode* child2, IScalarExprNode* child3)",
            "Impossible to create the new expression node, an invalid child node was provided.");
  }

  double CScalarTernaryOpExprNode::reduce() const
  {
    COperatorExpr::functionScalarScalarScalar op = operatorExpr.getOpScalarScalarScalar(opId);
    return op(child1->reduce(), child2->reduce(), child3->reduce());
  }
}
