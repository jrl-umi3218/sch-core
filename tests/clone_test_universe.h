#pragma once

#include "shared-tests/tests/common.h"

inline TestMaterial CloneUniverse(TestMaterial & in, bool nonSTPBV)
{
  TestMaterial out(nonSTPBV);
  for(size_t i = 0; i < in.sObj.size(); ++i)
  {
    out.sObj.addObject(in.sObj[i]->clone());
  }
  return out;
}
