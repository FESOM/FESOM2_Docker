#ifndef __INTERSECTION_YM_HPP__
#define __INTERSECTION_YM_HPP__

#include <vector>
#include "elt.hpp"

namespace sphereRemap {

double intersect_ym(Elt *a, Elt *b) ;
void createGreatCirclePolygon(const Elt& element, const Coord& pole, vector<Coord>& coordinates) ;

}

#endif
