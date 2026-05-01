#include "filter_expr_node.hpp"
#include "unary_arithmetic_filter.hpp"
#include "binary_arithmetic_filter.hpp"
#include "ternary_arithmetic_filter.hpp"
#include "field.hpp"

namespace xios
{
  CFilterFieldExprNode::CFilterFieldExprNode(const std::string& fieldId)
    : fieldId(fieldId)
  { /* Nothing to do */ }

  
  std::shared_ptr<COutputPin> CFilterFieldExprNode::reduce(CGarbageCollector& gc, CField& thisField, Time start_graph, Time end_graph) const
  {
    std::shared_ptr<COutputPin> outputPin;

    if (fieldId == "this") outputPin = thisField.getSelfReference(gc);
    else
    {
      string id ;

      if (fieldId == "this_ref")
      {
        if (thisField.field_ref.isEmpty())
        {
          ERROR("shared_ptr<COutputPin> CFilterFieldExprNode::reduce(CGarbageCollector& gc, CField& thisField) const",
                << "field_ref attribute is empty.");
        }
        else id = thisField.field_ref ;
      }
      else id= fieldId ;
       
      if (CField::has(id))
      {
        CField* field = CField::get(id);
        if (field == &thisField)
          ERROR("shared_ptr<COutputPin> CFilterFieldExprNode::reduce(CGarbageCollector& gc, CField& thisField) const",
                << "The field " << id << " has an invalid reference to itself. "
                << "Use the keyword \"this\" if you want to reference the input data sent to this field.");

        // field->buildFilterGraph(gc, false);
        field->buildFilterGraph(gc, false, start_graph, end_graph);
        outputPin = field->getInstantDataFilter();
      }
      else ERROR("boost::shared_ptr<COutputPin> CFilterFieldExprNode::reduce(CGarbageCollector& gc, CField& thisField) const",
                  << "The field " << id << " does not exist.");
    }
    return outputPin;
  }


  CFilterTemporalFieldExprNode::CFilterTemporalFieldExprNode(const std::string& fieldId)
    : fieldId(fieldId)
  { /* Nothing to do */ }


  std::shared_ptr<COutputPin> CFilterTemporalFieldExprNode::reduce(CGarbageCollector& gc, CField& thisField, Time start_graph, Time end_graph) const
  {
    std::shared_ptr<COutputPin> outputPin;

    if (fieldId == "this")
      outputPin = thisField.getSelfTemporalDataFilter(gc, thisField.freq_op.isEmpty() ? TimeStep : thisField.freq_op);
    else
    {
      string id ;

      if (fieldId == "this_ref")
      {
        if (thisField.field_ref.isEmpty())
        {
          ERROR("shared_ptr<COutputPin> CFilterFieldExprNode::reduce(CGarbageCollector& gc, CField& thisField) const",
                << "field_ref attribute is empty.");
        }
        else id = thisField.field_ref ;
      }
      else id = fieldId ;

      if (CField::has(id))
      {
        CField* field = CField::get(id);
        if (field == &thisField)
          ERROR("shared_ptr<COutputPin> CFilterTemporalFieldExprNode::reduce(CGarbageCollector& gc, CField& thisField) const",
                << "The field " << fieldId << " has an invalid reference to itself. "
                << "Use the keyword \"this\" if you want to reference the input data sent to this field.");

        field->buildFilterGraph(gc, false);
        outputPin = field->getTemporalDataFilter(gc, thisField.freq_op.isEmpty() ? TimeStep : thisField.freq_op);
      }
      else
        ERROR("shared_ptr<COutputPin> CFilterTemporalFieldExprNode::reduce(CGarbageCollector& gc, CField& thisField) const",
              << "The field " << fieldId << " does not exist.");
    }
    return outputPin;
  }


  CFilterUnaryOpExprNode::CFilterUnaryOpExprNode(const std::string& opId, IFilterExprNode* child)
    : opId(opId)
    , child(child)
  {
    if (!child)
      ERROR("CFilterUnaryOpExprNode::CFilterUnaryOpExprNode(const std::string& opId, IFilterExprNode* child)",
            "Impossible to create the new expression node, an invalid child node was provided.");
  }

