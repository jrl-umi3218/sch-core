#pragma once
#ifndef _S_SPHERE_H
#define _S_SPHERE_H

#include <SCD/scd_api.h>
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
		SCD_API S_Sphere(const Scalar& radius);
		SCD_API virtual ~S_Sphere();

		SCD_API virtual Point3 l_Support(const Vector3& v, int& lastFeature)const;

		SCD_API virtual S_ObjectType getType() const;

    #ifdef WITH_OPENGL
		SCD_API virtual void drawGLInLocalCordinates();
    #endif

	protected:
		Scalar radius_;
		int slices_, stacks_;



	};
}

#endif
