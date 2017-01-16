#include "shared-tests/tests/common.h"

#ifdef ENABLE_SIGFPE
# include <fenv.h>
#endif

using namespace sch;

void display() {}

/*
* main - this is the main programme.
*/
int main ()
{
  #ifdef ENABLE_SIGFPE
  feenableexcept(FE_ALL_EXCEPT & ~FE_INEXACT);
  #endif
  TestMaterial universe = TestMaterial(); //No other objects than STP-BVs
  universe.initializeUniverse();
  universe.TestAnimation();
  return 0;
}


