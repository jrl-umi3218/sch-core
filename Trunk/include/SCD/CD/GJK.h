#pragma once

#ifndef _CLASS_GJK
#define _CLASS_GJK

#include <SCD/matrix/SCD_Types.h>
class GJK
{
public:
	GJK(void);
	virtual ~GJK(void);
	virtual Point3 Support1(void) = 0;
	virtual Point3 Support2(void) = 0;
	
	Scalar Compute(Point3& p1,Point3& p2);

private :

	

};

#endif
