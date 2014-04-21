#include <sch/STP-BV/STP_Torus.h>

using namespace sch;

s_STP_Circle::s_STP_Circle(const Vector3& normal, const Point3& center, Scalar radius):
  m_normal(normal), m_center(center), m_radius(radius)
{
  m_normal.normalize();
}

STP_Torus::STP_Torus()
{
}

STP_Torus::STP_Torus(const Vector3& cNormal, const Point3& cCenter, Scalar cRadius, Scalar sRadius):
  m_circle(cNormal, cCenter, cRadius), m_sphereRadius(sRadius)
{
}

STP_Torus::STP_Torus(const STP_Torus& t):
  STP_Feature(t),m_circle(t.m_circle.m_normal, t.m_circle.m_center, t.m_circle.m_radius), m_sphereRadius(t.m_sphereRadius)
{
  m_VVR0 = t.m_VVR0;
  m_VVR1 = t.m_VVR1;
  m_VVR2 = t.m_VVR2;
  m_VVR3 = t.m_VVR3;
}

STP_Torus::~STP_Torus()
{
}


void STP_Torus::setVVR(const STP_VVR* vvr)
{
  if(!vvr)
    return;

  m_VVR0 = vvr[0];
  m_VVR1 = vvr[1];
  m_VVR2 = vvr[2];
  m_VVR3 = vvr[3];
}

void STP_Torus::print() const
{
  std::cout << "type : torus" << std::endl;
  std::cout << "center : " << m_circle.m_center[0] << ", " << m_circle.m_center[1] << ", " << m_circle.m_center[2] << std::endl;
  std::cout << "circle radius : " << m_circle.m_radius << std::endl;
  std::cout << "circle normal : " << m_circle.m_normal[0] << ", " << m_circle.m_normal[1] << ", " << m_circle.m_normal[2] << std::endl;
  std::cout << "sphere radius : " << this->m_sphereRadius << std::endl << std::endl;
}

bool STP_Torus::isHere(const Vector3& v) const
{
  //outside first cone ?
  if(!m_VVR0.isInside(v))
  {
    //outside second cone ?
    if(!m_VVR1.isInside(v))
    {
      //outside first plane ?
      if(!m_VVR2.isInside(v))
      {
        //outside second plane ?
        if(!m_VVR3.isInside(v))
        {
          return true;
        }
        else
          return false;
      }
      else
        return false;
    }
    else
      return false;
  }
  else
    return false;
}

