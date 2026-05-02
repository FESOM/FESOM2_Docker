#ifndef __XIOS_Configure__
#define __XIOS_Configure__


/// /////////// Macros /////////// ///
#define DECLARE_PROPERTY(type, name, value) \
   extern type name; // = value

namespace xios
{
#include "properties.conf"
} // namespace xios

#endif // __XIOS_Configure__
