#pragma once
#ifndef _S_SPHERE_H
#define _S_SPHERE_H

#include "s_object.h"

class S_Sphere :
	public S_Object
{
public:
	S_Sphere(const Scalar&);
	virtual ~S_Sphere();

	virtual Point3  N_Support(const Vector3& v, int& lastFeature)const;

	virtual S_ObjectType S_GetType() const;

	virtual void DrawGL() const;

protected:
	Scalar radius;
	int slices, stacks;



};

#endif
