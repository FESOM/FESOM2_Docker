#include <cstdlib>
#include <cmath>
#include <cassert>
#include <iostream>
#include "elt.hpp"
#include "polyg.hpp"

#include "inside.hpp"

namespace sphereRemap {

static const double SNAP = 1e-11;

using namespace std;

/* returns the index of the element in `v` with the maximum absolute value*/
int argmaxAbs3(double *v)
{
	/* ip
	    0  F F   |v0| >= |v1| && |v0| >= |v2|  max: v0 
	    1  T F   |v0|  < |v1| && |v1| >= |v2|       v1
	    2  ? T   |v0|  < |v2| && |v1| <  |v2|       v2
	*/
	int amax = 0;
	double maxv = fabs(v[0]);
	if (fabs(v[1]) > maxv)
	{
		amax = 1;
		maxv = fabs(v[1]);
	}
	if (fabs(v[2]) > maxv)
	{
		amax = 2;
		maxv = fabs(v[2]);
	}
	return amax;
}

/**
   Find all intersections of edges of ea with edges of eb, and store all intersection points in ipt.
   `ipt` is flattened matix of `Ipt` with inner dimension the number of edges of `ea` and outer dimension the one of `eb`.
   `Ipt` contains two coordinates for two possible intersections between two edges.
*/
void ptsec(Elt *ea, Elt *eb, Ipt *ipt)
{
	int na = ea->n;
	int nb = eb->n;

	for (int i = 0; i < ea->n; i++)
	{
		for (int j = 0; j < eb->n; j++)
		{
			int ij = i*eb->n + j;
			if (norm(crossprod(ea->edge[i], eb->edge[j])) < 1e-15)
			{
				ipt[ij].nb = 0;
				continue;
			}

			double A, B, C, D, Ap, Bp, Cp, Dp;
			double d3, d4, aa, bb, cc, dd; // if polygon then d3 = d4 = 0
			double d[3];

			A =ea->edge[i].x; B =ea->edge[i].y; C =ea->edge[i].z; D =-ea->d[i];
			Ap=eb->edge[j].x; Bp=eb->edge[j].y; Cp=eb->edge[j].z; Dp=-eb->d[j];

			d[0] = B * Cp - C * Bp;
			d[1] = C * Ap - A * Cp;
			d[2] = A * Bp - B * Ap;

			int ip = argmaxAbs3(d);
			if (ip == 0) {
				d3 = -ea->edge[i].z*eb->d[j]        + ea->d[i]      *eb->edge[j].z;
				d4 = -ea->d[i]      *eb->edge[j].y  + ea->edge[i].y*eb->d[j];      
			}
			if (ip == 1) {
				d[0] = C*Ap-A*Cp;
				d[1] = A*Bp-B*Ap;
				d[2] = B*Cp-C*Bp;
				d3 = A*Dp-D*Ap;
				d4 = D*Cp-C*Dp;
			}
			if (ip == 2) {
				d[0] = A*Bp-B*Ap; d[1] = B*Cp-C*Bp; d[2] = C*Ap-A*Cp;
				d3 = B*Dp-D*Bp; d4 = D*Ap-A*Dp;
			}
			aa = d[0]*d[0] + d[1]*d[1] + d[2]*d[2];
			bb = d[1]*d3 + d[2]*d4;
			cc = d3*d3 + d4*d4 - d[0]*d[0];
			dd = bb*bb - aa*cc; // if polygon dd = 0*0 - ||d||**2 * d0**2

			if (dd < EPS*EPS)
			{
				ipt[ij].nb = 0;
				continue;
			}
			ipt[ij].nb = 2;

			double v_[3];
			v_[ip]       = (-bb + sqrt(dd))/aa;
			v_[(ip+1)%3] = (d[1]*v_[ip] + d3)/d[0];
			v_[(ip+2)%3] = (d[2]*v_[ip] + d4)/d[0];
			double w_[3];
			w_[ip]       = (-bb - sqrt(dd))/aa;
			w_[(ip+1)%3] = (d[1]*w_[ip] + d3)/d[0];
			w_[(ip+2)%3] = (d[2]*w_[ip] + d4)/d[0];

			Coord v(v_[0], v_[1], v_[2]);
			Coord w(w_[0], w_[1], w_[2]);

			int ii = (i + 1) % na;
			int jj = (j + 1) % nb;

			/* if v and/or w is close to a vertex make exact (align) */
			if (squaredist(v, ea->vertex[i] ) < SNAP*SNAP)  v = ea->vertex[i];
			if (squaredist(v, ea->vertex[ii]) < SNAP*SNAP)  v = ea->vertex[ii];
			if (squaredist(v, eb->vertex[j] ) < SNAP*SNAP)  v = eb->vertex[j];
			if (squaredist(v, eb->vertex[jj]) < SNAP*SNAP)  v = eb->vertex[jj];
			if (squaredist(w, ea->vertex[i] ) < SNAP*SNAP)  w = ea->vertex[i];
			if (squaredist(w, ea->vertex[ii]) < SNAP*SNAP)  w = ea->vertex[ii];
			if (squaredist(w, eb->vertex[j] ) < SNAP*SNAP)  w = eb->vertex[j];
			if (squaredist(w, eb->vertex[jj]) < SNAP*SNAP)  w = eb->vertex[jj];

			assert(squaredist(v,w) > EPS*EPS); // inconsistency in line intersection

			/* in 99% os cases we will later discart one of the two points for lying on the the other side of the globe */
			ipt[ij].pt[0] = v;
			ipt[ij].pt[1] = w;
		}
	}
}

void recense(Elt *ea, Elt *eb, Ipt *ipt, list<Sgm> &isedge, int pass)
{
	list<Sgm> plan;
	list<Sgm>::iterator bit;
	Sgm sgm;
	int na = ea->n;
	int nb = eb->n;

	for (int i = 0; i<na; i++)
	{
sega:
		int ii = (i+1)%na;
		sgm.n = ea->edge[i];
		sgm.d = ea->d[i];
		sgm.xt[0] = ea->vertex[i];
		sgm.xt[1] = ea->vertex[ii];
		plan.push_back(sgm);
		for (int j = 0; j<nb; j++)
		{
			int ij = i*nb+j;
			const double OUT = 1e-11;

			if (ipt[ij].nb < 2)
			{
				bit = plan.begin();
				double side = scalarprod(bit->xt[0], eb->edge[j]) - eb->d[j];
				double side1= scalarprod(bit->xt[1], eb->edge[j]) - eb->d[j];
				if (side < -OUT || side1 < -OUT ||
						(side < OUT && side1 < OUT && pass)) //dedans
					continue;  // all bits unscathed, j++
				plan.clear(); i++;
				if (i<na) goto sega; // all bits destroyed, i++
				else return;
			}

			Coord& x = ipt[ij].pt[0];
			Coord& y = ipt[ij].pt[1];
			bit = plan.begin();
			double r2 = 1 - bit->d*bit->d;
			while (bit!=plan.end()) {  // bit++ !!
				double lg = squaredist(bit->xt[0], bit->xt[1]);
				double side = scalarprod(bit->xt[0], eb->edge[j]) - eb->d[j];
				double ag = angle(bit->xt[0], bit->xt[1], bit->n) /r2;
				double agx = angle(bit->xt[0], x, bit->n) /r2;
				double agy = angle(bit->xt[0], y, bit->n) /r2;
				double r = 1;//sqrt(r2);
				int isd = 0;  // is dans le seg

				if (ag > 0)
				{
					if (r*agx > OUT && r*agx < ag-OUT && squaredist(bit->xt[0], x) < lg) { isd += 1; }
					if (r*agy > OUT && r*agy < ag-OUT && squaredist(bit->xt[0], y) < lg) { isd += 2; }
				} else {
					if (r*agx< -OUT && r*agx > ag+OUT && squaredist(bit->xt[0], x) < lg) { isd += 1; }
					if (r*agy< -OUT && r*agy > ag+OUT && squaredist(bit->xt[0], y) < lg) { isd += 2; }
				}

				Coord m, ptout;
				double side_m, side_pt;
				int A=0;
				double agrot = M_PI_2;
				if (ag > 0) agrot *= -1;
				switch (isd) {
					case 0:
						if (bit->d)
							m = midpointSC(bit->xt[0], bit->xt[1]);
						else
							m = barycentre(bit->xt, 2);
						side = scalarprod(m, eb->edge[j]) - eb->d[j];
						if (side < 0)
							++bit;  // unscathed
						else
							bit = plan.erase(bit);
						continue;
					case 1:
						if (squaredist(x, bit->xt[1]) > squaredist(x, bit->xt[0])) A = 1;
						m = (bit->d) ? midpointSC(x, bit->xt[A]) : midpoint(x, bit->xt[A]);
						side_m = scalarprod(m, eb->edge[j]) - eb->d[j];
						if (side_m < 0) bit->xt[1-A] = x;
						else bit->xt[A] = x;
						++bit;
						continue;
					case 2:
						if (squaredist(y, bit->xt[0]) > squaredist(y, bit->xt[1])) A = 1;
						m = (bit->d) ? midpointSC(y, bit->xt[A]) : midpoint(y, bit->xt[A]);
						side_m = scalarprod(m, eb->edge[j]) - eb->d[j];
						if (side_m < 0) bit->xt[1-A] = y;
						else bit->xt[A] = y;
						++bit; continue;
					case 3:
						ptout = bit->xt[0];
						ptout.rot(bit->n, -ag);
						side_pt = scalarprod(ptout, eb->edge[j]) - eb->d[j];
						if (side_pt < 0.) {  // or side
							Sgm sgm2;
							sgm2.n = ea->edge[i];
							sgm2.d = ea->d[i];
							int A=0, B=1;
							if (squaredist(bit->xt[0], y) < squaredist(bit->xt[0], x))
							{
								++A;
								--B;
							}
							sgm2.xt[0] = ipt[ij].pt[B];
							sgm2.xt[1] = bit->xt[1];
							bit->xt[1] = ipt[ij].pt[A];
							++bit;
							plan.insert(bit,sgm2);
						} else {
							bit->xt[0] = ipt[ij].pt[0];
							bit->xt[1] = ipt[ij].pt[1];
							++bit;
						}
						continue;
				}
			}
		}
		for (bit=plan.begin(); bit!=plan.end(); ++bit) {
			isedge.push_back(*bit);
		}
		plan.clear();
	}

}

/* output: c, d, xc
   in/out: isedge get elements removed */
int assemble(list<Sgm>& isedge, Coord *c, double *d, Coord *xc)
{
	double lgmax = 0.;
	int idmax = 0, id = 0;
	for (list<Sgm>::iterator it = isedge.begin(); it != isedge.end(); ++it, ++id)
	{
		double lg = squaredist(it->xt[0], it->xt[1]);
		if (lg > lgmax)
		{
			idmax = id;
			lgmax = lg;
		}
	}

	list<Sgm>::iterator it = isedge.begin();
	advance(it, idmax);
	c[0] = it->n;
	d[0] = it->d;
	xc[0] = it->xt[0];
	Coord t = it->xt[1];
	int nc = 1;
	isedge.erase(it); //isedge.pop_front();

	while (isedge.size())
	{
		/* all distances as squares to omit sqrt */
		double d0, d1;
		double dmin = pow(17.,2);
		int idmin = 0, id = 0, s = 0;
		list< pair <int, double> > way;
		list< pair <int, double> >::iterator wi;
		int ps1way = 0;
		for (it = isedge.begin(); it != isedge.end(); ++it, ++id)
		{
			d0 = squaredist(t, it->xt[0]);
			d1 = squaredist(t, it->xt[1]);
			if (d0 < SNAP*SNAP || d1 < SNAP*SNAP)
			{
				double lg  = squaredist(it->xt[0], it->xt[1]);
				pair <int, double> p = make_pair(id, lg);
				if (d0 < 0.01*dmin || d1 < 0.01*dmin)
				{
					ps1way = 1;
					way.push_front(p);
				}
				else
				{
					ps1way = 0;
					way.push_back(p);
				}
			}
			if (d0 < dmin)
			{
				idmin = id;
				s = 0;
				dmin = d0;
			}
			if (d1 < dmin)
			{
				idmin = id;
				s = 1;
				dmin = d1;
			}
		}
		int ways = way.size();
		double lgmaxx = 0.;
		int A = 0, B = 1;
		assert(ways < 3);
		switch (ways)
		{
		case 0:
			return nc;
			break;
		case 2:
			if (ps1way == 1)
				idmin = way.front().first;
			else
			{
				for (wi = way.begin(); wi != way.end(); ++wi)
				{
					if (wi->second > lgmaxx)
					{
						idmin = wi->first;
						lgmaxx = wi->second;
					}
				}
			}
		case 1:
			if (ways == 1)
				idmin = way.front().first;
			it = isedge.begin();
			advance(it, idmin);
			c[nc] = it->n;
			d[nc] = it->d;
			if (s)
			{
				++A;
				--B;
			}
			xc[nc] = it->xt[A];
			t = it->xt[B];
			nc++;
			isedge.erase(it);
			break;
		default:
			; // assert(ways < 3) above -> cannot be reached
		}
	}

	return nc;
}

}
