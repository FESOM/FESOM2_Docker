#include "xios.hpp"

#include "icutil.hpp"
#include "icdate.hpp"
#include "calendar_util.hpp"

extern "C"
{
  void cxios_duration_convert_to_string(cxios_duration dur_c, char* str, int str_size)
  TRY
  {
    xios::CDuration dur( dur_c.year, dur_c.month, dur_c.day, dur_c.hour, dur_c.minute, dur_c.second, dur_c.timestep );

    if (!string_copy(dur.toString(), str, str_size))
      ERROR("void cxios_duration_convert_to_string(cxios_duration dur_c, char* str, int str_size)", << "Input string is too short");
  }
  CATCH_DUMP_STACK

  cxios_duration cxios_duration_convert_from_string(const char* str, int str_size)
  TRY
  {
    std::string dur_str;
    xios::CDuration dur;

    if (cstr2string(str, str_size, dur_str))
      dur = xios::CDuration::FromString(dur_str);

    return { dur.year, dur.month, dur.day, dur.hour, dur.minute, dur.second, dur.timestep };
  }
  CATCH_DUMP_STACK

  cxios_duration cxios_duration_add(cxios_duration dur1_c, cxios_duration dur2_c)
  TRY
  {
    xios::CDuration dur1( dur1_c.year, dur1_c.month, dur1_c.day, dur1_c.hour, dur1_c.minute, dur1_c.second, dur1_c.timestep );
    xios::CDuration dur2( dur2_c.year, dur2_c.month, dur2_c.day, dur2_c.hour, dur2_c.minute, dur2_c.second, dur2_c.timestep );

    xios::CDuration res = dur1 + dur2;
    return { res.year, res.month, res.day, res.hour, res.minute, res.second, res.timestep };
  }
  CATCH_DUMP_STACK

  cxios_duration cxios_duration_sub(cxios_duration dur1_c, cxios_duration dur2_c)
  TRY
  {
    xios::CDuration dur1( dur1_c.year, dur1_c.month, dur1_c.day, dur1_c.hour, dur1_c.minute, dur1_c.second, dur1_c.timestep );
    xios::CDuration dur2( dur2_c.year, dur2_c.month, dur2_c.day, dur2_c.hour, dur2_c.minute, dur2_c.second, dur2_c.timestep );

    xios::CDuration res = dur1 - dur2;
    return { res.year, res.month, res.day, res.hour, res.minute, res.second, res.timestep };
  }
  CATCH_DUMP_STACK

  cxios_duration cxios_duration_mult(double val, cxios_duration dur_c)
  TRY
  {
    xios::CDuration dur( dur_c.year, dur_c.month, dur_c.day, dur_c.hour, dur_c.minute, dur_c.second, dur_c.timestep );
    xios::CDuration res = val * dur;
    return { res.year, res.month, res.day, res.hour, res.minute, res.second, res.timestep };
  }
  CATCH_DUMP_STACK

  cxios_duration cxios_duration_neg(cxios_duration dur_c)
  TRY
  {
    xios::CDuration dur( dur_c.year, dur_c.month, dur_c.day, dur_c.hour, dur_c.minute, dur_c.second, dur_c.timestep );
    xios::CDuration res = -dur;
    return { res.year, res.month, res.day, res.hour, res.minute, res.second, res.timestep };
  }
  CATCH_DUMP_STACK

  bool cxios_duration_eq(cxios_duration dur1_c, cxios_duration dur2_c)
  TRY
  {
    xios::CDuration dur1( dur1_c.year, dur1_c.month, dur1_c.day, dur1_c.hour, dur1_c.minute, dur1_c.second, dur1_c.timestep );
    xios::CDuration dur2( dur2_c.year, dur2_c.month, dur2_c.day, dur2_c.hour, dur2_c.minute, dur2_c.second, dur2_c.timestep );
    return (dur1 == dur2);
  }
  CATCH_DUMP_STACK

  bool cxios_duration_neq(cxios_duration dur1_c, cxios_duration dur2_c)
  TRY
  {
    xios::CDuration dur1( dur1_c.year, dur1_c.month, dur1_c.day, dur1_c.hour, dur1_c.minute, dur1_c.second, dur1_c.timestep );
    xios::CDuration dur2( dur2_c.year, dur2_c.month, dur2_c.day, dur2_c.hour, dur2_c.minute, dur2_c.second, dur2_c.timestep );
    return (dur1 != dur2);
  }
  CATCH_DUMP_STACK
}
