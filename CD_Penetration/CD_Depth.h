#ifndef _CD_DEPTH
#define _CD_DEPTH

#pragma once
#include "../S_Object/S_Object.h"
#include "../CD/CD_SimplexEnhanced.h"

class CD_Depth
{
private:
	CD_Depth(void);
	virtual ~CD_Depth(void);
public:
	static Scalar getPenetrationDepth(const S_Object* O1, const S_Object* O2,Vector3& v, Point3& p1, Point3& p2, const CD_SimplexEnhanced& s,const CD_Simplex& s1,const CD_Simplex& s2,Scalar Precision,Scalar Epsilon);
};

#endif