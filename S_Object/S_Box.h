
#ifndef S_BOX_H
#define S_BOX_H 

#pragma once



#include "s_object.h"

class S_Box :
	public S_Object
{
public:
	S_Box(Scalar width,Scalar height,Scalar depth);
	
	virtual ~S_Box(void);

	virtual Point3  N_Support(const Vector3& v, int& lastFeature)const;

	virtual S_ObjectType S_GetType() const;

	virtual void DrawGL() const;

protected :
	Scalar a,b,c;

	
};

#endif
