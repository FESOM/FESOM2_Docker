#define __XIOS_Configure__ // < Ne pas supprimer

/// XIOS headers ///
#include "xios_spl.hpp"

/// /////////// Macros /////////// ///
#undef  DECLARE_PROPERTY
#define DECLARE_PROPERTY(type, name, value) \
   type name = value;

namespace xios
{
#include "properties.conf"
} // namespace xios
