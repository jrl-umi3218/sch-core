#include "clone_example_universe.h"

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
  {
    Example clone_universe = CloneUniverse(universe);
    success = clone_universe.unittest() && success;
  }
  return (success? 0:1);
}

