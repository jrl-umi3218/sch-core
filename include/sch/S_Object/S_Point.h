#ifndef _S_POINT_H
#define _S_POINT_H

#pragma once
#include <sch/sch_api.h>
#include <sch/S_Object/S_ObjectNonNormalized.h>

namespace sch
{
  class S_Point :
    public S_ObjectNonNormalized
  {
  public:
    SCH_API S_Point(void);
    SCH_API ~S_Point(void);

    void setDisplayRadius( Scalar r){displayRadius_ = r;}
    Scalar getDisplayRadius() const {return displayRadius_ ;}


  protected:
    SCH_API virtual Point3 l_Support(const Vector3& v, int& lastFeature)const;
    SCH_API virtual	S_ObjectType getType() const;

    Scalar displayRadius_;
  };
}
#endif
