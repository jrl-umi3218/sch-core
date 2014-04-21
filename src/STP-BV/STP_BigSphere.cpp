#include <sch/STP-BV/STP_BigSphere.h>
#include <sch/STP-BV/STP_BigSphere.h>

using namespace sch;

STP_BigSphere::STP_BigSphere()
{
}

STP_BigSphere::STP_BigSphere(Scalar radius, Point3 center):
  m_radius(radius), m_center(center)
{
}

STP_BigSphere::STP_BigSphere(const STP_BigSphere& s):
  STP_Feature(s), m_radius(s.m_radius), m_center(s.m_center)
{
  m_VVR0 = s.m_VVR0;
  m_VVR1 = s.m_VVR1;
  m_VVR2 = s.m_VVR2;
}

STP_BigSphere::~STP_BigSphere()
{
}

const Point3& STP_BigSphere::getCenter() const
{
  return m_center;
}

void STP_BigSphere::setVVR(const STP_VVR* vvr)
{
  if(!vvr)
    return;

  m_VVR0 = vvr[0];
  m_VVR1 = vvr[1];
  m_VVR2 = vvr[2];
}

void STP_BigSphere::print() const
{
  std::cout << "type : big sphere" << std::endl;
  std::cout << "center : " << m_center[0] << ", " << m_center[1] << ", " << m_center[2] << std::endl;
  std::cout << "radius : " << m_radius << std::endl << std::endl;
}

bool STP_BigSphere::isHere(const Vector3& v) const
{
  if(m_VVR0.isInside(v))
  {
    if(m_VVR1.isInside(v))
    {
      if(m_VVR2.isInside(v))
        return true;
      else
        return false;
    }
    else
      return false;
  }
  else
    return false;
}

bool STP_BigSphere::isHereFarthestNeighbour(const Vector3& v)
{
  bool res = true;
  Scalar tmp1 = 0;
  Scalar tmp2 = 0;
  Scalar tmp3 = 0;

//	std::cout << "test is here big sphere" << std::endl;

  m_nextBV[0] = m_nextBV[1] = m_nextBV[2] = -1;

  if(!(m_VVR0.isInside(v)))
  {
    res = false;
    tmp1 = m_VVR0.getDistance(v);
    m_nextBV[0] = m_VVR0.m_outerSTP;
  }
  if(!(m_VVR1.isInside(v)))
  {
    res = false;
    tmp2 = m_VVR1.getDistance(v);
    m_nextBV[1] = m_VVR1.m_outerSTP;
  }
  if(!(m_VVR2.isInside(v)))
  {
    res = false;
    tmp3 = m_VVR2.getDistance(v);
    m_nextBV[2] = m_VVR2.m_outerSTP;
  }

  if(m_nextBV[0] != -1)
  {
    if(m_nextBV[1] != -1)
    {
      if(m_nextBV[2] != -1)
      {
        //compare all three values
        if(tmp2 < tmp1)
        {
          int tmp = m_nextBV[0];
          if(tmp3 < tmp2)
          {
            m_nextBV[0] = m_nextBV[2];
            m_nextBV[2] = tmp;
          }
          else if(tmp3 < tmp1)
          {
            m_nextBV[0] = m_nextBV[1];
            m_nextBV[1] = m_nextBV[2];
            m_nextBV[2] = tmp;
          }
          else
          {
            m_nextBV[0] = m_nextBV[1];
            m_nextBV[1] = tmp;
          }
        }
        else if(tmp3 < tmp2)
        {
          if(tmp3 < tmp1)
          {
            int tmp = m_nextBV[0];
            m_nextBV[0] = m_nextBV[2];
            m_nextBV[2] = m_nextBV[1];
            m_nextBV[1] = tmp;
          }
          else
          {
            int tmp = m_nextBV[1];
            m_nextBV[1] = m_nextBV[2];
            m_nextBV[2] = tmp;
          }
        }
      }
      else
      {
        //compare tmp1 to tmp2
        if(tmp1 > tmp2)
        {
          int tmp = m_nextBV[0];
          m_nextBV[0] = m_nextBV[1];
          m_nextBV[1] = tmp;
        }
      }
    }
    else if(m_nextBV[2] != -1)
    {
      //compare tmp1 to tmp3
      if(tmp1 <= tmp3)
      {
        m_nextBV[1] = m_nextBV[2];
        m_nextBV[2] = -1;
      }
      else
      {
        m_nextBV[1] = m_nextBV[0];
        m_nextBV[0] = m_nextBV[2];
        m_nextBV[2] = -1;
      }
    }
  }
  else if(m_nextBV[1] != -1)
  {
    if(m_nextBV[2] != -1)
    {
      //compare tmp2 to tmp3
      if(tmp2 < tmp3)
      {
        m_nextBV[0] = m_nextBV[1];
        m_nextBV[1] = m_nextBV[2];
        m_nextBV[2] = -1;
      }
      else
      {
        m_nextBV[0] = m_nextBV[2];
        m_nextBV[2] = -1;
      }
    }
    else
    {
      m_nextBV[0] = m_nextBV[1];
      m_nextBV[1] = m_nextBV[2] = -1;
    }
  }
  else if(m_nextBV[2] != -1)
  {
    m_nextBV[0] = m_nextBV[2];
    m_nextBV[1] = m_nextBV[2] = -1;
  }

  return res;
}



