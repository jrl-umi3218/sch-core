#pragma once
#ifndef _S_SPHERE_H
#define _S_SPHERE_H

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
    SCH_API S_Sphere(const Scalar& radius);
    SCH_API virtual ~S_Sphere();

    SCH_API virtual Point3 l_Support(const Vector3& v, int& lastFeature)const;

    SCH_API virtual S_ObjectType getType() const;

    SCH_API virtual Scalar getRadius() const;

  protected:
    Scalar radius_;
  };
}

#endif

/**
 * \example      example0.cpp
 * This example shows the normal use of the SCH library:
 * The simplest proximity queries (How to transform a sphere into an ellipsoid)
 */
