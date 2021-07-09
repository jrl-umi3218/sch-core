#include <sch/S_Object/S_Cylinder.h>

using namespace sch;

S_Cylinder * S_Cylinder::clone() const
{
  return new S_Cylinder(*this);
}

S_Cylinder::S_Cylinder(Point3 p1, Point3 p2, Scalar radius): p1_(p1),p2_(p2),radius_(radius)
{
  normal_ = p2_ - p1_;
  assert(normal_.norm() != 0);
  normal_.normalize();
}

S_Cylinder::~S_Cylinder()
{
}

Point3 S_Cylinder::l_Support(const Vector3& v, int& /*lastFeature*/)const
{
  Point3 d = p1_;
  double dot = normal_ * v;
  if (dot > 0)
  {
    d = p2_;
  }
  Vector3 proj = v - normal_ * dot;
  double proj_norm = proj.norm();
  if(proj_norm != 0)
  {
    return d + proj * (radius_ / proj_norm);
  }
  else
  {
    return d;
  }
}

S_Object::S_ObjectType S_Cylinder::getType() const
{
  return S_Object::TCylinder;
}

const Point3 & S_Cylinder::getP1() const
{
  return p1_;
}

const Point3 & S_Cylinder::getP2() const
{
  return p2_;
}

Scalar S_Cylinder::getRadius() const
{
  return radius_;
}
