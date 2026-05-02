#include "triple.hpp"

namespace sphereRemap {

extern const Coord ORIGIN(0.0, 0.0, 0.0);

std::ostream& operator<<(std::ostream& os, const Coord& c) {
    return os << "(" << c.x << ", " << c.y << ", " << c.z << ")";
}

std::ostream& operator<<(std::ostream& os, const Vector& vec)
{
    return os << "(" << vec.u << ", " << vec.v << ", " << vec.w << ")";
}

double norm(const Coord &x)
{
	return sqrt(x.x*x.x + x.y*x.y + x.z*x.z);
}

Coord proj(const Coord &x)
{
	double n=norm(x);
	return Coord(x.x/n, x.y/n, x.z/n);
}

double scalarprod(const Coord &a, const Coord &b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

Coord crossprod(const Coord &a, const Coord &b)
{
	return Coord(a.y*b.z - a.z*b.y,
	             a.z*b.x - a.x*b.z,
	             a.x*b.y - a.y*b.x);
}

/* arc distance (along great circle) */
double arcdist(const Coord &x, const Coord &y)
{ // et angles aigus non orientes
	double n = norm(crossprod(x, y));
  if (n>1.) n=1. ;
	double a = asin(n);
	if (squaredist(x,y) > 2.0) a = M_PI - a;
	return a;
}

/* alternate way to compute distance along great circle */
double ds(const Coord &x, const Coord &y)
{
	return 2*asin(0.5*eucldist(x,y));
}

/* dp is both small circle distances */
double dp(const Coord &x, const Coord &y, const Coord &pole)
{
	return 2*asin(0.5 * eucldist(x,y) / sin(ds(pole,x)));
}

//* angle between `p` and `q` */ 
/*double angle(const Vector &p, const Vector &q)
{
	return acos(scalarprod(p, q));
}*/

void lonlat(const Coord &a, double &lon, double &lat)
{
	lon = atan2(a.y, a.x) * 180.0/M_PI;
	lat = (M_PI_2 - acos(a.z)) * 180.0/M_PI;
}

Coord xyz(double lon, double lat)
{
	double phi   = M_PI/180.0*lon;
	double theta = M_PI_2 - M_PI/180.0*lat;
	return Coord(sin(theta)*cos(phi),
	             sin(theta)*sin(phi),
	             cos(theta));
}

/** computes the midpoint on spherical arc between a and b */
Coord midpoint(const Coord &a, const Coord &b)
{
	return proj(a + b);
}

/** computes the midpoint on *small circle* between a and b */
Coord midpointSC(const Coord& p, const Coord& q)
{
	double phi1 = atan2(p.y, p.x);
	double phi2 = atan2(q.y, q.x);
	if (phi1*phi2 < 0)
		phi1 += (phi1 < phi2) ? 2*M_PI : -2*M_PI;
	double theta = acos(p.z);
	double phi   = 0.5*(phi1 + phi2);
	return Coord(sin(theta)*cos(phi),
	             sin(theta)*sin(phi),
	             cos(theta));
}

/* rotates us by angle theta around u (r is rotatiion matrix) */
void Coord::rot(const Coord &u, double theta)
{
	double x = this->x;
	double y = this->y;
	double z = this->z;

	double ux2 = u.x*u.x, uy2 = u.y*u.y, uz2 = u.z*u.z;
	double k = 1 - cos(theta);

	double r00 = ux2      + (1-ux2)*cos(theta),  r01 = u.x*u.y*k - u.z*sin(theta),  r02 = u.x*u.z*k + u.y*sin(theta);
	double r10 = u.x*u.y*k + u.z*sin(theta),  r11 = uy2      + (1-uy2)*cos(theta),  r12 = u.y*u.z*k - u.x*sin(theta);
	double r20 = u.x*u.z*k - u.y*sin(theta),  r21 = u.y*u.z*k + u.x*sin(theta),  r22 = uz2 + (1-uz2)*cos(theta);

	this->x = r00*x + r01*y + r02*z;
	this->y = r10*x + r11*y + r12*z;
	this->z = r20*x + r21*y + r22*z;
}

double angle(const Coord &a, const Coord &b, const Coord &pole)
{ 
	return scalarprod(crossprod(a, b), pole);
}

// return oriented vector angle in range [-pi..pi], pole must be orthogonal to a and b
double vectAngle(const Coord &a, const Coord &b, const Coord &pole)
{ 
  double nab = 1./(norm(a)*norm(b)) ;
  
  Coord a_cross_b=crossprod(a, b)*nab ;
  double sinVect ;
  if (scalarprod(a_cross_b, pole) >= 0) sinVect=norm(a_cross_b) ;
  else sinVect=-norm(a_cross_b) ;
  double cosVect=scalarprod(a,b)*nab ;

  return atan2(sinVect,cosVect) ;
}

}