bool STP_Torus::isHereFarthestNeighbour(const Vector3& v)
{
  bool res = true;
  Scalar tmp1 = 0;
  Scalar tmp2 = 0;
  Scalar tmp3 = 0;
  Scalar tmp4 = 0;

  //std::cout << "test is here torus" << std::endl;

  m_nextBV[0] = m_nextBV[1] = m_nextBV[2] = m_nextBV[3] = -1;

  if(m_VVR0.isInside(v))
  {
    res = false;
    tmp1 = m_VVR0.getDistance(v);
    m_nextBV[0] = m_VVR0.m_outerSTP;
  }
  if(m_VVR1.isInside(v))
  {
    res = false;
    tmp2 = m_VVR1.getDistance(v);
    m_nextBV[1] = m_VVR1.m_outerSTP;
  }
  if(m_VVR2.isInside(v))
  {
    res = false;
    tmp3 = m_VVR2.getDistance(v);
    m_nextBV[2] = m_VVR2.m_outerSTP;
  }
  if(m_VVR3.isInside(v))
  {
    res = false;
    tmp4 = m_VVR3.getDistance(v);
    m_nextBV[3] = m_VVR3.m_outerSTP;
  }

  if(m_nextBV[0] != -1)
  {
    if(m_nextBV[1] != -1)
    {
      if(m_nextBV[2] != -1)
      {
        if(m_nextBV[3] != -1)
        {
          //compare the four values
          if(tmp2 < tmp1)
          {
            if(tmp3 < tmp2)
            {
              if(tmp4 < tmp3)
              {
                int tmp = m_nextBV[0];
                m_nextBV[0] = m_nextBV[3];
                m_nextBV[3] = tmp;
                tmp = m_nextBV[1];
                m_nextBV[1] = m_nextBV[2];
                m_nextBV[2] = tmp;
              }
              else if(tmp4 < tmp2)
              {
                int tmp = m_nextBV[0];
                m_nextBV[0] = m_nextBV[2];
                m_nextBV[2] = m_nextBV[1];
                m_nextBV[1] = m_nextBV[3];
                m_nextBV[3] = tmp;
              }
              else if(tmp4 < tmp1)
              {
                int tmp = m_nextBV[0];
                m_nextBV[0] = m_nextBV[2];
                m_nextBV[2] = m_nextBV[3];
                m_nextBV[3] = tmp;
              }
              else
              {
                int tmp = m_nextBV[0];
                m_nextBV[0] = m_nextBV[2];
                m_nextBV[2] = tmp;
              }
            }
            else if(tmp3 < tmp1)
            {
              if(tmp4 < tmp2)
              {
                int tmp = m_nextBV[0];
                m_nextBV[0] = m_nextBV[3];
                m_nextBV[3] = tmp;
              }
              else if(tmp4 < tmp3)
              {
                int tmp = m_nextBV[0];
                m_nextBV[0] = m_nextBV[1];
                m_nextBV[1] = m_nextBV[3];
                m_nextBV[3] = tmp;
              }
              else if(tmp4 < tmp1)
              {
                int tmp = m_nextBV[0];
                m_nextBV[0] = m_nextBV[1];
                m_nextBV[1] = m_nextBV[2];
                m_nextBV[2] = m_nextBV[3];
                m_nextBV[3] = tmp;
              }
              else
              {
                int tmp = m_nextBV[0];
                m_nextBV[0] = m_nextBV[1];
                m_nextBV[1] = m_nextBV[2];
                m_nextBV[2] = tmp;
              }
            }
            else
            {
              if(tmp4 < tmp2)
              {
                int tmp = m_nextBV[0];
                m_nextBV[0] = m_nextBV[3];
                m_nextBV[3] = m_nextBV[2];
                m_nextBV[2] = tmp;
              }
              else if(tmp4 < tmp1)
              {
                int tmp = m_nextBV[0];
                m_nextBV[0] = m_nextBV[1];
                m_nextBV[1] = m_nextBV[3];
                m_nextBV[3] = m_nextBV[2];
                m_nextBV[2] = tmp;
              }
              else if(tmp4 < tmp3)
              {
                int tmp = m_nextBV[0];
                m_nextBV[0] = m_nextBV[1];
                m_nextBV[1] = tmp;
                tmp = m_nextBV[2];
                m_nextBV[2] = m_nextBV[3];
                m_nextBV[3] = tmp;
              }
              else
              {
                int tmp = m_nextBV[0];
                m_nextBV[0] = m_nextBV[1];
                m_nextBV[1] = tmp;
              }
            }
          }
          else if(tmp3 < tmp2)
          {
            if(tmp3 < tmp1)
            {
              if(tmp4 < tmp3)
              {
                int tmp = m_nextBV[0];
                m_nextBV[0] = m_nextBV[3];
                m_nextBV[3] = m_nextBV[1];
                m_nextBV[1] = m_nextBV[2];
                m_nextBV[2] = tmp;
              }
              else if(tmp4 < tmp1)
              {
                int tmp = m_nextBV[0];
                m_nextBV[0] = m_nextBV[2];
                m_nextBV[1] = tmp;
                tmp = m_nextBV[1];
                m_nextBV[1] = m_nextBV[3];
                m_nextBV[3] = tmp;
              }
              else if(tmp4 < tmp2)
              {
                int tmp = m_nextBV[0];
                m_nextBV[0] = m_nextBV[2];
                m_nextBV[2] = m_nextBV[3];
                m_nextBV[3] = m_nextBV[1];
                m_nextBV[1] = tmp;
              }
              else
              {
                int tmp = m_nextBV[0];
                m_nextBV[0] = m_nextBV[2];
                m_nextBV[2] = m_nextBV[1];
                m_nextBV[1] = tmp;
              }
            }
            else
            {
              if(tmp4 < tmp1)
              {
                int tmp = m_nextBV[0];
                m_nextBV[0] = m_nextBV[3];
                m_nextBV[3] = m_nextBV[1];
                m_nextBV[1] = tmp;
              }
              else if(tmp4 < tmp3)
              {
                int tmp = m_nextBV[1];
                m_nextBV[1] = m_nextBV[3];
                m_nextBV[3] = tmp;
              }
              else if(tmp4 < tmp2)
              {
                int tmp = m_nextBV[1];
                m_nextBV[1] = m_nextBV[2];
                m_nextBV[2] = m_nextBV[3];
                m_nextBV[3] = tmp;
              }
              else
              {
                int tmp = m_nextBV[1];
                m_nextBV[1] = m_nextBV[2];
                m_nextBV[2] = tmp;
              }
            }
          }
          else if(tmp4 < tmp3)
          {
            if(tmp4 < tmp2)
            {
              if(tmp4 < tmp1)
              {
                int tmp = m_nextBV[0];
                m_nextBV[0] = m_nextBV[3];
                m_nextBV[3] = m_nextBV[2];
                m_nextBV[2] = m_nextBV[1];
                m_nextBV[1] = tmp;
              }
              else
              {
                int tmp = m_nextBV[1];
                m_nextBV[1] = m_nextBV[3];
                m_nextBV[3] = m_nextBV[2];
                m_nextBV[2] = tmp;
              }
            }
            else
            {
              int tmp = m_nextBV[2];
              m_nextBV[2] = m_nextBV[3];
              m_nextBV[3] = tmp;
            }
          }
        }
        else
        {
          //compare the first three values

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
          m_nextBV[3] = -1;
        }
      }
      else if(m_nextBV[3] != -1)
      {
        //compare tmp1, tmp2 and tmp4
        if(tmp2 < tmp1)
        {
          if(tmp4 < tmp2)
          {
            m_nextBV[2] = m_nextBV[0];
            m_nextBV[0] = m_nextBV[3];
          }
          else if(tmp4 < tmp1)
          {
            m_nextBV[2] = m_nextBV[0];
            m_nextBV[0] = m_nextBV[1];
            m_nextBV[1] = m_nextBV[3];
          }
          else
          {
            m_nextBV[0] = m_nextBV[1];
            m_nextBV[1] = m_nextBV[0];
            m_nextBV[2] = m_nextBV[3];
          }
        }
        else if(tmp4 < tmp2)
        {
          if(tmp4 < tmp1)
          {
            m_nextBV[2] = m_nextBV[1];
            m_nextBV[1] = m_nextBV[0];
            m_nextBV[0] = m_nextBV[3];
          }
          else
          {
            m_nextBV[2] = m_nextBV[1];
            m_nextBV[1] = m_nextBV[3];
          }
        }
        else
        {
          m_nextBV[2] = m_nextBV[3];
        }
        m_nextBV[3] = -1;
      }
      else
      {
        //compare tmp1 and tmp2
        if(tmp2 < tmp1)
        {
          m_nextBV[2] = m_nextBV[0];
          m_nextBV[0] = m_nextBV[1];
          m_nextBV[1] = m_nextBV[2];
        }
      }
    }
    else if(m_nextBV[2] != -1)
    {
      if(m_nextBV[3] != -1)
      {
        //compare tmp1, tmp3 and tmp4
        if(tmp3 < tmp1)
        {
          if(tmp4 < tmp3)
          {
            m_nextBV[1] = m_nextBV[2];
            m_nextBV[2] = m_nextBV[0];
            m_nextBV[0] = m_nextBV[3];
          }
          else if(tmp4 < tmp1)
          {
            int tmp = m_nextBV[0];
            m_nextBV[0] = m_nextBV[2];
            m_nextBV[1] = m_nextBV[4];
            m_nextBV[2] = tmp;
          }
          else
          {
            m_nextBV[1] = m_nextBV[0];
            m_nextBV[0] = m_nextBV[2];
            m_nextBV[2] = m_nextBV[3];
          }
        }
        else if(tmp4 < tmp3)
        {
          if(tmp4 < tmp1)
          {
            m_nextBV[1] = m_nextBV[0];
            m_nextBV[0] = m_nextBV[3];
          }
          else
          {
            m_nextBV[1] = m_nextBV[3];
          }
        }
        else
        {
          m_nextBV[1] = m_nextBV[2];
          m_nextBV[2] = m_nextBV[3];
        }
        m_nextBV[3] = -1;
      }
      else
      {
        //compare tmp1 and tmp3
        if(tmp1 <= tmp3)
        {
          m_nextBV[1] = m_nextBV[2];
        }
        else
        {
          m_nextBV[1] = m_nextBV[0];
          m_nextBV[0] = m_nextBV[2];
        }
        m_nextBV[2] = -1;
      }
    }
    else if(m_nextBV[3] != -1)
    {
      //compare tmp1 amd tmp4
      if(tmp1 <= tmp4)
      {
        m_nextBV[1] = m_nextBV[3];
      }
      else
      {
        m_nextBV[1] = m_nextBV[0];
        m_nextBV[0] = m_nextBV[3];
      }
      m_nextBV[3] = -1;
    }
  }
  else if(m_nextBV[1] != -1)
  {
    if(m_nextBV[2] != -1)
    {
      if(m_nextBV[3] != -1)
      {
        //compare tmp2, tmp3 and tmp4
        if(tmp3 < tmp2)
        {
          if(tmp4 < tmp3)
          {
            int tmp = m_nextBV[2];
            m_nextBV[0] = m_nextBV[3];
            m_nextBV[2] = m_nextBV[1];
            m_nextBV[1] = tmp;
          }
          else if(tmp4 < tmp2)
          {
            m_nextBV[0] = m_nextBV[2];
            m_nextBV[2] = m_nextBV[1];
            m_nextBV[1] = m_nextBV[3];
          }
          else
          {
            m_nextBV[0] = m_nextBV[2];
            m_nextBV[2] = m_nextBV[3];
          }
        }
        else if(tmp4 < tmp3)
        {
          if(tmp4 < tmp2)
          {
            m_nextBV[0] = m_nextBV[3];
          }
          else
          {
            m_nextBV[0] = m_nextBV[1];
            m_nextBV[1] = m_nextBV[3];
          }
        }
        else
        {
          m_nextBV[0] = m_nextBV[1];
          m_nextBV[1] = m_nextBV[2];
          m_nextBV[2] = m_nextBV[3];
        }
        m_nextBV[3] = -1;
      }
      else
      {
        //compare tmp2 and tmp3
        if(tmp2 < tmp3)
        {
          m_nextBV[0] = m_nextBV[1];
          m_nextBV[1] = m_nextBV[2];
        }
        else
        {
          m_nextBV[0] = m_nextBV[2];
        }
        m_nextBV[2] = -1;
      }
    }
    else if(m_nextBV[3] != -1)
    {
      //compare tmp2 and tmp4
      if(tmp2 < tmp4)
      {
        m_nextBV[0] = m_nextBV[1];
        m_nextBV[1] = m_nextBV[3];
      }
      else
      {
        m_nextBV[0] = m_nextBV[3];
      }
      m_nextBV[3] = -1;
    }
    else
    {
      //only tmp2
      m_nextBV[0] = m_nextBV[1];
      m_nextBV[1] = -1;
    }
  }
  else if(m_nextBV[2] != -1)
  {
    if(m_nextBV[3] != -1)
    {
      //compare tmp3 and tmp4
      if(tmp3 < tmp4)
      {
        m_nextBV[0] = m_nextBV[2];
        m_nextBV[1] = m_nextBV[3];
      }
      else
      {
        m_nextBV[0] = m_nextBV[3];
        m_nextBV[1] = m_nextBV[2];
      }
      m_nextBV[2] = m_nextBV[3] = -1;
    }
    else
    {
      //only tmp3
      m_nextBV[0] = m_nextBV[2];
      m_nextBV[2] = -1;
    }
  }
  else if(m_nextBV[3] != -1)
  {
    //only tmp4
    m_nextBV[0] = m_nextBV[3];
    m_nextBV[3] = -1;
  }

  return res;
}


