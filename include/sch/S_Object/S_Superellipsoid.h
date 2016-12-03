#ifndef _S_SUPERELLIPSOID
#define _S_SUPERELLIPSOID

#pragma once

#include <sch/S_Object/S_ObjectNonNormalized.h>

namespace sch
{

  class S_Superellipsoid :
    public S_ObjectNonNormalized
  {
  public:
    SCH_API S_Superellipsoid(Scalar a,Scalar b,Scalar c,Scalar epsilon1,Scalar epsilon2);
    SCH_API virtual ~S_Superellipsoid(void);

    SCH_API virtual Point3  l_Support(const Vector3& v, int& lastFeature)const;

    SCH_API virtual S_ObjectType getType() const;

    SCH_API virtual void getEllipsoidParameter(Scalar & a, Scalar & b, Scalar & c,
        Scalar & epsilon1, Scalar & epsilon2) const;

  protected:
    Scalar a_,b_,c_,epsilon1_,epsilon2_;

    Scalar _2_e1on2,_2_e2on2,_2on2_e1,_2on2_e2;
  };
}

#endif
