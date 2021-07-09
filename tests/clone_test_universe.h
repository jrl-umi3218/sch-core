#pragma once

#include "shared-tests/tests/common.h"

inline void CloneUniverse(TestMaterial & in, TestMaterial & out)
{
  for(size_t i = 0; i < in.sObj.size(); ++i)
  {
    out.sObj.addObject(in.sObj[i]->clone());
  }
}
