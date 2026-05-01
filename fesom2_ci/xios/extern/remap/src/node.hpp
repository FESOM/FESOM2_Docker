#ifndef __NODE_H__
#define __NODE_H__

#include <cassert>
#include <list>
#include <vector>
#include <set>
#include <map>
#include <iostream>

#include "triple.hpp"

namespace sphereRemap {

struct Circle
{
	Coord centre;
	double radius;
};

const int MIN_NODE_SZ = 5;
const int MAX_NODE_SZ = MIN_NODE_SZ*2; /* maximum number of elements per tree-node */
const int TYPICAL_NODE_SZ = (2*MAX_NODE_SZ + MIN_NODE_SZ)/3;
const double frac = 0.3;

const int CLOSEST = 1;
const int FARTHEST = -1;

class CBasicTree;
struct Node;


//#ifdef DEBUG
//enum alloc_stat { ALLOCATED, DELETED, BORROWED /* mostly means allocated as part of new[] or C++ container */ };
//struct mem_info { int ref_cnt; enum alloc_stat stat; };
////extern std::map<void*, struct mem_info> _mem_deb; // reference counter
//std::map<void*, struct mem_info> _mem_deb; // reference counter
//
//// throughout the whole class, ignore NULL pointers
//class NodePtr
//{
//private:
//	Node* ptr;
//
//	void unlink();
//
//public:
//	NodePtr() : ptr(NULL) {}
//	NodePtr(Node* ptr) : ptr(ptr)
//	{
//		if (ptr)
//		{
//			// if ptr does not exist yet just add it, this is not the problem we want so solve here
//			// if we do not do this, we run in troubles with pointers on targets allocated as part of array
//			// start with 1 since we assume this target is always reachable through the array
//			// (we do not want to fix array leaks here)
//			if (_mem_deb.count(ptr) == 0)
//			{
//				_mem_deb[ptr].ref_cnt = 1;
//				_mem_deb[ptr].stat = BORROWED;
//			}
////std::cerr << "cnstr ptr " << ptr << " cnt " << _mem_deb[ptr].ref_cnt << std::endl;
//			_mem_deb[ptr].ref_cnt += 1;
//		}
//	}
//	NodePtr(const NodePtr& other) : ptr(other.ptr)
//	{
////std::cerr << "copy " << ptr << " cnt " << _mem_deb[ptr].ref_cnt << std::endl;
//		if (ptr) _mem_deb[ptr].ref_cnt += 1;
//	}
//	~NodePtr()
//	{
//		if (ptr and _mem_deb.count(ptr)) // if our target has been deleted, that's fine
//		{
//			// Target of ptr is not deleted. We want same behaviour as regular pointer here.
////std::cerr << "destr ptr " << ptr << " cnt " << _mem_deb[ptr].ref_cnt << std::endl;
//			unlink();
//		}
//	}
//	NodePtr& operator=(const NodePtr& other)
//	{
//		if (ptr == other.ptr) return *this;
//		if (ptr and _mem_deb.count(ptr)) // if our target has been deleted, that's fine
//		{
////std::cerr << "overr ptr " << ptr << " cnt " << _mem_deb[ptr].ref_cnt << std::endl;
//			unlink();
//		}
//		ptr = other.ptr;
//		if (ptr) _mem_deb[ptr].ref_cnt += 1;
//		return *this;
//	}
//	Node& operator*() const
//	{
//		assert(ptr);
//		return *ptr;
//	}
//	Node* operator->() const
//	{
//		assert(ptr);
//		return ptr;
//	}
//	operator Node*() const
//	{
//		return ptr;
//	}
//};
//
//void memory_report();
//
//#else
//typedef Node* NodePtr;
//#endif

typedef Node* NodePtr;

struct Node
{
	int level; /* FIXME leafs are 0 and root is max level? */
	int leafCount; /* number of leafs that are descendants of this node (the elements in it's cycle) */
	Coord centre;
	double radius;
	NodePtr parent, ref;
	std::vector<NodePtr> child;
	std::list<NodePtr> intersectors;
	bool reinserted;
	int updateCount;  // double var;
	CBasicTree* tree;
	void *data;
	int route;
  bool toDelete ;