  std::shared_ptr<COutputPin> CFilterUnaryOpExprNode::reduce(CGarbageCollector& gc, CField& thisField, Time start_graph, Time end_graph) const
  {
    std::shared_ptr<COutputPin> ch = child->reduce(gc, thisField, start_graph, end_graph);

    std::shared_ptr<CUnaryArithmeticFilter> filter(new CUnaryArithmeticFilter(gc, opId));
    ch->connectOutput(filter, 0);

    (filter->parent_filters).resize(1);
    (filter->parent_filters)[0] = ch;

    filter->tag = ch->tag;
    filter->start_graph = ch->start_graph;
    filter->end_graph = ch->end_graph;
    filter->field = &thisField;


    return filter;
  }

  CFilterScalarFieldOpExprNode::CFilterScalarFieldOpExprNode(IScalarExprNode* child1, const std::string& opId, IFilterExprNode* child2)
    : child1(child1)
    , opId(opId)
    , child2(child2)
  {
    if (!child1 || !child2)
      ERROR("CFilterScalarFieldOpExprNode::CFilterScalarFieldOpExprNode(IScalarExprNode* child1, const std::string& opId, IFilterExprNode* child2)",
            "Impossible to create the new expression node, an invalid child node was provided.");
  }

  std::shared_ptr<COutputPin> CFilterScalarFieldOpExprNode::reduce(CGarbageCollector& gc, CField& thisField, Time start_graph, Time end_graph) const
  {
    std::shared_ptr<COutputPin> ch2 = child2->reduce(gc, thisField, start_graph, end_graph);
    std::shared_ptr<CScalarFieldArithmeticFilter> filter(new CScalarFieldArithmeticFilter(gc, opId, child1->reduce()));
    ch2->connectOutput(filter, 0);
    
    (filter->parent_filters).resize(1);
    (filter->parent_filters)[0] = ch2;

    filter->tag = ch2->tag;
    filter->start_graph = ch2->start_graph;
    filter->end_graph = ch2->end_graph;
    filter->field = &thisField;

    return filter;
  }

  CFilterFieldScalarOpExprNode::CFilterFieldScalarOpExprNode(IFilterExprNode* child1, const std::string& opId, IScalarExprNode* child2)
    : child1(child1)
    , opId(opId)
    , child2(child2)
  {
    if (!child1 || !child2)
      ERROR("CFilterFieldScalarOpExprNode::CFilterFieldScalarOpExprNode(IFilterExprNode* child1, const std::string& opId, IScalarExprNode* child2)",
            "Impossible to create the new expression node, an invalid child node was provided.");
  }

  std::shared_ptr<COutputPin> CFilterFieldScalarOpExprNode::reduce(CGarbageCollector& gc, CField& thisField, Time start_graph, Time end_graph) const
  {
    std::shared_ptr<COutputPin> ch1 = child1->reduce(gc, thisField, start_graph, end_graph);

    std::shared_ptr<CFieldScalarArithmeticFilter> filter(new CFieldScalarArithmeticFilter(gc, opId, child2->reduce()));
    ch1->connectOutput(filter, 0);

    (filter->parent_filters).resize(1);
    (filter->parent_filters)[0] = ch1;

    filter->tag = ch1->tag;
    filter->start_graph = ch1->start_graph;
    filter->end_graph = ch1->end_graph;
    filter->field = &thisField;

    return filter;
  }

  CFilterFieldFieldOpExprNode::CFilterFieldFieldOpExprNode(IFilterExprNode* child1, const std::string& opId, IFilterExprNode* child2)
    : child1(child1)
    , opId(opId)
    , child2(child2)
  {
    if (!child1 || !child2)
      ERROR("CFilterFieldFieldOpExprNode::CFilterFieldFieldOpExprNode(IFilterExprNode* child1, const std::string& opId, IFilterExprNode* child2)",
            "Impossible to create the new expression node, an invalid child node was provided.");
  }

