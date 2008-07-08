#ifndef __S_OBJECTNONNORMALIZED
#define __S_OBJECTNONNORMALIZED

#pragma once
#include "s_object.h"

class S_ObjectNonNormalized :
	public S_Object
{
public:
	S_ObjectNonNormalized(void);
	~S_ObjectNonNormalized(void);
	
	virtual Point3 Support(const Vector3& v) const;
	virtual Point3 Support(const Vector3& v, int & LastFeature) const;
};

#include "S_ObjectNonNormalized.hxx"

#endif