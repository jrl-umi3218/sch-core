#ifndef __S_OBJECTNONNORMALIZED
#define __S_OBJECTNONNORMALIZED

#pragma once
#include <SCD/S_Object/S_Object.h>

#include <boost/serialization/base_object.hpp>

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

  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    boost::serialization::base_object<S_Object>(*this);
  }
};

#include <SCD/S_Object/S_ObjectNonNormalized.hxx>

}

#endif
