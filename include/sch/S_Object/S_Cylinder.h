#ifndef _S_CYLINDER_H
#define _S_CYLINDER_H

#include <sch/S_Object/S_ObjectNormalized.h>

namespace sch
{
  class S_Cylinder :
    public S_ObjectNormalized
  {
  public:
    SCH_API S_Cylinder(Point3 p1, Point3 p2, Scalar radius);
    SCH_API ~S_Cylinder();

    SCH_API const Point3 & getP1() const;

    SCH_API const Point3 & getP2() const;

    SCH_API Scalar getRadius() const;

  protected:
    SCH_API virtual Point3 l_Support(const Vector3& v, int& lastFeature)const;
    SCH_API virtual S_ObjectType getType() const;

    Point3 p1_, p2_;

    Vector3 normal_;

    Scalar radius_;
  };
}
#endif //_S_CYLINDER_H

