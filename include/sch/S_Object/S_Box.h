#ifndef _S_BOX_H
#define _S_BOX_H

#pragma once

#include <sch/S_Object/S_ObjectNonNormalized.h>

namespace sch
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
    SCH_API S_Box(Scalar width,Scalar height,Scalar depth);
    SCH_API virtual ~S_Box(void);


    SCH_API virtual Point3  l_Support(const Vector3& v, int& lastFeature)const;

    SCH_API virtual S_ObjectType getType() const;

    SCH_API virtual void getBoxParameters(Scalar & a, Scalar & b, Scalar & c) const;
  protected :
    Scalar a_,b_,c_;
  };
}

#endif

/**
 * \example      example0.cpp
 * This example shows the normal use of the SCH library:
 * The simplest proximity queries
 */
