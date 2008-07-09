#pragma once
#ifndef _S_SPHERE_H
#define _S_SPHERE_H

#include "s_object.h"

class S_Sphere :
	public S_Object
{
public:
	/*!
	 * \brief constructor
	 * \param radius, the shpere radius
 	 */
	S_Sphere(const Scalar& radius);
	virtual ~S_Sphere();

	virtual Point3 n_Support(const Vector3& v, int& lastFeature)const;

	virtual S_ObjectType getType() const;

	virtual void drawGL() const;

protected:
	Scalar radius_;
	int slices_, stacks_;



};

#endif
