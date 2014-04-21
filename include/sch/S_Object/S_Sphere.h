#pragma once
#ifndef _S_SPHERE_H
#define _S_SPHERE_H

#include <sch/sch_api.h>
#include <sch/S_Object/S_ObjectNormalized.h>

namespace sch
{

	class S_Sphere :
		public S_ObjectNormalized
	{
	public:
		/*!
		* \brief constructor
		* \param radius, the sphere radius
		*/
		sch_API S_Sphere(const Scalar& radius);
		sch_API virtual ~S_Sphere();

		sch_API virtual Point3 l_Support(const Vector3& v, int& lastFeature)const;

		sch_API virtual S_ObjectType getType() const;

		sch_API virtual Scalar getRadius() const;

	protected:
		Scalar radius_;
	};
}

#endif