  std::shared_ptr<COutputPin> CFilterFieldFieldOpExprNode::reduce(CGarbageCollector& gc, CField& thisField, Time start_graph, Time end_graph) const
  {
    std::shared_ptr<COutputPin> ch1 = child1->reduce(gc, thisField, start_graph, end_graph);
    std::shared_ptr<COutputPin> ch2 = child2->reduce(gc, thisField, start_graph, end_graph);

    std::shared_ptr<CFieldFieldArithmeticFilter> filter(new CFieldFieldArithmeticFilter(gc, opId));
    ch1->connectOutput(filter, 0);
    ch2->connectOutput(filter, 1); 

    (filter->parent_filters).resize(2);
    (filter->parent_filters)[0] = ch1;
    (filter->parent_filters)[1] = ch2;

    filter->tag = (ch1->tag || ch2->tag);
    filter->start_graph = ch1->tag? ch1->start_graph : (ch2->tag? ch2->start_graph: -1);
    filter->end_graph = ch1->tag? ch1->end_graph : (ch2->tag? ch2->end_graph: -1);

    filter->field = &thisField;


    return filter;
  }




  CFilterScalarScalarFieldOpExprNode::CFilterScalarScalarFieldOpExprNode(IScalarExprNode* child1, const std::string& opId, IScalarExprNode* child2, IFilterExprNode* child3)
    : child1(child1)
    , opId(opId)
    , child2(child2)
    , child3(child3)
  {
    if (!child1 || !child2 || !child3)
      ERROR("  CFilterScalarScalarFieldOpExprNode::CFilterScalarScalarFieldOpExprNode(IScalarExprNode* child1, const std::string& opId, IScalarExprNode* child2, IFilterExprNode* child3)",
            "Impossible to create the new expression node, an invalid child node was provided.");
  }

  std::shared_ptr<COutputPin> CFilterScalarScalarFieldOpExprNode::reduce(CGarbageCollector& gc, CField& thisField, Time start_graph, Time end_graph) const
  {
    std::shared_ptr<COutputPin> ch3 = child3->reduce(gc, thisField, start_graph, end_graph);

    std::shared_ptr<CScalarScalarFieldArithmeticFilter> filter(new CScalarScalarFieldArithmeticFilter(gc, opId, child1->reduce(),child2->reduce()));
    ch3->connectOutput(filter, 0);
    
    (filter->parent_filters).resize(1);
    (filter->parent_filters)[0] = ch3;

    filter->tag = ch3->tag;
    filter->start_graph = ch3->start_graph;
    filter->end_graph = ch3->end_graph;
    filter->field = &thisField;

    return filter;
  }


  CFilterScalarFieldScalarOpExprNode::CFilterScalarFieldScalarOpExprNode(IScalarExprNode* child1, const std::string& opId, IFilterExprNode* child2, IScalarExprNode* child3)
    : child1(child1)
    , opId(opId)
    , child2(child2)
    , child3(child3)
  {
    if (!child1 || !child2 || !child3)
      ERROR("  CFilterScalarFieldScalarOpExprNode::CFilterScalarFieldScalarOpExprNode(IScalarExprNode* child1, const std::string& opId, IFilterExprNode* child2, IScalarExprNode* child3)",
            "Impossible to create the new expression node, an invalid child node was provided.");
  }

  std::shared_ptr<COutputPin> CFilterScalarFieldScalarOpExprNode::reduce(CGarbageCollector& gc, CField& thisField, Time start_graph, Time end_graph) const
  {
    std::shared_ptr<COutputPin> ch2 = child2->reduce(gc, thisField, start_graph, end_graph);

    std::shared_ptr<CScalarFieldScalarArithmeticFilter> filter(new CScalarFieldScalarArithmeticFilter(gc, opId, child1->reduce(),child3->reduce()));
    ch2->connectOutput(filter, 0);

    (filter->parent_filters).resize(1);
    (filter->parent_filters)[0] = ch2;

    filter->tag = ch2->tag;
    filter->start_graph = ch2->start_graph;
    filter->end_graph = ch2->end_graph;
    filter->field = &thisField;

    return filter;
  }


  CFilterScalarFieldFieldOpExprNode::CFilterScalarFieldFieldOpExprNode(IScalarExprNode* child1, const std::string& opId, IFilterExprNode* child2, IFilterExprNode* child3)
    : child1(child1)
    , opId(opId)
    , child2(child2)
    , child3(child3)
  {
    if (!child1 || !child2 || !child3)
      ERROR("  CFilterScalarFieldFieldOpExprNode::CFilterScalarFieldFieldOpExprNode(IScalarExprNode* child1, const std::string& opId, IFilterExprNode* child2, IFilterExprNode* child3)",
            "Impossible to create the new expression node, an invalid child node was provided.");
  }