bool STP_Torus::isHereFarthestNeighbourPrime(const Vector3& v)
{
  Scalar tmp1, tmp2, tmp3, tmp4;

  //std::cout << "test is here torus" << std::endl;

  tmp1 = m_VVR0.isInsidePrime(v);
  tmp2 = m_VVR1.isInsidePrime(v);
  tmp3 = m_VVR2.isInsidePrime(v);
  tmp4 = m_VVR3.isInsidePrime(v);

  if ((tmp1<0)&&(tmp2<0)&&(tmp3<0)&&(tmp4<0))
    return true;
  else if (tmp1>tmp2)
  {
    if (tmp1>tmp3)
    {
      if (tmp1>tmp4)
      {
        m_nextBVPrime = m_VVR0.m_outerSTP;
      }
      else //(tmp1<=tmp4)
      {
        m_nextBVPrime = m_VVR3.m_outerSTP;
      }

    }
    else //(tmp1<=tmp3)
    {
      if (tmp3>tmp4)
      {
        m_nextBVPrime = m_VVR2.m_outerSTP;
      }
      else //(tmp3<=tmp4)
      {
        m_nextBVPrime = m_VVR3.m_outerSTP;
      }
    }
  }
  else //(tmp1<=tmp2)
  {
    if (tmp2>tmp3)
    {
      if (tmp2>tmp4)
      {
        m_nextBVPrime = m_VVR1.m_outerSTP;
      }
      else //(tmp2<=tmp4)
      {
        m_nextBVPrime = m_VVR3.m_outerSTP;
      }

    }
    else //(tmp2c=tmp3)
    {
      if (tmp3>tmp4)
      {
        m_nextBVPrime = m_VVR2.m_outerSTP;
      }
      else //(tmp3<=tmp4)
      {
        m_nextBVPrime = m_VVR3.m_outerSTP;
      }
    }
  }
  return false;
}


