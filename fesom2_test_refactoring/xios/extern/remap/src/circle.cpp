#include <algorithm>
#include "node.hpp"
#include "elt.hpp"

#include "circle.hpp"

namespace sphereRemap
{

  /* computes the radius of the smallest circle
     around the barycentre `x` of grid element `elt`
     which contains all vertices of `elt`. */
  double cptRadius(Elt elt)
  {
  	double squareradius = 0.0;
  	int argmax = 0;
  	// use cheep `squaredist` to find farthest vertex and compute radius as arcdistance only once
  	for (int i = 0; i < elt.n; i++)
  	{
  		double dist2 = squaredist(elt.x, elt.vertex[i]);
  		if (dist2 > squareradius)
  		{
  			squareradius = dist2;
  			argmax = i;
  		}
  	}
  	return arcdist(elt.x, elt.vertex[argmax]) + 1e-10;
  }

  void setCircleAndLink(Elt& elt, Node& leaf)
  {
  	leaf.centre = elt.x;
  	leaf.radius = cptRadius(elt);
  	leaf.data = &elt;
  }
  
  void setCirclesAndLinks(Elt *elts, vector<Node>& nodes)
  {
  	for (int i = 0; i < nodes.size(); i++)
	  	setCircleAndLink(elts[i], nodes[i]);
  }
}
