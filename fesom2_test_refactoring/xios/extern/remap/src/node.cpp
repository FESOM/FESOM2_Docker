#include "mpi.hpp"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cassert>
#include "tree.hpp"
#include "elt.hpp"
#include "intersect.hpp"
#include <vector>
#include <set>
#include <algorithm>

#include "node.hpp"

namespace sphereRemap {


#define UPDATE_EVERY 1

using namespace std;

//#ifdef DEBUG
//std::map<void*, struct mem_info> _mem_deb; // reference counter
//
//void NodePtr::unlink()
//{
//	_mem_deb[ptr].ref_cnt -= 1;
//	if (_mem_deb[ptr].ref_cnt == 0) // we were last reference
//	{
//		if (_mem_deb[ptr].stat == DELETED) // delete has already been called, everything is fine, free memory now
//		{
//			_mem_deb.erase(ptr);
//			::delete [] ((char *) ptr);
//		}
//		else // no more pointer, but memory not freed -> memory leak !!
//		{
//			std::cerr << "WARNING: Memory leak created at address " << ptr << ".";
//			assert(_mem_deb[ptr].stat == ALLOCATED); // and not BORROWED
//#ifdef AUTO_LEAK_FIX
//			// free automatically, just for fun
//			_mem_deb.erase(ptr);
//			ptr->~Node(); // call destructor, since `Node::delete` has not been applied it has not been called
//			::delete [] ((char *) ptr);
//			std::cerr << " LEAK FIXED.";
//#endif
//
//			std::cerr << std::endl;
//		}
//	}
//}
//
//void memory_report()
//{
//	for (std::map<void*, struct mem_info>::iterator it = _mem_deb.begin(); it != _mem_deb.end(); it++)
//	{
//		if (it->second.stat == BORROWED) continue;
//		std::cerr << "Node at " << it->first << " has " << it->second.ref_cnt << " references to it and "
//		          << ((it->second.stat == DELETED) ? "has" : "has *not*") << " been deleted." << std::endl;
//#ifdef AUTO_LEAK_FIX
//		if (it->second.stat == ALLOCATED) // `Node::delete` has not been called
//			((Node *) it->first)->~Node();
//		delete [] ((char *)  it->first);
//#endif
//	}
//}
//
//int ref_cnt(void *ptr)
//{
//	return _mem_deb[ptr].ref_cnt;
//}
//#endif

int compareDist(NodePtr n1, NodePtr n2)
{
	return squaredist(n1->tree->ref->centre, n1->centre)
	     < squaredist(n2->tree->ref->centre, n2->centre);
}

/* On level `level` find the node in our subtree that is closest to `src` and return through argument `closest`.
   The return value is just for recursive calling */
void Node::findClosest(int level, NodePtr src, double& minDist2, NodePtr &closest)
{
	double r2;

	r2 = squaredist(src->centre, this->centre);
	if (level == this->level)
	{
		if (r2 < minDist2 || closest == NULL)
		{
			minDist2 = r2;
			closest = this;
		}
	}
	else if (r2 < radius*radius)
	{
		for(int i = 0; i < child.size(); i++)
			child[i]->findClosest(level, src, minDist2, closest);
	}
}

NodePtr Node::farthest(vector<NodePtr >& list)
{
	assert(this);
	double dmax = -HUGE_VAL;
	NodePtr node = NULL;
	for (size_t i=0; i < list.size(); i++)
	{
		double d = ds(this->centre, list[i]->centre);
		if (d > dmax) {
			node = list[i];
			dmax = d;
		}
	}
	return node;
}

/* returns element in `list` cosest to us (`this`) by meassure `ds`.
   If `n` is negative finds element furthest away instead. */
NodePtr Node::closest(vector<NodePtr >& list, int n)
{
	assert(this);
	double dmin2 = (n>0) ? HUGE_VAL : -HUGE_VAL;
	NodePtr node = NULL;
	for (int i = 0; i < list.size(); i++)
	{
		double d2 = squaredist(this->centre, list[i]->centre);
		if (n * (d2 - dmin2) < 0)
		{
			node = list[i];
			dmin2 = d2;
		}
	}
	return node;
}

// make sure we will be able to accomodate `node`
void Node::move(const NodePtr node)   // this->leafCount may be 0
{
	double w = double(node->leafCount)/double(node->leafCount + this->leafCount);
	Coord oldCentre = this->centre;
	this->centre = proj(this->centre * (1-w) + node->centre * w);
	this->leafCount += node->leafCount;
	this->radius += arcdist(oldCentre, this->centre) + 1e-9;
}

void Node::remove(const NodePtr node)
{
	if (node == NULL) return;
	double w = double(node->leafCount) / this->leafCount;
	Coord newCentre = proj(this->centre - node->centre * w);
	this->leafCount -= node->leafCount;
	this->radius += arcdist(newCentre, this->centre) + 1e-9;
	this->centre = newCentre;
	this->updateCount++;
}

void Node::inflate(const NodePtr node)
{
	double d = arcdist(this->centre, node->centre);
	double r = node->radius;
	if (this->radius < d + r)
		this->radius = d + r + 1e-9;
}

/* recomputes the radius which currently might be much larger than necessary */
void Node::update()
{
	Coord centre = ORIGIN;
	int n = 0;
	for (int i = 0; i < this->child.size(); i++) {
		centre = centre + this->child[i]->centre * this->child[i]->leafCount;
		n += this->child[i]->leafCount;
	}
	this->centre = proj(centre);
	this->leafCount = n;

	double R = 0;
	for (int i = 0; i < this->child.size(); i++)
	{
		double d = arcdist(this->centre, this->child[i]->centre);
		double r = this->child[i]->radius;
		if (R < d + r) R = d + r;
	}
	this->radius = R + 1e-9;
	this->updateCount = 0;
	if (child.size())
		level = child[0]->level + 1;
}

void Node::output(ostream& flux, int level, int color)
{
  if (level==this->level)
  {
    flux<<centre.x<<" , "<<centre.y<<" , "<<centre.z<<" , "<<radius<<endl ;
  }
  else
  {
    for (int i = 0; i < this->child.size(); i++) child[i]->output(flux,level,color) ;
  }
}


/* void Node::append(NodePtr node);
{
	if (node->level == this->level -1)
	{
		// new node is one level lower (correct level)
		this->child.append(node);
		node->parent = this;
	}
	else if (node->level < this->level -1)
	{
		// if new node is on even lower level, recursively append to closest child
		node->closest(this->child)->append(node);
	}
	else
	{
		cerr << "Error: Attempted node insertion with invalid level." << endl;
		exit(1);
	}
}*/

bool find_in_tree1(Node* node)
{
	if (node == node->tree->root) return true;
	if (node->parent == NULL)
	{
		cerr << "Cannot find!" << endl;
		return false;
	}
	return find_in_tree1(node->parent);
}

bool find_in_tree2(NodePtr node, NodePtr ref)
{
	for (int i = 0; i < ref->child.size(); i++)
	{
		if (node == ref->child[i])
		{
			cerr << "find2: " << ref << " -> " << ref->child[i] << endl;
			return true;
		}
		else if (find_in_tree2(node, ref->child[i]))
		{
			cerr << "find2: " << ref << " -> " << ref->child[i] << endl;
			return true;
		}
	}
	return false;
}


/* This appends `this` to the node `node` */
NodePtr insert(NodePtr thIs, NodePtr node)
{
	int la = thIs->level; // node to be inserted
	int lb = node->level; // node where insertation
	assert(la < lb); // node to be inserted must have lower level then parent
	//if (thIs->parent) assert(find_in_tree1(thIs) == true);
	NodePtr q = NULL;
	NodePtr chd = NULL;
	node->move(thIs);
	if (la == lb - 1)
	{
    node->child.push_back(thIs);
		thIs->parent = node;
		if (node->child.size() > MAX_NODE_SZ &&  node->tree->canSplit() ) // with us as additional child `node` is now too large :(
			return (node->reinserted || node->parent == NULL) ? split(node) : reinsert(node);
	}
	else // la < lb - 1
	{
		chd = thIs->closest(node->child);
		q = insert(thIs, chd);
	}
	if ((node->updateCount + 1) % UPDATE_EVERY == 0)
		node->update();
	else
	{
		if (q) node->remove(q);
		node->inflate(chd);
	}


  return q;
}

typedef NodePtr pNode;

/* move `frac` of our children to a new node which is returned */
NodePtr reinsert(NodePtr thIs)
{
	thIs->tree->ref = thIs;
	std::sort(thIs->child.begin(), thIs->child.end(), compareDist);
	int out = (int) (frac*thIs->child.size());

	/* make sure out is only so big that there are still MIN_NODE_SZ children after removing out */
	if (thIs->child.size() - out < MIN_NODE_SZ) out = thIs->child.size() - MIN_NODE_SZ;

  
	/* transfere out children from us to a new node q which will be returned */
	NodePtr q = new Node;
	q->tree = thIs->tree;
	q->child.resize(out);
	for (int i = thIs->child.size() - out; i < thIs->child.size(); i++)
	{
		thIs->tree->push_back(thIs->child[i]);
		int k = i - (thIs->child.size() - out);
		q->child[k] = thIs->child[i];
		q->child[k]->parent = q;
	}
	thIs->child.resize(thIs->child.size() - out);
	thIs->update();
	q->update();
	thIs->reinserted = true; // avoid infinite loop of reinserting the same node, by marking it as reinserted and stop if same node arrives at same place again
	thIs->tree->ri = 1;

	return q;
}

/* move around nodes that are far away from the centre of their parents in order reduce radia of the circles
   leading to faster look-up times because of less redundancies between nodes.
   TODO cite paper for Slim SS-tree */
void slim2(NodePtr thIs, int level, int minNodeSize)
{
	bool out;
	double distChild;

#ifdef DEBUG
//	assert(ref_cnt(thIs) >= thIs->child.size() + 1 /*parent*/ + 1 /*thIs*/);
#endif
	if (thIs->level==level)
	{
/*
		out = false;
		while (!out)
		{
			// remove child which is farthest away from the centre and try to reinsert it into the tree 
			double distMax = 0;
			int itMax = -1;

			for (int i = 0; i < thIs->child.size(); i++)
			{
				distChild = arcdist(thIs->centre, thIs->child[i]->centre) + thIs->child[i]->radius;
				if (distChild > distMax)
				{
					distMax = distChild;
					itMax = i;
				}
			}
			if (transferNode(thIs->tree->root, thIs, thIs->child[itMax]))
			{
				thIs->child.erase(thIs->child.begin()+itMax);
				out = false;
			}
			else
				out = true;

			if (thIs->child.size() < minNodeSize) out = true;
		}
*/
    if (thIs->tree-> isActiveOkSplit && thIs->tree->levelSize[thIs->tree->assignLevel] <= thIs->tree->keepNodes)
    {

      return ;
    }
    for (int i = 0; i < thIs->child.size(); i++)
		{
      std::vector<NodePtr> before;
      if (transferNode(thIs->tree->root, thIs, thIs->child[i]))
      {
        before=thIs->child ;
        thIs->child.erase(thIs->child.begin()+i);
        i--;
      }
    }
        

		if (thIs->child.size() < minNodeSize  && thIs->level < thIs->tree->root->level)
		{
			thIs->tree->decreaseLevelSize(thIs->level);
			for(int i = 0; i < thIs->child.size(); i++)
				thIs->tree->push_back(thIs->child[i]);
			thIs->child.resize(0);
		}
		else thIs->update();
	}
	else
	{
		int newChildCount = 0;
		for (int i = 0; i < thIs->child.size(); i++)
		{
			if (thIs == thIs->tree->root)
			{
				// keep at least one child for root
				if (i == thIs->child.size()-1 && newChildCount == 0)
				{
					thIs->child[newChildCount] = thIs->child[i];
					newChildCount++;
					break;
				}
			}

			slim2(thIs->child[i], level);
			if (thIs->child[i]->child.size() != 0) // thIs->child[i] is not a leaf
			{
				thIs->child[newChildCount] = thIs->child[i];
				newChildCount++;
			} /* else FIXME sometimes this child must be deleted (otherwise leak) sometimes not (otherwise segfault)
			                maybe delete not here but when transfered
				delete thIs->child[i]; // if our child does not make any grand-children what good is it? -> remove!
*/

		}
		thIs->child.resize(newChildCount);

		if (thIs->child.size() < MIN_NODE_SZ && thIs->level < thIs->tree->root->level)
		{
			thIs->tree->decreaseLevelSize(thIs->level);
			for (int i = 0; i < thIs->child.size(); i++)
				thIs->tree->push_front(thIs->child[i]);
			thIs->child.resize(0);
		}
		else thIs->update();
	}

}

bool transferNode(NodePtr thIs, NodePtr parent, NodePtr node)
{
  if (parent == thIs) return false;

	if (thIs->level == parent->level)
	{
		if ( (thIs->child.size() < MAX_NODE_SZ || thIs->tree->isActiveOkSplit) && thIs->child.size() >= MIN_NODE_SZ)
		{
			insert(node, thIs);
			return true;
		}
		else
			return false;
	}
	else
	{
		for (int i = 0; i < thIs->child.size(); i++)
		{
			if (arcdist(thIs->child[i]->centre, node->centre) + node->radius < thIs->child[i]->radius)
			{
				if (transferNode(thIs->child[i], parent, node))
				{
					thIs->update();
					return true;
				}
			}
		}
		return false;
	}
}



NodePtr split(NodePtr thIs)
{
	thIs->tree->increaseLevelSize(thIs->level);
	NodePtr p = new Node;
	NodePtr q = new Node;
	p->level = q->level = thIs->level;
	p->reinserted = q->reinserted = false;
	p->parent = q->parent = thIs->parent;
	p->tree = q->tree = thIs->tree;


	p->child.resize(MAX_NODE_SZ/2);
	q->child.resize(MAX_NODE_SZ/2 + 1);
	assert(thIs->child.size() == MAX_NODE_SZ+1);
	thIs->tree->ref = thIs->closest(thIs->child, FARTHEST); // farthest from centre
	std::sort(thIs->child.begin(), thIs->child.end(), compareDist);
	for (int i = 0; i < MAX_NODE_SZ+1; i++)
		assert(thIs->child[i]->parent == thIs);
	for (int i = 0; i < MAX_NODE_SZ/2 + 1; i++)
		q->child[i] = thIs->child[i];
	for (int i = MAX_NODE_SZ/2+1; i<MAX_NODE_SZ+1; i++)
		p->child[i-MAX_NODE_SZ/2-1] = thIs->child[i];
	for (int i = 0; i < MAX_NODE_SZ/2 + 1; i++)
		q->child[i]->parent = q;
	for (int i = MAX_NODE_SZ/2+1; i < MAX_NODE_SZ+1; i++)
		p->child[i-MAX_NODE_SZ/2-1]->parent = p;
	p->update();
	q->update();
   
	if (squaredist(thIs->centre, q->centre) < squaredist(thIs->centre, p->centre))
		swap(p, q);

	thIs->child = p->child; // now our children do not know we are their parents and believe p is their parent
	for (int i = 0; i < thIs->child.size(); i++)
		thIs->child[i]->parent = thIs;
	thIs->reinserted = p->reinserted;
	thIs->update();
	delete p;

	if (thIs == thIs->tree->root) // root split
	{
		// since we currently are root, make new root and make us and q its children
		thIs->tree->newRoot(thIs->level + 1);
		thIs->tree->root->child.push_back(thIs);  thIs->parent = thIs->tree->root;
		thIs->tree->root->child.push_back(q);     q->parent    = thIs->tree->root;
		thIs->tree->root->update();
	}
	else
	{
		thIs->tree->push_front(q);
	}  // push_front?

  	return q;
}

/* Assuming we are a leaf push all leafs into our list of intersectors
   that are descendant of node and whoes circle intersects ours.
*/
void Node::search(NodePtr node)
{
	assert(this->level == 0);
	int Nchild = node->child.size();
	if (this->intersects(node)) {
		if (node->level == 0)
			this->intersectors.push_back(node);
		else
			for (int i=0; i<Nchild; i++)
				search(node->child[i]);
	}
}

/* FIXME this should not be in node.cpp and getNeighbours should not be part of the SS-tree
   this is mapper specific */
void findNeighbour(NodePtr thIs, NodePtr node, set<NodePtr >& neighbourList)
{
	if (thIs->level==0)
	{
		Elt* elt1= (Elt*)(thIs->data);
		Elt* elt2= (Elt*)(node->data);
		if (isNeighbour(*elt1, *elt2)) neighbourList.insert(thIs);
	}
	else
	{
		for(int i=0; i<thIs->child.size(); i++)
			if (thIs->child[i]->intersects(node)) findNeighbour(thIs->child[i], node, neighbourList);
	}
}

bool Node::intersects(NodePtr node)
{
	double d = arcdist(this->centre, node->centre);
	double r = this->radius;
	double R = node->radius;
	return (d < r + R + 1e-9) ? true : false;
}

bool Node::centreInside(Node &node)
{
	double d = arcdist(this->centre, node.centre);
	double R = node.radius;
	return (d < R + 1e-9) ? true : false;
}

bool Node::isInside(Node &node)
{
	double d = arcdist(this->centre, node.centre);
	double r = this->radius;
	double R = node.radius;
	return (d + r < R + 1e-9) ? true : false;
}

int Node::incluCheck()
{
	if (this->level == 0) return 0;
	int nOutside = 0;
	int n = this->child.size();  // cout << "n = " << n << endl;
	for (int i=0; i<n; i++)
	{
		if (!this->child[i]->isInside(*this))
		{
			cout << "Node of level " << this->level << " does not contain its "
				<< i << "th child\n";
			nOutside++;
		}
		nOutside += this->child[i]->incluCheck();
	}
	return nOutside;
}

void Node::checkParent(void)
{
  int childSize = child.size() ;
  
  for (int i = 0; i < childSize; i++)
		assert(child[i]->parent == this);

  if (level>0) for (int i = 0; i < childSize; i++) child[i]->checkParent() ;
}
  
void Node::printChildren()
{
	cout << "level " << this->level << ", centre ";
	cout << "level " << this->level << ", centre " << this->centre << "\t r = " << this->radius << endl;
	cout << this << " p: " << this->parent << endl;
	int n = this->child.size();
	for (int i=0; i<n; i++)
	{
		NodePtr child = this->child[i];
		cout << "fils " << i << ": centre " << child->centre << "\t r = " << child->radius << endl;
		cout << "dist to center " << arcdist(this->centre, child->centre) <<
		        " d + R = " << arcdist(this->centre,child->centre)+child->radius << endl;
	}
}

void Node::assignRoute(std::vector<int>::iterator& rank, int level)
{
	if (this->level==level)
	{
		route = *rank;
		rank++;
	}
	else
	{
		for (int i = 0; i < child.size(); i++)
			child[i]->assignRoute(rank, level);
	}
}

void Node::assignCircleAndPropagateUp(Coord *centres, double *radia, int level)
{
	if (this->level == level)
	{
		// assign
		centre = centres[route];
		radius = radia[route];
		free_descendants(); // levels of sample tree beyond `level` will not be used any more
		child.resize(0);
		this->level = 0;
	}
	else
	{
		for (int i = 0; i < child.size(); i++)
			child[i]->assignCircleAndPropagateUp(centres, radia, level);
		update(); // propagate up
	}
}

/* Route node `node` within the subtree attached to us.
 `level` is the level one which to assign
*/
// Each sample node has a rank randomly assigned to it, assign `node` from full tree
void Node::routeNode(NodePtr node, int level)
{
	NodePtr closest;

	double distMin2 = 0; // squared distance
	closest = NULL;
	if (tree->root == this)
		findClosest(level, node, distMin2, closest);

	if (closest != NULL && tree->root == this)
		/* When is this point reached?
		   if the preceeding findClosest was called and succesed to set closest
		   findClosest sets closest if we are `level` or src is in our circle (=> belongs to child of ours)
		   => reached if we are not `level` and node is not child of us
		*/
		node->route = closest->route;
	else  /* find closest was not successfull or we were not root */
	{
		if (this->level == level)
			node->route = this->route;
		else /* not yet right level => go down one more */
			node->closest(this->child)->routeNode(node, level);
	}
}

void Node::routeIntersection(vector<int>& routes, NodePtr node)
{
	if (level == 0)
	{
		routes.push_back(this->route);
	}
	else
	{
		for (int i = 0; i < child.size(); i++) {
			if (child[i]->intersects(node))
				child[i]->routeIntersection(routes, node);
		}
	}
}

void Node::routingIntersecting(vector<Node> *routingList, NodePtr node)
{
	if (level==0)
	{
		int rank = route;
		routingList[rank].push_back(*node);
	}
	else
	{
		for (int i = 0; i < child.size(); i++) {
			if (child[i]->intersects(node))
				child[i]->routingIntersecting(routingList, node);
		}
	}
}

void Node::free_descendants()
{
	for (int i = 0; i < child.size(); i++)
	{
		child[i]->free_descendants();
		if (child[i]->level) // do not attempt to delete leafs, they are delete through leafs vector
			delete child[i];
	}
}

void Node::getNodeLevel(int assignLevel, std::list<NodePtr>& NodeList)
{
  if (level==assignLevel) NodeList.push_back(this) ;
  else if (level>0) for (int i = 0; i < child.size(); i++) child[i]->getNodeLevel(assignLevel,NodeList) ;
  return ;
}

bool Node::removeDeletedNodes(int assignLevel)
{
  std::vector<NodePtr> newChild ;

  if (level==assignLevel+1)
  {
    bool isUpdate=false ;
    for (int i = 0; i < child.size(); i++)
    {
      if (child[i]->toDelete)
      {
        isUpdate=true ;
        for (int j = 0; j < child[i]->child.size(); j++) tree->push_back(child[i]->child[j]) ;
        tree->decreaseLevelSize(assignLevel) ;
        delete child[i] ;
      }
      else newChild.push_back(child[i]) ;
    }

    if (isUpdate)
    {
      child=newChild ;
      update() ;
      return true ;
    }
    else return false ;
  }
  else
  {
    bool isUpdate=false ;
    for (int i = 0; i < child.size(); i++) isUpdate |= child[i]->removeDeletedNodes(assignLevel) ;
    if (isUpdate) update() ;
    return isUpdate ;
  }
}

}