bool STP_Torus::isHereFirstNeighbour(const Vector3& v)
{
  if(m_VVR2.isInsidePrime(v)>0)//begin with big spheres
  {
    m_nextBVPrime = m_VVR2.m_outerSTP;
    return false;
  }
  if(m_VVR3.isInsidePrime(v)>0)
  {
    m_nextBVPrime= m_VVR3.m_outerSTP;
    return false;
  }

  if(m_VVR0.isInsidePrime(v)>0)//small spheres
  {
    m_nextBVPrime = m_VVR0.m_outerSTP;
    return false;
  }
  if(m_VVR1.isInsidePrime(v)>0)
  {
    m_nextBVPrime = m_VVR1.m_outerSTP;
    return false;
  }
  return true;
}


bool STP_Torus::isHereFirstNeighbourPrime(const Vector3& v,int idp)
{
  if((m_VVR2.m_outerSTP!=idp)&&(m_VVR2.isInsidePlane(v)>0))//begin with big spheres limits
  {
    m_nextBVPrime = m_VVR2.m_outerSTP;
    return false;
  }
  if((m_VVR3.m_outerSTP!=idp)&&(m_VVR3.isInsidePlane(v)>0))
  {
    m_nextBVPrime = m_VVR3.m_outerSTP;
    return false;
  }

  if((m_VVR0.m_outerSTP!=idp)&&(m_VVR0.isInsidePrime(v)>0))//small spheres
  {
    m_nextBVPrime = m_VVR0.m_outerSTP;
    return false;
  }
  if((m_VVR1.m_outerSTP!=idp)&&(m_VVR1.isInsidePrime(v)>0))
  {
    m_nextBVPrime = m_VVR1.m_outerSTP;
    return false;
  }

  return true;
}


