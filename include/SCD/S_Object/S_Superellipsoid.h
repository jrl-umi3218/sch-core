#ifndef _S_SUPERELLIPSOID
#define _S_SUPERELLIPSOID

#pragma once


#include <SCD/scd_api.h>
#include <SCD/S_Object/S_ObjectNonNormalized.h>

namespace SCD
{

	class S_Superellipsoid :
		public S_ObjectNonNormalized
	{
	public:
		SCD_API S_Superellipsoid(Scalar a,Scalar b,Scalar c,Scalar epsilon1,Scalar epsilon2);
		SCD_API virtual ~S_Superellipsoid(void);

		SCD_API virtual Point3  l_Support(const Vector3& v, int& lastFeature)const;

		SCD_API virtual S_ObjectType getType() const;

    #ifdef WITH_OPENGL
		SCD_API virtual void drawGLInLocalCordinates();
    #endif

	protected:
		Scalar a_,b_,c_,epsilon1_,epsilon2_;
		int displist_;
		int slices_, stacks_;

		Scalar _2_e1on2,_2_e2on2,_2on2_e1,_2on2_e2;



	};
}

#endif
