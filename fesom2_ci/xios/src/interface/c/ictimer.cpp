#include "timer.hpp"
#include <string>


using namespace xios;

extern "C"
{
  void cxios_timer_resume(const char* timer_id, int len_timer_id, bool trace)
  {
    std::string str(timer_id,len_timer_id);
    CTimer::get(str).resume();
  }

  void cxios_timer_suspend(const char* timer_id, int len_timer_id, bool trace)
  {
    std::string str(timer_id,len_timer_id);
    CTimer::get(str).suspend();
  }

  void cxios_timer_reset(const char* timer_id, int len_timer_id)
  {
    std::string str(timer_id,len_timer_id);
    CTimer::get(str).reset();
  }

  void cxios_timer_get_time(double* time)
  {
    *time=CTimer::getTime();
  }

  void cxios_timer_get_cumulated_time(const char* timer_id, int len_timer_id, double* time)
  {
    std::string str(timer_id,len_timer_id);
    *time=CTimer::get(str).getCumulatedTime();
  }
}


