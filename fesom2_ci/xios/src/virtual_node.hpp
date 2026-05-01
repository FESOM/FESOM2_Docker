/*!
   \file virtual_group.hpp
   \author Ha NGUYEN
   \date 14 Aprill 2015
   \since 14 April 2015

   \brief Class template for virtual nodes
 */
#ifndef __XIOS_VIRTUAL_NODE_HPP__
#define __XIOS_VIRTUAL_NODE_HPP__

namespace xios {
/*!
\class CVirtualNode
On processing xml file, there are several cases in which a node contains other node type.
These different nodes are stored in a virtual node.
*/
template<typename NodeType>
class CVirtualNode
{
public:
  CVirtualNode() { this->setVirtualNode(); }
  virtual ~CVirtualNode() {}

protected:
  void setVirtualNode(NodeType* newVirtualNode) { this->virtualNode_ = newVirtualNode; }
  void setVirtualNode() { this->setVirtualNode(NodeType::create());}
  NodeType* getVirtualNode() const { return virtualNode_; }

protected:
  NodeType* virtualNode_;
};

}
#endif // __XIOS_VIRTUAL_NODE_HPP__
