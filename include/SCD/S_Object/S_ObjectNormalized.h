#pragma once
#include <SCD/scd_api.h>
#include <SCD/S_Object/S_Object.h>

#ifndef _S_OBJECTNORMALIZED_H
#define _S_OBJECTNORMALIZED_H

#ifdef WITH_BOOST_1_36
#include <SCD/boost/archive/detail/oserializer.hpp>
#endif
#include <boost/serialization/base_object.hpp>

namespace SCD
{
	class S_ObjectNormalized :
		public S_Object
	{
	public:
		SCD_API S_ObjectNormalized(void);
		SCD_API virtual ~S_ObjectNormalized(void);

		/*!
		*  \brief put the vector NORMALIZED it in objects coordinates, then calls l_support. DO NOT OVERLOAD IT UNLESS YOU KNOW WHAT YOU ARE DOING (if you want to define the support function, overload l_support)
		*  \param v direction vector
		*  \return returns the support point.
		*/ 
		SCD_API virtual Point3 support(const Vector3& v) const;

		/*! 
		*  \brief version of support with last feature optimization
		*  \param v direction vector
		*  \param lastFeature tells in which feature we were in last query, and returns the new one. very important in spatio-temporal coherence
		*  \return returns the support point.
		*/ 
		SCD_API virtual Point3 support(const Vector3& v, int & LastFeature) const;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int /*version*/)
    {
      ar & boost::serialization::base_object<S_Object>(*this);
    }
	};

#include <SCD/S_Object/S_ObjectNormalized.hxx>
}

#endif
