#ifndef  __TRIPLE_H__
#define __TRIPLE_H__

#include <cmath>
#include <iostream>

namespace sphereRemap {

#define EPS 1e-15

/* coordinate on sphere */
class Coord
{
public:
	Coord() : x(0), y(0), z(0) {};
	Coord(double x, double y, double z) : x(x), y(y), z(z) {};

	bool operator==(const Coord& rhs) const
	{
		return x == rhs.x && y == rhs.y && z == rhs.z;
	}

	void rot(const Coord &u, double theta);

	double x, y, z;
};

class Vector
{
public:
	Vector(double u = 0, double v = 0, double w = 0) : u(u), v(v), w(w) {};

	/* vector from origin to point on sphere */
	Vector(const Coord& to) : u(to.x), v(to.y), w(to.z) {};

	Vector& operator+=(const Vector& rhs)
	{
           u += rhs.u;
           v += rhs.v;
           w += rhs.w;
           return *this ;
	}

	double u, v, w;
};

extern const Coord ORIGIN;

std::ostream& operator<<(std::ostream& os, const Coord& c);
std::ostream& operator<<(std::ostream& os, const Vector& c);

inline double lengthSquared(Vector& vec)
{
	return vec.u*vec.u + vec.v*vec.v + vec.w*vec.w;
}
	
inline Coord operator+(const Coord &lhs, const Coord &rhs)
{
	return Coord(lhs.x + rhs.x, 
	             lhs.y + rhs.y, 
	             lhs.z + rhs.z);
}

inline Coord operator-(const Coord &lhs, const Coord &rhs)
{
	return Coord(lhs.x - rhs.x, 
	             lhs.y - rhs.y, 
	             lhs.z - rhs.z);
}

/** vector scalar multiplication */
inline Coord operator*(const Coord &lhs, double rhs)
{
	return Coord(lhs.x * rhs, 
	             lhs.y * rhs, 
	             lhs.z * rhs);
}

inline double squaredist(const Coord &x, const Coord &y)
{
	return (y.x-x.x)*(y.x-x.x)
	     + (y.y-x.y)*(y.y-x.y) 
	     + (y.z-x.z)*(y.z-x.z);
}

inline double eucldist(const Coord &x, const Coord &y)
{
	return sqrt(squaredist(x, y));
}


double norm(const Coord &x);

Coord proj(const Coord &x);

double scalarprod(const Coord &a, const Coord &b);

Coord crossprod(const Coord &a, const Coord &b);

double arcdist(const Coord &x, const Coord &y);

double ds(const Coord &x, const Coord &y);

double dp(const Coord &x, const Coord &y, const Coord &pole);

//double angle(const Vector&, const Vector&)

void lonlat(const Coord &a, double &lon, double &lat);

Coord xyz(double lon, double lat);

/** Computes the midpoint on spherical arc between two points on the sphere */
Coord midpoint(const Coord &a, const Coord &b);

/** Computes the midpoint on *small circle* between two points on the sphere */
Coord midpointSC(const Coord &a, const Coord &b);

void rot(const Coord &u, const double th, Coord &x);

void rotsg(const Coord &a, Coord &b, const Coord &c,
           const Coord &d, Coord &x);

double angle(const Coord &a, const Coord &b, const Coord &pole);

// return oriented vector angle in range [-pi..pi], pole must be orthogonal to a and b
double vectAngle(const Coord &a, const Coord &b, const Coord &pole) ;

void print_Coord(Coord &p);

}

#endif
