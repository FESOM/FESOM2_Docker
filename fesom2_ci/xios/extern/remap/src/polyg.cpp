/* utilities related to polygons */

#include <cassert>
#include <iostream>
#include "elt.hpp"
#include "errhandle.hpp"

#include "polyg.hpp"

namespace sphereRemap {

using namespace std;

/* given `N` `vertex`es, `N` `edge`s and `N` `d`s (d for small circles)
   and `g` the barycentre,
   this function reverses the order of arrays of `vertex`es, `edge`s and `d`s 
   but only if it is required!
  (because computing intersection area requires both polygons to have same orientation)
*/
void orient(int N, Coord *vertex, Coord *edge, double *d, const Coord &g)
{
  Coord ga = vertex[0] - g;
  Coord gb = vertex[1] - g;
  Coord vertical = crossprod(ga, gb);
  if (N > 2 && scalarprod(g, vertical) < 0)  // (GAxGB).G
  {
    for (int i = 0; i < N/2; i++)
      swap(vertex[i], vertex[N-1-i]);

    for (int i = 0; i < (N-1)/2; i++)
    {
      swap(edge[N-2-i], edge[i]);
      swap(d[i], d[N-2-i]);
    }
  }
}


void normals(Coord *x, int n, Coord *a)
{
  for (int i = 0; i<n; i++)
    a[i] = crossprod(x[(i+1)%n], x[i]);
}

Coord barycentre(const Coord *x, int n)
{
  if (n == 0) return ORIGIN;
  Coord bc = ORIGIN;
  for (int i = 0; i < n; i++)
    bc = bc + x[i];
  /* both distances can be equal down to roundoff when norm(bc) < mashineepsilon 
     which can occur when weighted with tiny area */

  assert(squaredist(bc, proj(bc)) <= squaredist(bc, proj(bc * (-1.0))));
  //if (squaredist(bc, proj(bc)) > squaredist(bc, proj(bc * (-1.0)))) return proj(bc * (-1.0));

  return proj(bc);
}

/** computes the barycentre of the area which is the difference
  of a side ABO of the spherical tetrahedron and of the straight tetrahedron */
static Coord tetrah_side_diff_centre(Coord a, Coord b)
{
  Coord n = crossprod(a,b);
        double sinc2 = n.x*n.x + n.y*n.y + n.z*n.z;
  assert(sinc2 < 1.0 + EPS);

        // exact: u = asin(sinc)/sinc - 1; asin(sinc) = geodesic length of arc ab
  // approx:
        // double u = sinc2/6. + (3./40.)*sinc2*sinc2;

  // exact  
  if (sinc2 > 1.0 - EPS) /* if round-off leads to sinc > 1 asin produces NaN */
    return n * (M_PI_2 - 1);
  double sinc = sqrt(sinc2);
        double u = asin(sinc)/sinc - 1;

        return n*u;
}

/* compute the barycentre as the negative sum of all the barycentres of sides of the tetrahedron */
Coord gc_normalintegral(const Coord *x, int n)
{
  Coord m = barycentre(x, n);
  Coord bc = crossprod(x[n-1]-m, x[0]-m) + tetrah_side_diff_centre(x[n-1], x[0]);
  for (int i = 1; i < n; i++)
    bc = bc + crossprod(x[i-1]-m, x[i]-m) + tetrah_side_diff_centre(x[i-1], x[i]);
  return bc*0.5;
}

Coord exact_barycentre(const Coord *x, int n)
{
  if (n >= 3)
  {
    return  proj(gc_normalintegral(x, n));
  }
  else if (n == 0) return ORIGIN;
  else if (n == 2) return midpoint(x[0], x[1]);
  else if (n == 1) return x[0];
}

Coord sc_gc_moon_normalintegral(Coord a, Coord b, Coord pole)
{
  double hemisphere = (a.z > 0) ? 1: -1;

  double lat = hemisphere * (M_PI_2 - acos(a.z));
  double lon1 = atan2(a.y, a.x);
  double lon2 = atan2(b.y, b.x);
  double lon_diff = lon2 - lon1;

  // wraparound at lon=-pi=pi
  if (lon_diff < -M_PI) lon_diff += 2.0*M_PI;
  else if (lon_diff > M_PI) lon_diff -= 2.0*M_PI;

  // integral of the normal over the surface bound by great arcs a-pole and b-pole and small arc a-b 
  Coord sc_normalintegral = Coord(0.5*(sin(lon2)-sin(lon1))*(M_PI_2 - lat - 0.5*sin(2.0*lat)),
                                  0.5*(cos(lon1)-cos(lon2))*(M_PI_2 - lat - 0.5*sin(2.0*lat)),
                                  hemisphere * lon_diff * 0.25 * (cos(2.0*lat) + 1.0));
  Coord p = Coord(0,0,hemisphere); // TODO assumes north pole is (0,0,1)
  Coord t[] = {a, b, p};
  if (hemisphere < 0) swap(t[0], t[1]);
  return (sc_normalintegral - gc_normalintegral(t, 3)) * hemisphere;
}


double triarea(const Coord& A, const Coord& B, const Coord& C)
{
  double a = ds(B, C);
  double b = ds(C, A);
  double c = ds(A, B);
  double tmp ;

  if (a<b) { tmp=a ; a=b ; b=tmp ; }
  if (c > a) { tmp=a ; a=c ; c=b, b=tmp;  }
  else if (c > b) { tmp=c ; c=b ; b=tmp ; }
  
  double s = 0.5 * (a + b + c);
  double t = tan(0.25*(a+(b+c))) * tan(0.25*(c-(a-b))) * tan(0.25*( c + (a-b) )) * tan(0.25*( a + (b - c)));
  if (t>0) return 4 * atan(sqrt(t));
  else
  {
    std::cout<<"double triarea(const Coord& A, const Coord& B, const Coord& C) : t < 0 !!! t="<<t<<endl ;
    return 0 ;
  }
}

/** Computes area of two two-sided polygon
   needs to have one small and one great circle, otherwise zero
   (name origin: lun is moon in french)
*/
double alun(double b, double d)
{
  double a  = acos(d);
  assert(b <= 2 * a);
  double s  = a + 0.5 * b;
  double t = tan(0.5 * s) * tan(0.5 * (s - a)) * tan(0.5 * (s - a)) * tan(0.5 * (s - b));
  double r  = sqrt(1 - d*d);
  double p  = 2 * asin(sin(0.5*b) / r);
  return p*(1 - d) - 4*atan(sqrt(t));
}

/**
  This function returns the area of a spherical element 
that can be composed of great and small circle arcs.
 The caller must ensure this function is not called when `alun` should be called instaed.
  This function also sets `gg` to the barycentre of the element.
  "air" stands for area and  "bar" for barycentre.
*/
double airbar(int N, const Coord *x, const Coord *c, double *d, const Coord& pole, Coord& gg)
{
  if (N < 3)
    return 0; /* polygons with less then three vertices have zero area */
  Coord t[3];
  t[0] = barycentre(x, N);
  Coord *g = new Coord[N];
  double area = 0;
  Coord gg_exact = gc_normalintegral(x, N);
  for (int i = 0; i < N; i++)
  {
    /* for "spherical circle segment" sum triangular part and "small moon" and => account for small circle */
    int ii = (i + 1) % N;
    t[1] = x[i];
    t[2] = x[ii];
                double sc=scalarprod(crossprod(t[1] - t[0], t[2] - t[0]), t[0]) ;
    assert(sc >= -1e-10); // Error: tri a l'env (wrong orientation)
    double area_gc = triarea(t[0], t[1], t[2]);
    double area_sc_gc_moon = 0;
    if (d[i]) /* handle small circle case */
    {
      Coord m = midpoint(t[1], t[2]);
      double mext = scalarprod(m, c[i]) - d[i];
      char sgl = (mext > 0) ? -1 : 1;
      area_sc_gc_moon = sgl * alun(arcdist(t[1], t[2]), fabs(scalarprod(t[1], pole)));
      gg_exact = gg_exact + sc_gc_moon_normalintegral(t[1], t[2], pole);
    }
    area += area_gc + area_sc_gc_moon; /* for "spherical circle segment" sum triangular part (at) and "small moon" and => account for small circle */
    g[i] = barycentre(t, 3) * (area_gc + area_sc_gc_moon);
  }
  gg = barycentre(g, N);
  gg_exact = proj(gg_exact);
  delete[] g;
  gg = gg_exact;
  return area;
}

double polygonarea(Coord *vertices, int N)
{
  assert(N >= 3);

  /* compute polygon area as sum of triangles */
  Coord centre = barycentre(vertices, N);
  double area = 0;
  for (int i = 0; i < N; i++)
    area += triarea(centre, vertices[i], vertices[(i+1)%N]);
  return area;
}

int packedPolygonSize(const Elt& e)
{
  return sizeof(e.id) + sizeof(e.src_id) + sizeof(e.x) + sizeof(e.val)  + sizeof(e.given_area)+
         sizeof(e.n) + e.n*(sizeof(double)+sizeof(Coord));
}

void packPolygon(const Elt& e, char *buffer, int& pos) 
{
  *((GloId *) &(buffer[pos])) = e.id;
  pos += sizeof(e.id);
  *((GloId *) &(buffer[pos])) = e.src_id;
  pos += sizeof(e.src_id);

  *((Coord *) &(buffer[pos])) = e.x;
  pos += sizeof(e.x);

  *((double*) &(buffer[pos])) = e.val;
  pos += sizeof(e.val);

  *((double*) &(buffer[pos])) = e.given_area;
  pos += sizeof(e.val);

  *((int *) & (buffer[pos])) = e.n;
  pos += sizeof(e.n);

  for (int i = 0; i < e.n; i++)
  {
    *((double *) & (buffer[pos])) = e.d[i];
    pos += sizeof(e.d[i]);

    *((Coord *) &(buffer[pos])) = e.vertex[i];
    pos += sizeof(e.vertex[i]);
  } 

}

void unpackPolygon(Elt& e, const char *buffer, int& pos) 
{
  e.id = *((GloId *) &(buffer[pos]));
  pos += sizeof(e.id);
  e.src_id = *((GloId *) &(buffer[pos]));
  pos += sizeof(e.src_id);

  e.x = *((Coord *) & (buffer[pos]) );
  pos += sizeof(e.x);

  e.val = *((double *) & (buffer[pos]));
  pos += sizeof(double);

  e.given_area = *((double *) & (buffer[pos]));
  pos += sizeof(double);

  e.n = *((int *) & (buffer[pos]));
  pos += sizeof(int);

  for (int i = 0; i < e.n; i++)
  {
    e.d[i] = *((double *) & (buffer[pos]));
    pos += sizeof(double);

    e.vertex[i] = *((Coord *) & (buffer[pos]));
    pos += sizeof(Coord);
  }
}

int packIntersectionSize(const Elt& elt) 
{
  return elt.is.size() * (2*sizeof(int)+ sizeof(GloId) + 5*sizeof(double));
}

void packIntersection(const Elt& e, char* buffer,int& pos) 
{
  for (list<Polyg *>::const_iterator it = e.is.begin(); it != e.is.end(); ++it)
  {
    *((int *) &(buffer[0])) += 1;

    *((int *) &(buffer[pos])) = e.id.ind;
    pos += sizeof(int);

    *((double *) &(buffer[pos])) = e.area;
    pos += sizeof(double);


    *((GloId *) &(buffer[pos])) = (*it)->id;
    pos += sizeof(GloId);
  
    *((int *) &(buffer[pos])) = (*it)->n;
    pos += sizeof(int);
    *((double *) &(buffer[pos])) = (*it)->area;
    pos += sizeof(double);

    *((Coord *) &(buffer[pos])) = (*it)->x;
    pos += sizeof(Coord);
  }
}

void unpackIntersection(Elt* e, const char* buffer) 
{
  int ind;
  int pos = 0;
  
  int n = *((int *) & (buffer[pos]));
  pos += sizeof(int);
  for (int i = 0; i < n; i++)
  {
    ind = *((int*) &(buffer[pos]));
    pos+=sizeof(int);

    Elt& elt= e[ind];

    elt.area=*((double *) & (buffer[pos]));
    pos += sizeof(double);


    Polyg *polygon = new Polyg;

    polygon->id =  *((GloId *) & (buffer[pos]));
    pos += sizeof(GloId);

    polygon->n =  *((int *) & (buffer[pos]));
    pos += sizeof(int);

    polygon->area =  *((double *) & (buffer[pos]));
    pos += sizeof(double);

    polygon->x = *((Coord *) & (buffer[pos]));
    pos += sizeof(Coord);

    elt.is.push_back(polygon);
  }
}

}
