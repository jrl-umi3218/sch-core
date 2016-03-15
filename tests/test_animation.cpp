#include "shared-tests/tests/common.h"

#ifdef __linux__
  #include <fenv.h>
#endif

using namespace sch;

void display() {}

/*
* main - this is the main programme.
*/
int main ()
{
  #ifdef __linux__
  feenableexcept(FE_ALL_EXCEPT & ~FE_INEXACT);
  #endif
  TestMaterial universe;
  universe.initializeUniverse();
  universe.TestAnimation();
  return 0;
}


