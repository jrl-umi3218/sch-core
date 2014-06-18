#include "common.h"

using namespace sch;

TestMaterial universe;

void display() {}

/*
* main - this is the main programme.
*/
int main ()
{
  universe.initializeUniverse();
  universe.RandomTestSupportFunction();
  universe.RandomTestSupportFunctionAllObjects();

  return 0;
}


