#ifndef  __ERRHANDLE_H__
#define __ERRHANDLE_H__

#include <stdlib.h>
#include <iostream>
#include <string>

namespace sphereRemap {

static inline void error_exit(const std::string& msg)
{
	std::cerr << "Error: " << msg << std::endl;
	exit(0);
}

static inline void exit_on_failure(int status, const std::string& msg)
{
	if (status) error_exit(msg);
}

}
#endif
