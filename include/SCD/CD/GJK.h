#pragma once

#ifndef _CLASS_GJK
#define _CLASS_GJK

#include <SCD/scd_api.h>
#include <SCD/matrix/SCD_Types.h>
class GJK
{
public:
	SCD_API GJK(void);
	SCD_API virtual ~GJK(void);
	SCD_API virtual Point3 Support1(void) = 0;
	SCD_API virtual Point3 Support2(void) = 0;
	
	SCD_API Scalar Compute(Point3& p1,Point3& p2);

private :

	

};

#endif