  std::shared_ptr<COutputPin> CFilterScalarFieldFieldOpExprNode::reduce(CGarbageCollector& gc, CField& thisField, Time start_graph, Time end_graph) const
  {
    std::shared_ptr<COutputPin> ch2 = child2->reduce(gc, thisField, start_graph, end_graph);
    std::shared_ptr<COutputPin> ch3 = child3->reduce(gc, thisField, start_graph, end_graph);

    std::shared_ptr<CScalarFieldFieldArithmeticFilter> filter(new CScalarFieldFieldArithmeticFilter(gc, opId, child1->reduce()));
    ch2->connectOutput(filter, 0);
    ch3->connectOutput(filter, 1);

    (filter->parent_filters).resize(2);
    (filter->parent_filters)[0] = ch2;
    (filter->parent_filters)[1] = ch3;

    filter->tag = (ch3->tag || ch2->tag);
    filter->start_graph = ch3->tag? ch3->start_graph : (ch2->tag? ch2->start_graph: -1);
    filter->end_graph = ch3->tag? ch3->end_graph : (ch2->tag? ch2->end_graph: -1);
    filter->field = &thisField;

    return filter;
  }



  CFilterFieldScalarScalarOpExprNode::CFilterFieldScalarScalarOpExprNode(IFilterExprNode* child1, const std::string& opId, IScalarExprNode* child2, IScalarExprNode* child3)
    : child1(child1)
    , opId(opId)
    , child2(child2)
    , child3(child3)
  {
    if (!child1 || !child2 || !child3)
      ERROR("  CFilterFieldScalarScalarOpExprNode::CFilterFieldScalarScalarOpExprNode(IFilterExprNode* child1, const std::string& opId, IScalarExprNode* child2, IScalarExprNode* child3)",
            "Impossible to create the new expression node, an invalid child node was provided.");
  }

  std::shared_ptr<COutputPin> CFilterFieldScalarScalarOpExprNode::reduce(CGarbageCollector& gc, CField& thisField, Time start_graph, Time end_graph) const
  {
    std::shared_ptr<COutputPin> ch1 = child1->reduce(gc, thisField, start_graph, end_graph);

    std::shared_ptr<CFieldScalarScalarArithmeticFilter> filter(new CFieldScalarScalarArithmeticFilter(gc, opId, child2->reduce(),child3->reduce()));
    ch1->connectOutput(filter, 0);

    (filter->parent_filters).resize(1);
    (filter->parent_filters)[0] = ch1;

    filter->tag = ch1->tag;
    filter->start_graph = ch1->start_graph;
    filter->end_graph = ch1->end_graph;
    filter->field = &thisField;

    return filter;
  }



  CFilterFieldScalarFieldOpExprNode::CFilterFieldScalarFieldOpExprNode(IFilterExprNode* child1, const std::string& opId, IScalarExprNode* child2, IFilterExprNode* child3)
    : child1(child1)
    , opId(opId)
    , child2(child2)
    , child3(child3)
  {
    if (!child1 || !child2 || !child3)
      ERROR("  CFilterFieldScalarFieldOpExprNode::CFilterFieldScalarFieldOpExprNode(IFilterExprNode* child1, const std::string& opId, IScalarExprNode* child2, IFilterExprNode* child3)",
            "Impossible to create the new expression node, an invalid child node was provided.");
  }

  std::shared_ptr<COutputPin> CFilterFieldScalarFieldOpExprNode::reduce(CGarbageCollector& gc, CField& thisField, Time start_graph, Time end_graph) const
  {
    std::shared_ptr<COutputPin> ch1 = child1->reduce(gc, thisField, start_graph, end_graph);
    std::shared_ptr<COutputPin> ch3 = child3->reduce(gc, thisField, start_graph, end_graph);

    std::shared_ptr<CFieldScalarFieldArithmeticFilter> filter(new CFieldScalarFieldArithmeticFilter(gc, opId, child2->reduce()));
    ch1->connectOutput(filter, 0);
    ch3->connectOutput(filter, 1);

    (filter->parent_filters).resize(2);
    (filter->parent_filters)[0] = ch1;
    (filter->parent_filters)[1] = ch3;

    filter->tag = (ch3->tag || ch1->tag);
    filter->start_graph = ch3->tag? ch3->start_graph : (ch1->tag? ch1->start_graph: -1);
    filter->end_graph = ch3->tag? ch3->end_graph : (ch1->tag? ch1->end_graph: -1);
    filter->field = &thisField;

    return filter;
  }



