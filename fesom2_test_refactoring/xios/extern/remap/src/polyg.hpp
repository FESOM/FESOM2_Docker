#include "elt.hpp"

namespace sphereRemap {


Coord barycentre(const Coord *x, int n);

void orient(int n, Coord *vertex, Coord *edge, double *d, const Coord &g);

void normals(Coord *x, int n, Coord *a);

double alun(double b, double d);

double airbar(int N, const Coord *x, const Coord *c, double *d, const Coord &pole, Coord &gg);

double polygonarea(Coord *x, int n);
Coord exact_barycentre(const Coord *x, int n) ;

int packedPolygonSize(const Elt& e);
void packPolygon(const Elt& e, char *buffer, int& pos);
void unpackPolygon(Elt& e, const char *buffer, int& pos);
void packIntersection(const Elt& e, char *buffer, int& pos);
void unpackIntersection(Elt *e, const char *buffer);
int packIntersectionSize(const Elt& e);
double triarea( const Coord& A, const Coord& B, const Coord& C) ;

}
