#include <cassert>
#include "tree.hpp"
#include "node.hpp"
#include "elt.hpp"
#include <iostream>
#include "mpi.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <list>
#include <set>

#include "timer.hpp"
#include "mpi_routing.hpp"

namespace sphereRemap {

const int MAX_LEVEL_SIZE = 100;

double cputime();
using namespace std;

/*
CBasicTree::CBasicTree() : ri(0), levelSize(MAX_LEVEL_SIZE), root(NULL)
{
}
*/

void CBasicTree::routeNodes(vector<int>& route, vector<Node>& nodes, int assignLevel)
{
	for (int i = 0; i < nodes.size(); i++)
	{
		root->routeNode(&nodes[i], assignLevel);
		route[i] = nodes[i].route;
	}
}

void CBasicTree::routeIntersections(vector<vector<int> >& routes, vector<Node>& nodes)
{
	for (int i = 0; i < nodes.size(); i++)
		root->routeIntersection(routes[i], &nodes[i]);
}

void CBasicTree::build(vector<Node>& nodes)
{
	newRoot(1);
	insertNodes(nodes);
}

void CBasicTree::output(ostream& flux, int level)
{
	root->output(flux,level,0) ;
}
void CBasicTree::slim(int nbIts)
{
	for (int i = 0; i < nbIts; i++)
	{
		for (int level = root->level - 1; level > 0; level--)
		{
			slim2(root, level);
			ri = 0;
			emptyPool();
		}

		for (int level = 2; level < root->level; level++)
		{
			slim2(root, level);
			ri = 0;
			emptyPool();
		}
	}
}



void CBasicTree::insertNode(NodePtr node)
{
	node->tree = this;
	increaseLevelSize(0);
	push_back(node);

	NodePtr q;
	while (pool.size())
	{
		q = pool.front();
		pool.pop_front();
		q = insert(q, root);
		if (ri)
		{
			delete q;
			ri = 0;
		}
	}
}

void CBasicTree::emptyPool(void)
{
	while (pool.size())
	{
		NodePtr q = pool.front();
		pool.pop_front();
		q = insert(q, root);
		if (ri)
		{
			delete q;
			ri = 0;
		}
	}
}

void CBasicTree::push_back(NodePtr node)
{
#ifdef DEBUG
	node->parent = NULL; // will be overridden later, but for mem leak check better trigger leak as soon as possible
#endif
	pool.push_back(node);
}

void CBasicTree::push_front(NodePtr node)
{
#ifdef DEBUG
	node->parent = NULL; // will be overridden later, but for mem leak check better trigger leak as soon as possible
#endif
	pool.push_front(node);
}

void CBasicTree::increaseLevelSize(int level)
{
	levelSize[level]++;
}

void CBasicTree::decreaseLevelSize(int level)
{
	levelSize[level]--;
}

void CBasicTree::newRoot(int level)  // newroot <- root
{
	root = new Node;
	// if (level > 1) cout << " newRoot level " << level << endl;
	root->level = level;
	root->parent = 0;
	root->leafCount = 0;
// initialize root node on the sphere
  root->centre.x=1 ; root->centre.y=0 ; root->centre.z=0 ; 
	root->radius = 0.;
	root->reinserted = false;
	root->updateCount = 0;
	root->tree = this;
	levelSize[level]++;
}

CBasicTree::~CBasicTree()
{
	//FIXME uncomment the next line and figure out why it segfault sometimes
	//root->free_descendants(); // recursively deletes all nodes in the tree
	if (root) delete root;
}

void CTree::insertNodes(vector<Node>& nodes)
{
	int stepSlim = MAX_NODE_SZ*MAX_NODE_SZ*2;
	const double ratio = 1.5;
	for (int i = 0; i < nodes.size(); i++)
	{
		insertNode(&nodes[i]);

		if (root->leafCount > stepSlim) // time for slim down
		{
			slim();
			stepSlim = stepSlim * ratio;
		}
	}
}


void CSampleTree::insertNodes(vector<Node>& nodes)
{
	bool first1 = true;
	bool first2 = true;
	int stepSlim = MAX_NODE_SZ * MAX_NODE_SZ * keepNodes / 4;
//	double ratio = 1 + (0.5 * (1 - (keepNodes - 1) / (1.0 * keepNodes))) ;
	double ratio = 1.5 ;
  int i ;
  
//  cout<<"CSampleTree::insertNodes  : nb node to be inserted : "<<nodes.size()<<endl ;
  for (i = 0; i < nodes.size(); i++)
	{
    insertNode(&nodes[i]);

		if (root->leafCount > stepSlim && levelSize[assignLevel] < keepNodes-2) // time for slim down
		{
			slim();
			stepSlim = stepSlim * ratio;
		}

    
    if (levelSize[assignLevel] == keepNodes-2 && first1)
		{
      slim();
			first1 = false;
		}

		if (levelSize[assignLevel] == keepNodes-1 && first2)
		{
      slim();
      first2=false ;
		}

   	if (levelSize[assignLevel] >= keepNodes) slim();
   	if (levelSize[assignLevel] > keepNodes) slim();
    if (levelSize[assignLevel] > keepNodes) slimAssignedLevel() ;

    if (levelSize[assignLevel] >= keepNodes) 
		{
      if (levelSize[assignLevel] > keepNodes)
      {
//        cout<<"assign Level : "<<assignLevel<< "     levelSize[assignLevel] :"<<levelSize[assignLevel]<<"   keepNodes : "<<keepNodes<<endl ;
        removeExtraNode() ;
      }
      break ;
 		}
	}
//	cout << "SampleTree build : nb Node inserted : " << i << endl;

}

void CSampleTree::slimAssignedLevel()
{
  for(int i=MIN_NODE_SZ;i<=MAX_NODE_SZ;i++)
  {
    int levelSizeOrigin=levelSize[assignLevel] ;
    slim2(root, assignLevel,i);
    ri = 0;
    int levelSizeBefore=levelSize[assignLevel] ;
    isActiveOkSplit=true ;
    emptyPool();
//    cout<<"assign Level : "<<assignLevel<<"  MinNodeSize :"<<i<< "     levelSize[assignLevel] : "<<levelSizeOrigin<<"->"<<levelSizeBefore<<"->" <<levelSize[assignLevel]<<"   keepNodes : "<<keepNodes<<"  "<<"CanSplit " <<canSplit()<<endl ;
    if (levelSize[assignLevel]<=keepNodes) break ;
  }

}

void CSampleTree::removeExtraNode(void)
{
  std::list<NodePtr> nodeList ;
  std::list<NodePtr>::iterator it1,it2, rm ;

  root->getNodeLevel(assignLevel,nodeList) ;
  double dist,minDist ;
 
  
  for (int n=0; n<levelSize[assignLevel]-keepNodes ; ++n)
  {
    minDist=-1 ;
    for(it1=nodeList.begin();it1!=nodeList.end();++it1)
    {
      dist=0 ;
      for(it2=nodeList.begin();it2!=nodeList.end();++it2) dist+=arcdist((*it1)->centre,(*it2)->centre) ;
      if (minDist > dist || minDist < 0.)
      {
        minDist=dist ;
        rm=it1 ;
      }
    }
    (*rm)->toDelete=true ;
    nodeList.erase(rm) ;
    
  }
  root->removeDeletedNodes(assignLevel) ;
  isActiveOkSplit=true ;
  emptyPool();
}

}
