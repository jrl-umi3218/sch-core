#include <sch/STP-BV/STP_Feature.h>

using namespace sch;
s_STP_VVR::s_STP_VVR():
  m_axis(0.0, 0.0, 0.0), m_cosangle(0.0)
{
}

s_STP_VVR::s_STP_VVR(const s_STP_VVR& vvr):
  m_axis(vvr.m_axis), m_cosangle(vvr.m_cosangle), m_outerSTP(vvr.m_outerSTP)
{
  Scalar n;
  if ((n=m_axis.norm())!=0)
    m_axis/=n;
}

s_STP_VVR::s_STP_VVR(Scalar cosangle, const Vector3& axis):
  m_axis(axis), m_cosangle(cosangle)
{
  Scalar n;
  if ((n=m_axis.norm())!=0)
    m_axis/=n;
}


bool s_STP_VVR::isInside(const Vector3& v) const
{
  //std::cout << "is inside ?" << std::endl;
  if (v.normsquared() == 0)
    return true;

  Scalar res = m_axis * v / (v.norm() * m_axis.norm());
  return (res >= m_cosangle);
}


Scalar s_STP_VVR::getDistance(const Vector3& v) const
{
  return (m_axis*v) / (v.norm() * m_axis.norm()) - m_cosangle;
}

bool s_STP_VVR::isSameLimit(const s_STP_VVR& vvr) const
{
  double epsilon = 1e-8;

  if(m_cosangle == 0.0 && vvr.m_cosangle == 0.0)
  {
    if( (fabs(m_axis[0] + vvr.m_axis[0]) < epsilon) && (fabs(m_axis[1] + vvr.m_axis[1]) < epsilon) && (fabs(m_axis[2] + vvr.m_axis[2]) < epsilon) )
      return true;
    else if( (fabs(m_axis[0] - vvr.m_axis[0]) < epsilon) && (fabs(m_axis[1] - vvr.m_axis[1]) < epsilon) && (fabs(m_axis[2] - vvr.m_axis[2]) < epsilon) )
      return true;
    else
      return false;
  }
  else
    return this->operator ==(vvr);
}

s_STP_VVR& s_STP_VVR::operator=(const s_STP_VVR& vvr)
{
  m_axis = vvr.m_axis;
  m_cosangle = vvr.m_cosangle;
  m_outerSTP = vvr.m_outerSTP;

  return *this;
}

bool s_STP_VVR::operator==(const s_STP_VVR& vvr) const
{
  double epsilon = 1e-7;

  if( (fabs(m_axis[0] - vvr.m_axis[0]) < epsilon)
      && (fabs(m_axis[1] - vvr.m_axis[1]) < epsilon)
      && (fabs(m_axis[2] - vvr.m_axis[2]) < epsilon)
      && (fabs(m_cosangle - vvr.m_cosangle) < epsilon) )
    return true;
  else
    return false;
}

s_STN_VVR::s_STN_VVR():
  m_axis(Scalar(0), Scalar(0), Scalar(0)), m_cosangle(Scalar(0))
{
}

s_STN_VVR::s_STN_VVR(const s_STN_VVR& vvr):
  m_axis(vvr.m_axis), m_cosangle(vvr.m_cosangle), m_outerSTP(vvr.m_outerSTP)
{
}

s_STN_VVR::s_STN_VVR(Scalar cosangle, const Vector3& axis):
  m_axis(axis), m_cosangle(cosangle)
{
}

bool s_STN_VVR::isInside(const Vector3& v) const
{
  //std::cout << "is inside ?" << std::endl;

  if(v.normsquared()==0)
    return true;

  Scalar res = m_axis*v / (v.norm() * m_axis.norm());
  return (res >= m_cosangle);
}

Scalar s_STN_VVR::getDistance(const Vector3& v) const
{
  return m_axis*v / (v.norm() * m_axis.norm()) - m_cosangle ;
}

bool s_STN_VVR::isSameLimit(const s_STN_VVR& vvr) const
{
  Scalar epsilon = 1e-8;

  if((m_cosangle==0 )&& (vvr.m_cosangle==0))
  {
    if( (fabs(m_axis[0] + vvr.m_axis[0]) < epsilon) && (fabs(m_axis[1] + vvr.m_axis[1]) < epsilon) && (fabs(m_axis[2] + vvr.m_axis[2]) < epsilon) )
      return true;
    else if( (fabs(m_axis[0] - vvr.m_axis[0]) < epsilon) && (fabs(m_axis[1] - vvr.m_axis[1]) < epsilon) && (fabs(m_axis[2] - vvr.m_axis[2]) < epsilon) )
      return true;
    else
      return false;
  }
  else
    return this->operator ==(vvr);
}

s_STN_VVR& s_STN_VVR::operator=(const s_STN_VVR& vvr)
{
  m_axis = vvr.m_axis;
  m_cosangle = vvr.m_cosangle;
  m_outerSTP = vvr.m_outerSTP;

  return *this;
}

bool s_STN_VVR::operator==(const s_STN_VVR& vvr) const
{
  Scalar epsilon = 1e-7;

  if( (fabs(m_axis[0] - vvr.m_axis[0]) < epsilon)
      && (fabs(m_axis[1] - vvr.m_axis[1]) < epsilon)
      && (fabs(m_axis[2] - vvr.m_axis[2]) < epsilon)
      && (fabs(m_cosangle - vvr.m_cosangle) < epsilon) )
    return true;
  else
    return false;
}

STP_Feature::STP_Feature()
{
}

STP_Feature::~STP_Feature()
{
}
