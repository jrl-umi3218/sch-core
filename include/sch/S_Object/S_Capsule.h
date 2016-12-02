#ifndef _S_CAPSULE_H
#define _S_CAPSULE_H

#include <sch/S_Object/S_ObjectNormalized.h>

namespace sch
{
  class S_Capsule :
    public S_ObjectNormalized
  {
  public:
    SCH_API S_Capsule(Point3 p1, Point3 p2, Scalar radius);
    SCH_API ~S_Capsule();



  protected:
    SCH_API virtual Point3 l_Support(const Vector3& v, int& lastFeature)const;
    SCH_API virtual	S_ObjectType getType() const;

    Point3 p1_, p2_;

    Scalar radius_;
  };
}
#endif //_S_CAPSULE_H
