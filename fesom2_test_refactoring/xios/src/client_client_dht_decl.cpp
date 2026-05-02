/*!
   \file client_client_dht.cpp
   \author Ha NGUYEN
   \since 05 Oct 2015
   \date 23 Mars 2016

   \brief Distributed hashed table implementation.
 */
#include "client_client_dht_template_impl.hpp"

namespace xios
{

template class CClientClientDHTTemplate<int>;
template class CClientClientDHTTemplate<size_t>;
template class CClientClientDHTTemplate<double>;
template class CClientClientDHTTemplate<PairIntInt>;

}
