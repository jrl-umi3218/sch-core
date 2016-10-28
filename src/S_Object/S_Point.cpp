#include <sch/S_Object/S_Point.h>

using namespace sch;
S_Point::S_Point():displayRadius_(1e-3)
{
}

S_Point::~S_Point()
{
}

void S_Point::setDisplayRadius(Scalar r)
{
  displayRadius_ = r;
}

Scalar S_Point::getDisplayRadius() const
{
  return displayRadius_;
}

Point3 S_Point::l_Support(const Vector3& /*v*/, int& /*lastFeature*/)const
{
  return Point3(0,0,0);
}

S_Object::S_ObjectType S_Point::getType() const
{
  return S_Object::T_Point;
}