bool STP_BigSphere::isHereFarthestNeighbourPrime(const Vector3& v)
{
  Scalar tmp1, tmp2, tmp3;

//	std::cout << "test is here big sphere" << std::endl;

  //m_nextBV[0] = m_nextBV[1] = m_nextBV[2] = -1;

  tmp1 = m_VVR0.isInsidePrime(v);
  tmp2 = m_VVR1.isInsidePrime(v);
  tmp3 = m_VVR2.isInsidePrime(v);

  if ((tmp1>=0)&&(tmp2>=0)&&(tmp3>=0))
    return true;

  else if (tmp1<tmp2)
  {
    if (tmp1<tmp3)
    {
      m_nextBVPrime = m_VVR0.m_outerSTP;
    }
    else //(tmp1>=tmp3)
    {
      m_nextBVPrime = m_VVR2.m_outerSTP;
    }
  }
  else //(tmp1>=tmp2)
  {
    if (tmp2<tmp3)
    {
      m_nextBVPrime = m_VVR1.m_outerSTP;
    }
    else //(tmp2>=tmp3)
    {
      m_nextBVPrime = m_VVR2.m_outerSTP;
    }
  }
  return false;
}




bool STP_BigSphere::isHereFirstNeighbour(const Vector3& v)
{

//	std::cout << "test is here big sphere" << std::endl;


  if(m_VVR0.isInsidePrime(v)<0)
  {
    m_nextBVPrime = m_VVR0.m_outerSTP;
    return false;

  }
  if(m_VVR1.isInsidePrime(v)<0)
  {
    m_nextBVPrime = m_VVR1.m_outerSTP;
    return false;

  }
  if(m_VVR2.isInsidePrime(v)<0)
  {
    m_nextBVPrime = m_VVR2.m_outerSTP;
    return false;

  }
  return true;

}


bool STP_BigSphere::isHereFirstNeighbourPrime(const Vector3& v,int idp)
{
//	std::cout << "test is here big sphere" << std::endl;
  if((m_VVR0.m_outerSTP!=idp)&&(m_VVR0.isInsidePlane(v)<0))
  {
    m_nextBVPrime = m_VVR0.m_outerSTP;
    return false;

  }
  if((m_VVR1.m_outerSTP!=idp)&&(m_VVR1.isInsidePlane(v)<0))
  {
    m_nextBVPrime = m_VVR1.m_outerSTP;
    return false;

  }
  if((m_VVR2.m_outerSTP!=idp)&&(m_VVR2.isInsidePlane(v)<0))
  {
    m_nextBVPrime = m_VVR2.m_outerSTP;
    return false;
  }
  return true;
}


bool STP_BigSphere::isHereHybrid(const Vector3& v,int idp)
{
//	std::cout << "test is here big sphere" << std::endl;

  if((m_VVR0.m_outerSTP!=idp)&&(m_VVR0.isInsidePlane(v)<0))
  {
    m_nextBVPrime = m_VVR0.m_outerSTP;
    return false;
  }
  if((m_VVR1.m_outerSTP!=idp)&&(m_VVR1.isInsidePlane(v)<0))
  {
    m_nextBVPrime = m_VVR1.m_outerSTP;
    return false;
  }
  if((m_VVR2.m_outerSTP!=idp)&&(m_VVR2.isInsidePlane(v)<0))
  {
    m_nextBVPrime = m_VVR2.m_outerSTP;
    return false;
  }
  return true;
}


int STP_BigSphere::getNextBV(unsigned int id) const
{
  if(id < 3)
    return m_nextBV[id];
  else
    return -1;
}


Scalar STP_BigSphere::supportH(const Vector3& v) const
{
  //tenir compte du centre ??
  return m_radius * v.norm();
}

Point3 STP_BigSphere::support(const Vector3& v) const
{
  return m_center + v*m_radius;
}

bool STP_BigSphere::ray_cast(const Point3& source, const Point3& target,
                             Scalar& param, Vector3& normal) const
{
  Vector3 r = target - source;
  Scalar  delta = -source*r;
  Scalar  r_length2 = r.norm();
  Scalar  sigma = delta * delta - r_length2 * (source.normsquared() - m_radius * m_radius);

  if (sigma >= Scalar(0.0))
    // The line trough source and target intersects the sphere.
  {
    Scalar sqrt_sigma = sqrt(sigma);
    // We need only the sign of lambda2, so the division by the positive
    // r_length2 can be left out.
    Scalar lambda2 = (delta + sqrt_sigma) /* / r_length2 */ ;
    if (lambda2 >= Scalar(0.0))
      // The ray points at the sphere
    {
      Scalar lambda1 = (delta - sqrt_sigma) / r_length2;
      if (lambda1 <= param)
        // The ray hits the sphere, since
        // [lambda1, lambda2] overlaps [0, param].
      {
        if (lambda1 > Scalar(0.0))
        {
          param = lambda1;
          normal = (source + r * lambda1) / m_radius;
          // NB: division by m_radius to normalize the normal.
        }
        else
        {
          param = Scalar(0.0);
          normal.Set(Scalar(0.0), Scalar(0.0), Scalar(0.0));
        }
        return true;
      }
    }
  }
  return false;
}


STP_Feature* STP_BigSphere::clone() const
{
  return new STP_BigSphere(*this);
}

