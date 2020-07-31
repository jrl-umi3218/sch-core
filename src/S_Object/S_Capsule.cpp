#include <sch/S_Object/S_Capsule.h>

using namespace sch;

S_Capsule::S_Capsule(Point3 p1, Point3 p2, Scalar radius): p1_(p1),p2_(p2),radius_(radius)
{
}

S_Capsule::~S_Capsule()
{
}

Point3 S_Capsule::l_Support(const Vector3& v, int& /*lastFeature*/)const
{
  Point3 d(p2_);
  d -= p1_;

  if (d*v>0)
  {
    d = p2_;
  }
  else
  {
    d = p1_;
  }

  d += v*radius_;

  return d;
}

S_Object::S_ObjectType S_Capsule::getType() const
{
  return S_Object::TCapsule;
}

const Point3 & S_Capsule::getP1() const
{
  return p1_;
}

const Point3 & S_Capsule::getP2() const
{
  return p2_;
}

Scalar S_Capsule::getRadius() const
{
  return radius_;
}
