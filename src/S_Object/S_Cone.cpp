#include <sch/S_Object/S_Cone.h>

using namespace sch;


S_Cone::S_Cone(const Scalar& angle, const Scalar &  height) 

{
  if (fabs(angle) >= M_PI/2)
  {
    throw std::domain_error("Ivalig angle for a cone. It should be < M_PI/2");
  }
  
  angle_=fabs(angle);
  height_=fabs(angle);
  angleTan_=tan(angle_);
  baseRadius_=height_*angleTan_;
  
  slices_ = 100;
  stacks_ = 4; /// we don't need many stacks to display a cone
} 

S_Cone::~S_Cone(void)
{
}


Point3 S_Cone::l_Support(const Vector3& v, int& /*lastFeature*/)const
{
  Scalar norm = sqrt(v[0] * v[0] + v[1] * v[1]);
  if (norm < sch::epsilon)
  {
    if (v[2] >= 0)    
    {
      return Point3(0., 0., height_);
    } 
    else
    {
      return Point3(0., 0., 0.);
    }
  }
  else
  {
    if ( v[2] < - angleTan_ * norm)
    {
      return Point3(0., 0., 0.);
    }
    else
    {
      Scalar normInverse = 1 / norm;
      return Point3(normInverse * v[0]*baseRadius_, normInverse * v[1]*baseRadius_, height_);
    }
  }

}


S_Object::S_ObjectType S_Cone::getType() const
{
  return S_Object::TCone;
}

Scalar S_Cone::getAngle() const
{
  return angle_;
}

Scalar S_Cone::getHeight() const
{
  return height_;
}
