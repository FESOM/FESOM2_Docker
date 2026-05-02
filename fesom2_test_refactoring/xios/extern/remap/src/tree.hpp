#ifndef  __TREE_HPP__
#define __TREE_HPP__
//#include <list>
#include <deque>
#include <vector>
#include "elt.hpp"
#include "node.hpp"

namespace sphereRemap {

using namespace std;
extern const int MAX_LEVEL_SIZE ;

class CBasicTree
{
public:

	NodePtr root; /* The main tree is stored as Nodes which can be reached through traversal starting here */
	NodePtr ref; // FIXME this reference, set by a node is odd, try to remove
	int ri; /** this is set to one by a node in case of reinsertion */
	vector<int> levelSize; /** e.g. levelSize[0] == leafs.size() */
	vector<Node> leafs; /** leafs are stored in vector for easy access and rest of the tree nodes as separate allocations, only reachable through tree traversal */

	CBasicTree() : ri(0), levelSize(MAX_LEVEL_SIZE), root(NULL), isAssignedLevel(false), okSplit(true), isActiveOkSplit(false) {} 
	~CBasicTree(); 
	void build(vector<Node>& nodes);
	void slim(int nbIts = 1);
	virtual void insertNodes(vector<Node>& node) = 0;

	void routeNodes(vector<int>& route, vector<Node>& nodes, int assignLevel);
	void routeIntersections(vector<vector<int> >& route, vector<Node>& nodes);

	void push_back(NodePtr node);
	void push_front(NodePtr node);
	void increaseLevelSize(int level);
	void decreaseLevelSize(int level);
	void newRoot(int level);
	void insertNode(NodePtr node);
  void output(ostream& flux, int level) ;

	int keepNodes;
  bool isAssignedLevel ; 
  int assignLevel;
  bool isActiveOkSplit ;
  bool canSplit(void)
  {
    if (isActiveOkSplit && levelSize[assignLevel] >= keepNodes ) okSplit=false ;
    return okSplit ;
  }    

  
private:
	deque<NodePtr > pool;
	
  bool okSplit ;
 
protected:
  void emptyPool();
  CBasicTree(int keepNodes_, int assignLevel_) : ri(0), levelSize(MAX_LEVEL_SIZE), root(NULL), keepNodes(keepNodes_), assignLevel(assignLevel_), isAssignedLevel(true), okSplit(true), isActiveOkSplit(false) {} 
};

class CTree : public CBasicTree
{
public:
	void insertNodes(vector<Node>& nodes);
};

class CSampleTree : public CBasicTree
{

public:
	CSampleTree(int keepNodes_, int assignLevel_) : CBasicTree(keepNodes_,assignLevel_) {}
  void slimAssignedLevel() ;
  void removeExtraNode(void) ;
	void insertNodes(vector<Node>& nodes);
};

}
#endif
