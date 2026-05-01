#include "field_impl.hpp"

namespace xios
{
  template void CField::setData<1>(const CArray<double, 1>& _data, int ntile);
  template void CField::setData<2>(const CArray<double, 2>& _data, int ntile);
  template void CField::setData<3>(const CArray<double, 3>& _data, int ntile);
  template void CField::setData<4>(const CArray<double, 4>& _data, int ntile);
  template void CField::setData<5>(const CArray<double, 5>& _data, int ntile);
  template void CField::setData<6>(const CArray<double, 6>& _data, int ntile);
  template void CField::setData<7>(const CArray<double, 7>& _data, int ntile);

  template void CField::getData<1>(CArray<double, 1>& _data) const;
  template void CField::getData<2>(CArray<double, 2>& _data) const;
  template void CField::getData<3>(CArray<double, 3>& _data) const;
  template void CField::getData<4>(CArray<double, 4>& _data) const;
  template void CField::getData<5>(CArray<double, 5>& _data) const;
  template void CField::getData<6>(CArray<double, 6>& _data) const;
  template void CField::getData<7>(CArray<double, 7>& _data) const;
}
