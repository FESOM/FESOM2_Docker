#ifndef  __TREE_H__
#define __TREE_H__
#include <iostream>
#include "triple.hpp"

namespace sphereRemap {

struct CRemapGrid
{
	Coord pole;
	int numElts;
};

Coord readPole(std::istream&);

extern CRemapGrid srcGrid;
extern CRemapGrid tgtGrid;

}

#endif
