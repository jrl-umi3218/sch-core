#pragma once

#ifndef _CLASS_GJK
#define _CLASS_GJK

#include <sch/sch_api.h>
#include <sch/matrix/SCH_Types.h>

class GJK
{
public:
  SCH_API GJK(void);
  SCH_API virtual ~GJK(void);
  SCH_API virtual Point3 Support1(void) = 0;
  SCH_API virtual Point3 Support2(void) = 0;

  SCH_API Scalar Compute(Point3& p1,Point3& p2);
};

#endif
