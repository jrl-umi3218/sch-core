#ifndef __S_OBJECTNONNORMALIZED
#define __S_OBJECTNONNORMALIZED

#pragma once
#include "s_object.h"

namespace SCD
{

class S_ObjectNonNormalized :
	public S_Object
{
public:
	S_ObjectNonNormalized(void);
	~S_ObjectNonNormalized(void);

	/*! 
	 *  \brief put the vector in objects coordinates, then calls l_support, without normalizing it
	 *  \param v direction vector
	 *  \return returns the support point.
	 */ 	
	virtual Point3 support(const Vector3& v) const;

	/*! 
	 *  \brief put the vector in objects coordinates, then calls l_support, without normalizing it
	 *  \param v direction vector
     *  \param lastFeature tells in which feature we were in last query, amd returns the new one. very important in spatio-temporal coherence
	 *  \return returns the support point.
	 */
	virtual Point3 support(const Vector3& v, int & LastFeature) const;
};

#include "S_ObjectNonNormalized.hxx"

}

#endif