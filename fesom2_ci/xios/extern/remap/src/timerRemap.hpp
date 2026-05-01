#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include "mpi.hpp"
#include <string>
#include <map>

namespace sphereRemap {

  using namespace std;


  class CTimer
  {
    public :

    double cumulatedTime;
    double lastTime;
    bool suspended;
    string name;

    CTimer(const string& name);
    void suspend(void);
    void resume(void);
    void reset(void);
    double getCumulatedTime(void);
    void print(void);
    static map<string,CTimer*> allTimer;
    static double getTime(void);
    static CTimer& get(string name);
  };



}
#endif
