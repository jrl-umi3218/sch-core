#include "shared-tests/examples/example_common.h"

#ifdef __linux__
  #include <fenv.h>
#endif

void display() {}

int main()
{
  #ifdef __linux__
  feenableexcept(FE_ALL_EXCEPT & ~FE_INEXACT);
  #endif
  Example universe;
  universe.initializeUniverse();
  bool success = universe.unittest();
  return (success? 0:1);
}

