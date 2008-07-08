#ifndef _S_SUPERELLIPSOID
#define _S_SUPERELLIPSOID

#pragma once


#include "s_object.h"

class S_Superellipsoid :
	public S_Object
{
public:
	S_Superellipsoid(Scalar a,Scalar b,Scalar c,Scalar epsilon1,Scalar epsilon2);
	virtual ~S_Superellipsoid(void);

	virtual Point3  N_Support(const Vector3& v, int& lastFeature)const;

	virtual S_ObjectType S_GetType() const;

	virtual void DrawGL() const;

protected:
	Scalar a,b,c,epsilon1,epsilon2;
	int displist;
	int slices, stacks;


};

#endif