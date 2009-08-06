#pragma once
#ifndef _S_SPHERE_H
#define _S_SPHERE_H

#include <SCD/S_Object/S_ObjectNormalized.h>

namespace SCD
{

	class S_Sphere :
		public S_ObjectNormalized
	{
	public:
		/*!
		* \brief constructor
		* \param radius, the shpere radius
		*/
		S_Sphere(const Scalar& radius);
		virtual ~S_Sphere();

		virtual Point3 l_Support(const Vector3& v, int& lastFeature)const;

		virtual S_ObjectType getType() const;

		virtual void drawGLInLocalCordinates();

	protected:
		Scalar radius_;
		int slices_, stacks_;



	};
}

#endif