  CFilterFieldFieldScalarOpExprNode::CFilterFieldFieldScalarOpExprNode(IFilterExprNode* child1, const std::string& opId, IFilterExprNode* child2, IScalarExprNode* child3)
    : child1(child1)
    , opId(opId)
    , child2(child2)
    , child3(child3)
  {
    if (!child1 || !child2 || !child3)
      ERROR("  CFilterFieldFieldScalarOpExprNode::CFilterFieldFieldScalarOpExprNode(IFilterExprNode* child1, const std::string& opId, IFilterExprNode* child2, IScalarExprNode* child3)",
            "Impossible to create the new expression node, an invalid child node was provided.");
  }

  std::shared_ptr<COutputPin> CFilterFieldFieldScalarOpExprNode::reduce(CGarbageCollector& gc, CField& thisField, Time start_graph, Time end_graph) const
  {
    std::shared_ptr<COutputPin> ch1 = child1->reduce(gc, thisField, start_graph, end_graph);
    std::shared_ptr<COutputPin> ch2 = child2->reduce(gc, thisField, start_graph, end_graph);

    std::shared_ptr<CFieldFieldScalarArithmeticFilter> filter(new CFieldFieldScalarArithmeticFilter(gc, opId, child3->reduce()));
    ch1->connectOutput(filter, 0);
    ch2->connectOutput(filter, 1);

    (filter->parent_filters).resize(2);
    (filter->parent_filters)[0] = ch1;
    (filter->parent_filters)[1] = ch2;

    filter->tag = (ch2->tag || ch1->tag);
    filter->start_graph = ch2->tag? ch2->start_graph : (ch1->tag? ch1->start_graph: -1);
    filter->end_graph = ch2->tag? ch2->end_graph : (ch1->tag? ch1->end_graph: -1);
    filter->field = &thisField;
    return filter;
  }


  CFilterFieldFieldFieldOpExprNode::CFilterFieldFieldFieldOpExprNode(IFilterExprNode* child1, const std::string& opId, IFilterExprNode* child2, IFilterExprNode* child3)
    : child1(child1)
    , opId(opId)
    , child2(child2)
    , child3(child3)
  {
    if (!child1 || !child2 || !child3)
      ERROR("  CFilterFieldFieldFieldOpExprNode::CFilterFieldFieldFieldOpExprNode(IFilterExprNode* child1, const std::string& opId, IFilterExprNode* child2, IFilterExprNode* child3)",
            "Impossible to create the new expression node, an invalid child node was provided.");
  }

  std::shared_ptr<COutputPin> CFilterFieldFieldFieldOpExprNode::reduce(CGarbageCollector& gc, CField& thisField, Time start_graph, Time end_graph) const
  {
    std::shared_ptr<COutputPin> ch1 = child1->reduce(gc, thisField, start_graph, end_graph);
    std::shared_ptr<COutputPin> ch2 = child2->reduce(gc, thisField, start_graph, end_graph);
    std::shared_ptr<COutputPin> ch3 = child3->reduce(gc, thisField, start_graph, end_graph);

    std::shared_ptr<CFieldFieldFieldArithmeticFilter> filter(new CFieldFieldFieldArithmeticFilter(gc, opId));
    ch1->connectOutput(filter, 0);
    ch2->connectOutput(filter, 1);
    ch3->connectOutput(filter, 2);

    (filter->parent_filters).resize(3);
    (filter->parent_filters)[0] = ch1;
    (filter->parent_filters)[1] = ch2;
    (filter->parent_filters)[2] = ch3;


    filter->tag = (ch1->tag || ch1->tag || ch3->tag);
    filter->start_graph = ch1->tag? ch1->start_graph : (ch2->tag? ch2->start_graph: (ch3->tag? ch3->start_graph: -1));
    filter->end_graph = ch1->tag? ch1->end_graph : (ch2->tag? ch2->end_graph: (ch3->tag? ch3->end_graph: -1));
    filter->field = &thisField;


    return filter;
  }
  
}
