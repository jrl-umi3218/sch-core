#include "shared-tests/tests/common.h"

using namespace sch;

void display() {}

/*
* main - this is the main programme.
*/
int main ()
{
  TestMaterial universe;
  universe.initializeUniverse();
  universe.TestPrecision();
  return 0;
}


