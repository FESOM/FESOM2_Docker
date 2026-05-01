#include "elt.hpp"

namespace sphereRemap {

void ptsec(Elt *ea, Elt *eb, Ipt *ipt);
void recense(Elt *ea, Elt *eb, Ipt *ipt, std::list<Sgm> &iscot, int pass);
int assemble(std::list<Sgm> &iscot, Coord *c, double *d, Coord *xc);

}
