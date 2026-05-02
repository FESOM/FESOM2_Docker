/*!
   \file dht_data_types.hpp
   \author Ha NGUYEN
   \since 17 Mars 2016
   \date 17 Mars 2016

   \brief Customized data type for dht
 */

#ifndef __XIOS_DHT_DATATYPES_HPP__
#define __XIOS_DHT_DATATYPES_HPP__

#include "utils.hpp"

namespace xios
{
typedef std::pair<int,int> PairIntInt;

template<typename T>
struct ProcessDHTElement
{
  typedef T Type;
  static int typeSize()
  {
    return sizeof(Type);
  }

  static void packElement(const T& inputElement, unsigned char* packedElement, int& index)
  {
    if (NULL == packedElement) index += sizeof(Type);
    else
    {
      *(T *)(&packedElement[index]) = inputElement;
      index+=sizeof(Type);
    }
  }

  static void unpackElement(T& outputElement, unsigned char* unpackedElement, int& index)
  {
    outputElement = *(Type*)(&unpackedElement[index]);
    index+=sizeof(Type);
  }
};

template<>
struct ProcessDHTElement<PairIntInt>
{
  typedef PairIntInt Type;
  static int typeSize()
  {
    return (2*sizeof(int));
  }

  static void packElement(const PairIntInt& inputElement, unsigned char* packedElement, int& index)
  {
    if (NULL == packedElement) index +=(2*sizeof(int));
    else
    {
      *(int *)(&packedElement[index]) = inputElement.first;
      index+=sizeof(int);
      *(int *)(&packedElement[index]) = inputElement.second;
      index+=sizeof(int);
    }
  }

  static void unpackElement(PairIntInt& outputElement, unsigned char* unpackedElement, int& index)
  {
    outputElement.first=*(int *)(&unpackedElement[index]);
    index+=sizeof(int);
    outputElement.second=*(int *)(&unpackedElement[index]);
    index+=sizeof(int);
  }
};

}

#endif // __XIOS_DHT_DATATYPES_HPP__
