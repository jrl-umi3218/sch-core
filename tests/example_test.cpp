#include "shared-tests/examples/example_common.h"

void display() {}

int main()
{
  Example universe;
  universe.initializeUniverse();
  bool success = universe.unittest();
  return (success? 0:1);
}

