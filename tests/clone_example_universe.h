#pragma once

#include "shared-tests/examples/example_common.h"

inline Example CloneUniverse(Example & in)
{
  Example out;
  // Initialize the universe to have the correct names
  out.initializeUniverse();
  // Clear the scene
  out.sObj = sch::CD_Scene();
  for(size_t i = 0; i < in.sObj.size(); ++i)
  {
    out.sObj.addObject(in.sObj[i]->clone());
  }
  return out;
}
