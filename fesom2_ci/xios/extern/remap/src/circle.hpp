#ifndef __CIRCLE_HPP__
#define __CIRCLE_HPP__
#include "elt.hpp"
#include "node.hpp"

namespace sphereRemap {
  
double cptRadius(Elt elt);

void setCircleAndLink(Elt& elt, Node& leaf);

/* For arrays of grid elements `elt` and SS-tree nodes `leaf`,
   both of length `NE`, initialize each node with radius of encompassing circle and barycentre
   of the corresponding grid element.
   At this point the node is a leaf and contains only one element.
*/
void setCirclesAndLinks(Elt *elts, vector<Node>& leaf);

}
#endif
