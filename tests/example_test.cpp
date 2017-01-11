#include "shared-tests/examples/example_common.h"

#ifdef ENABLE_SIGFPE
# include <fenv.h>
#endif

void display() {}

int main()
{
  #ifdef ENABLE_SIGFPE
  feenableexcept(FE_ALL_EXCEPT & ~FE_INEXACT);
  #endif
  Example universe;
  universe.initializeUniverse();
  bool success = universe.unittest();
  return (success? 0:1);
}