bool STP_Torus::isHereHybrid(const Vector3& v,int idp)
{
  if((m_VVR2.m_outerSTP!=idp)&&(m_VVR2.isInsidePlane(v)>0))//begin with big spheres limits
  {
    m_nextBVPrime = m_VVR2.m_outerSTP;
    return false;
  }
  if((m_VVR3.m_outerSTP!=idp)&&(m_VVR3.isInsidePlane(v)>0))
  {
    m_nextBVPrime = m_VVR3.m_outerSTP;
    return false;
  }

  if((m_VVR0.m_outerSTP!=idp)&&(m_VVR0.isInsidePrime(v)>0))//small spheres
  {
    m_nextBVPrime = m_VVR0.m_outerSTP;
    return false;
  }
  if((m_VVR1.m_outerSTP!=idp)&&(m_VVR1.isInsidePrime(v)>0))
  {
    m_nextBVPrime = m_VVR1.m_outerSTP;
    return false;
  }

  return true;
}


int STP_Torus::getNextBV(unsigned int id) const
{
  if(id < 4)
    return m_nextBV[id];
  else
    return -1;
}


Scalar STP_Torus::supportH(const Vector3& v) const
{
  //TODO : ???
  //return Scalar(1.0);

  // A.E // changed to usual definition
  return v*support(v);
}

Point3 STP_Torus::support(const Vector3& v) const
{
  Vector3 w;

//should never happen
  /*	if(v*m_circle.m_normal >= (sqrt((1 - (m_circle.m_radius * m_circle.m_radius)/(m_sphereRadius * m_sphereRadius)))))
  	{
  		Point3 p(m_circle.m_normal);
  		p *= sqrt(m_sphereRadius * m_sphereRadius - m_circle.m_radius * m_circle.m_radius);
  		p += m_circle.m_center;
  		return p;
  	}

  	if(v*m_circle.m_normal <= -(sqrt((1 - (m_circle.m_radius * m_circle.m_radius)/(m_sphereRadius * m_sphereRadius)))))
  	{
  		Point3 p(-m_circle.m_normal);
  		p *= sqrt(m_sphereRadius * m_sphereRadius - m_circle.m_radius * m_circle.m_radius);
  		p += m_circle.m_center;
  		return p;
  	}*/

  w[0]= -v[0] + v*m_circle.m_normal * m_circle.m_normal[0];
  w[1]= -v[1] + v*m_circle.m_normal * m_circle.m_normal[1];
  w[2]= -v[2] + v*m_circle.m_normal * m_circle.m_normal[2];

  Scalar s = w.norm();

  s = m_circle.m_radius / s;

  Point3 tmp(m_circle.m_center );
  tmp+= w * s;
  tmp+= v * m_sphereRadius;
  return tmp;
}



STP_Feature* STP_Torus::clone() const
{
  return new STP_Torus(*this);
}
