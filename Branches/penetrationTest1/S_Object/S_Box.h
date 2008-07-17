
#ifndef _S_BOX_H
#define _S_BOX_H 

#pragma once



#include "s_objectnonnormalized.h"

namespace SCD
{

	class S_Box :
		public S_ObjectNonNormalized
	{
	public:
		/*!
		* \brief constructor
		* \param width, the width of the box (x axis)
		* \param height, the height of the box (y axis)
		* \param depth, the depth of the box (z axis)
		*/
		S_Box(Scalar width,Scalar height,Scalar depth);


		virtual ~S_Box(void);


		virtual Point3  n_Support(const Vector3& v, int& lastFeature)const;

		virtual S_ObjectType getType() const;

		virtual void drawGLInLocalCordinates();

	protected :
		Scalar a_,b_,c_;


	};

}
#endif
