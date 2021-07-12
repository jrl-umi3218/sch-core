#define NON_STP_BV_OBJECTS true

#include "clone_test_universe.h"

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
  TestMaterial universe = TestMaterial(NON_STP_BV_OBJECTS);
  universe.initializeUniverse();
  universe.RandomTestSupportFunction();
  universe.RandomTestSupportFunctionAllObjects();
  {
    TestMaterial clone_universe(NON_STP_BV_OBJECTS);
    CloneUniverse(universe, clone_universe);
    clone_universe.RandomTestSupportFunction();
    clone_universe.RandomTestSupportFunctionAllObjects();
  }

  return 0;
}


