#ifndef  __MISC_H__
#define  __MISC_H__

#include <stdlib.h> // srand
#include <algorithm> // swap
#include <cmath> // pow
#include <vector> // randomizeArray

namespace sphereRemap {

// y = b^x
// always round down to integer

// b unknown
static int iroot(int x, int y)
{
	// FIXME: is this save to do? will it work correctly for integer cases like iroot(3, 8)?
	// (what if roundoff errors produce pow(3., 1./8.) = 1.99999999999995? )
	return pow(y, 1./x); 
}

// y unknown
static int ipow(int basis, int exponent)
{
        int res = 1;
        while (exponent--) res *= basis;
        return res;
}

// x unknown
// integer logarithm, rounds down
static int ilog(int base, int arg)
{
	int x = 0;
	for (int y = base; y <= arg; y *= base)
		x++;
	return x;
}


/* provide an array of indices that are in random order but every index appears exatly 1 time */
static void randomizeArray(std::vector<int>& array)
{
	srand (3);

	for (int i = 0; i < array.size(); i++)
		array[i] = i;

	for (int i = 0; i < 3 * array.size(); i++)
	{
		int ind1 = rand() % array.size();
		int ind2 = rand() % array.size();
		std::swap(array[ind1], array[ind2]);
	}
}

}
#endif