	Node() : level(0), leafCount(1), centre(ORIGIN), radius(0), reinserted(false), updateCount(0), toDelete(false) {}
	Node(const Coord& centre, double radius, void *data)
		: level(0), leafCount(1), centre(centre), radius(radius), reinserted(false), updateCount(0), data(data), toDelete(false) {}

//#ifdef DEBUG
////	void *operator new[](size_t size)
////	{
////		void *new_array = ::new char[size];
////std::cerr << "new vector " << new_array << " cnt " << std::endl;
////		return new_array;
////	}
//	void *operator new(size_t size)
//	{
//		assert(size == sizeof(Node)); // also sanity? I found this on the internet, better save than sorry
//		void *new_node = ::new char[size];
//		assert(_mem_deb.count(new_node) == 0); // sanity that new is returned new pointer (should not happen even if code is broke)
//		_mem_deb[new_node].ref_cnt = 0;
//		_mem_deb[new_node].stat = ALLOCATED;
////std::cerr << "new " << new_node << " cnt " << 0 << std::endl;
//		return new_node;
//	}
//
////	void operator delete[](void *ptr)
////	{
////		if (ptr)
////		{
////std::cerr << "delete vector " << ptr << " cnt " << _mem_deb_counter[ptr] << std::endl;
////			_mem_deb.erase(ptr);
////			::delete [] ptr;
////		}
////	}
//
//	void operator delete(void *ptr)
//	{
//		if (ptr)
//		{
//			assert(_mem_deb[ptr].ref_cnt); // if this fails it means Matthias is wrong (because he thinks it cannot fail)
//			// IF THIS FAILS we handed an invalid pointer to delete (DOUBLE FREE, POINTER ON STL CONTAINER, etc)
//			assert(_mem_deb[ptr].stat == ALLOCATED);
////std::cerr << "delete " << ptr << " cnt " << _mem_deb[ptr].ref_cnt << std::endl;
//			// if/since there are still references to this Node, we cannot delete the memory,
//			// because otherwise it might get allocate it to a new Node and the reference will point to this node
//			// so we mark that delete has been called and free the memory when the last reference disappears
//			_mem_deb[ptr].stat = DELETED;
//		}
//	}
//#endif

	void move(const NodePtr node);
	void remove(const NodePtr node);
	void inflate(const NodePtr node);
	void update();
  void output(std::ostream& flux, int level, int color) ;
	NodePtr closest(std::vector<NodePtr>& list, int n = CLOSEST);
	NodePtr farthest(std::vector<NodePtr>& list);
	void findClosest(int level, NodePtr src, double& minDist, NodePtr &closest);

	void search(NodePtr node);
	bool centreInside(Node &node);
	bool intersects(NodePtr node);
	bool isInside(Node &node);
	int incluCheck();
  void checkParent(void) ;
	void printChildren();
	void assignRoute(std::vector<int>::iterator& rank, int level);
	void assignCircleAndPropagateUp(Coord *centres, double *radia, int level);
	void printLevel(int level);
	void routeNode(NodePtr node, int level);
	void routingIntersecting(std::vector<Node>* routingList, NodePtr node);
	void routeIntersection(std::vector<int>& routes, NodePtr node);
  void getNodeLevel(int level,std::list<NodePtr>& NodeList) ;
  bool removeDeletedNodes(int assignLevel) ;
  void free_descendants();
};

bool transferNode(NodePtr thIs, NodePtr parent, NodePtr node);
void findNeighbour(NodePtr thIs, NodePtr node, std::set<NodePtr>& neighbourList);
NodePtr split(NodePtr);
NodePtr reinsert(NodePtr);
NodePtr insert(NodePtr, NodePtr);
void slim2(NodePtr thIs, int level, int minNodeSize=MIN_NODE_SZ);

}
#endif
