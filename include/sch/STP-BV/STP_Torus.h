#ifndef _STP_TORUS
#define _STP_TORUS

#pragma once
#include <sch/sch_api.h>
#include <sch/STP-BV/STP_Feature.h>

#ifdef WITH_BOOST_1_36
#include <sch/boost/archive/detail/oserializer.hpp>
#endif
#include <boost/serialization/base_object.hpp>

namespace sch
{
  /*! \struct s_STP_Circle
  *  \brief
  *  \author Cochet-Grasset Amelie
  *  \date    july 2007
  *
  *
  */
  typedef struct s_STP_Circle
  {
    Vector3 m_normal;
    Point3 m_center;
    Scalar m_radius;

    bool operator==(const s_STP_Circle & c) const
    {
      return
        m_normal == c.m_normal &&
        m_center == c.m_center &&
        m_radius == c.m_radius;
    }

    template<class Archive>
    void serialize(Archive & ar, const unsigned int /*version*/)
    {
      ar & m_normal & m_center & m_radius;
    }

    s_STP_Circle(const Vector3& normal, const Point3& center, Scalar radius);
    s_STP_Circle() {}
  } STP_Circle;

  /*!  \class STP_Torus
  *  \brief
  *  \author Cochet-Grasset Amelie
  *  \date    july 2007
  *
  *
  */

  class STP_Torus :
    public STP_Feature
  {
  public:
    SCH_API STP_Torus();
    SCH_API STP_Torus(const Vector3& cNormal, const Point3& cCenter, Scalar cRadius, Scalar sRadius);
    SCH_API STP_Torus(const STP_Torus& t);
    SCH_API ~STP_Torus();

    SCH_API void setVVR(const STP_VVR* vvr);

    SCH_API virtual void print() const;

    SCH_API virtual bool isHere(const Vector3& v) const;
    SCH_API virtual bool isHereFarthestNeighbour(const Vector3& v);
    SCH_API virtual bool isHereFarthestNeighbourPrime(const Vector3& v);
    SCH_API virtual bool isHereFirstNeighbour(const Vector3& v);
    SCH_API virtual bool isHereFirstNeighbourPrime(const Vector3& v,int idp);
    SCH_API virtual bool isHereHybrid(const Vector3& v,int idp) ;
    SCH_API virtual int getNextBV(unsigned int id) const;
    SCH_API virtual int getNextBVPrime() const
    {
      return m_nextBVPrime;
    }
    SCH_API virtual Scalar supportH(const Vector3& v) const;
    SCH_API virtual Point3 support(const Vector3& v) const;

    SCH_API virtual STP_Feature* clone() const;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int /*version*/)
    {
      ar & boost::serialization::base_object<STP_Feature>(*this);
      ar & m_circle & m_sphereRadius & m_VVR0 & m_VVR1 & m_VVR2 & m_VVR3 & m_nextBV;
      m_nextBV[0] = m_VVR0.m_outerSTP;
      m_nextBV[1] = m_VVR1.m_outerSTP;
      m_nextBV[2] = m_VVR2.m_outerSTP;
      m_nextBV[3] = m_VVR3.m_outerSTP;
    }


  protected:
    STP_Circle m_circle;
    Scalar m_sphereRadius;
    STP_VVR m_VVR0,m_VVR1,m_VVR2,m_VVR3;
    int m_nextBV[4];
  };

}

#endif
