#include <sch/STP-BV/STP_SmallSphere.h>

#include <math.h>
#include <iostream>

#include <map>


using namespace sch;

STP_SmallSphere::STP_SmallSphere() : m_neighbors(NULL), m_endneighbors(NULL)
{
}

STP_SmallSphere::STP_SmallSphere(Scalar radius, Point3 center):
  m_radius(radius), m_center(center),m_neighbors(NULL),m_endneighbors(NULL)
{
}

STP_SmallSphere::STP_SmallSphere(const STP_SmallSphere& s):
  STP_Feature(s), m_radius(s.m_radius), m_center(s.m_center), m_VVR(s.m_VVR),m_neighbors(NULL),m_endneighbors(NULL)
{
  m_nextBV.resize(m_VVR.size());
  updateVector();
}

STP_SmallSphere::~STP_SmallSphere()
{
  if (m_neighbors!=NULL)
  {
    delete[] m_neighbors;
  }
}


STP_SmallSphere& STP_SmallSphere::operator =(const STP_SmallSphere &s)
{
  if (&s==this)
  {
    return *this;
  }
  STP_Feature::operator=(s);
  m_radius=s.m_radius;
  m_center=s.m_center;
  m_VVR=s.m_VVR;
  m_nextBV.resize(m_VVR.size());
  updateVector();
  return *this;
}

const Point3& STP_SmallSphere::getCenter() const
{
  return m_center;
}

const Scalar& STP_SmallSphere::getRadius() const
{
  return m_radius;
}


void STP_SmallSphere::setVVR(const std::vector<STP_VVR>& vvr)
{
  for(std::vector<STP_VVR>::const_iterator it1 = vvr.begin() ; it1 != vvr.end() ; ++it1)
  {
    m_VVR.push_back(*it1);
  }

  m_nextBV.resize(m_VVR.size());

  updateVector();
}

void STP_SmallSphere::print() const
{
  std::cout << "type : small sphere" << std::endl;
  std::cout << "center : " << m_center[0] << ", " << m_center[1] << ", " << m_center[2] << std::endl;
  std::cout << "radius : " << m_radius << std::endl << std::endl;
}

bool STP_SmallSphere::isHere(const Vector3& v) const
{
  std::vector<STP_VVR>::const_iterator currentVVR = m_VVR.begin();
  bool in = false;

  while( currentVVR != m_VVR.end() && (in = currentVVR->isInside(v)))
  {
    ++currentVVR;
  }

  return in;
}


bool STP_SmallSphere::isHereFarthestNeighbour(const Vector3& v)
{
  bool res = true;
  std::vector<STP_VVR>::const_iterator currentVVR = m_VVR.begin();
  std::map<Scalar, int> values;

  //std::cout << "test is here small sphere" << std::endl;

  while( currentVVR != m_VVR.end() )
  {
    if(!(currentVVR->isInside(v)))
    {
      res = false;
      values.insert(std::pair<Scalar, int>(currentVVR->getDistance(v), currentVVR->m_outerSTP));
      //	std::cout << "outer STP : " << currentVVR->m_outerSTP << std::endl;
      //	std::cout << "distance : " << currentVVR->getDistance(v) << std::endl;
    }
    ++currentVVR;
  }

  std::map<Scalar, int>::iterator it;
  int i = 0;
  for(it = values.begin() ; it != values.end() ; ++it)
  {
    m_nextBV[i] = it->second;
    ++i;
  }

  return res;
}


bool STP_SmallSphere::isHereFarthestNeighbourPrime(const Vector3& v)
{
  std::vector<STP_VVR>::const_iterator currentVVR = m_VVR.begin();

  Scalar d=0;
  Scalar dp;

  //std::cout << "test is here small sphere" << std::endl;

  while( currentVVR != m_VVR.end() )
  {

    dp=currentVVR->isInsidePrime(v);
    if (d>dp)
    {
      this->m_nextBVPrime=currentVVR->m_outerSTP;
      d=dp;

    }
    ++currentVVR;
  }

  if (d==0)
    return true;
  else
    return false;
}

void STP_SmallSphere::updateVector()
{
  if (m_neighbors!=NULL)
  {
    delete m_neighbors;
  }
  m_neighbors=new STP_VVR[m_VVR.size()];
  m_endneighbors=&(m_neighbors[m_VVR.size()]);

  for (size_t i=0; i<m_VVR.size(); i++)
  {
    m_neighbors[i]=m_VVR[i];
  }
}


bool STP_SmallSphere::isHereFirstNeighbour(const Vector3& v)
{
  std::vector<STP_VVR>::const_iterator currentVVR = m_VVR.begin();

  while(currentVVR->isInsidePrime(v)>0)
  {

    ++currentVVR;
    if (currentVVR == m_VVR.end())
    {
      return true;
    }

  }

  /*while ( (currentVVR != m_VVR.end()) && (currentVVR->isInside(v)) )
  {
  	++currentVVR;
  }
  if (currentVVR == m_VVR.end())
  {
  	return true;
  }*/

  m_nextBVPrime = currentVVR->m_outerSTP ;

  return false;
}




bool STP_SmallSphere::isHereFirstNeighbourPrime(const Vector3& v,int /*idp*/)
{
  STP_VVR * currentVVR = m_neighbors;

  while((currentVVR->isInsidePrime(v)>=0))
  {
    ++currentVVR;
    if (currentVVR == m_endneighbors)
    {
      return true;
    }
  }

  m_nextBVPrime = currentVVR->m_outerSTP ;

  return false;
}


bool STP_SmallSphere::isHereHybrid(const Vector3& v,int /*idp*/)
{
  STP_VVR * currentVVR = m_neighbors;

  Scalar d=0;
  Scalar dp;


  //std::cout << "test is here small sphere" << std::endl;

  while( currentVVR !=  m_endneighbors )
  {
    dp=currentVVR->isInsidePrime(v);
    if (d>dp)
    {
      m_nextBVPrime=currentVVR->m_outerSTP;
      d=dp;
    }
    ++currentVVR;
  }

  if (d==0)
    return true;
  else
    return false;
}


int STP_SmallSphere::getNextBV(unsigned int id) const
{
//	std::cout << "STP retourne : " << m_nextBV.at(0) << std::endl;
  if(id < m_nextBV.size())
    return m_nextBV.at(id);
  else
    return -1;
}


Scalar STP_SmallSphere::supportH(const Vector3& v) const
{
  //tenir compte du centre ??
  return m_radius * v.norm();
}

Point3 STP_SmallSphere::support(const Vector3& v) const
{
  return m_center+v*m_radius;
}

bool STP_SmallSphere::ray_cast(const Point3& source, const Point3& target,
                               Scalar& param, Vector3& normal) const
{
  Vector3 r = target - source;
  Scalar  delta = -source*r;
  Scalar  r_length2 = r.normsquared();
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


STP_Feature* STP_SmallSphere::clone() const
{
  return new STP_SmallSphere(*this);
}

