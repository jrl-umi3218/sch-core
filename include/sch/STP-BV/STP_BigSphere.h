#ifndef _STP_BIGSPHERE
#define _STP_BIGSPHERE

#pragma once
#include <sch/sch_api.h>
#include <sch/STP-BV/STP_Feature.h>

#ifdef WITH_BOOST_1_36
#include <sch/boost/archive/detail/oserializer.hpp>
#endif
#include <boost/serialization/base_object.hpp>


namespace sch
{
  class STP_BigSphere :
    public STP_Feature
  {

  public:
    SCH_API STP_BigSphere();
    SCH_API STP_BigSphere(Scalar radius, Point3 center);
    SCH_API STP_BigSphere(const STP_BigSphere& s);
    SCH_API ~STP_BigSphere();

    SCH_API const Point3& getCenter() const;
    //void setVVR(const Vector3* vvr);
    SCH_API void setVVR(const STP_VVR* vvr);

    SCH_API virtual void print() const;

    SCH_API virtual bool isHere(const Vector3& v) const;
    SCH_API virtual bool isHereFarthestNeighbour(const Vector3& v);
    SCH_API virtual bool isHereFarthestNeighbourPrime(const Vector3& v);
    SCH_API virtual bool isHereFirstNeighbour(const Vector3& v);
    SCH_API virtual bool isHereFirstNeighbourPrime(const Vector3& v,int idp);
    SCH_API virtual bool isHereHybrid(const Vector3& v,int idp);

    SCH_API virtual int getNextBV(unsigned int id) const;

    SCH_API virtual Scalar supportH(const Vector3& v) const;
    SCH_API virtual Point3 support(const Vector3& v) const;

    SCH_API virtual bool ray_cast(const Point3& source, const Point3& target,
                                  Scalar& param, Vector3& normal) const;

    SCH_API virtual STP_Feature* clone() const;

    SCH_API virtual int getNextBVPrime() const
    {
      return m_nextBVPrime;
    }

    template<class Archive>
    void serialize(Archive & ar, const unsigned int /*version*/)
    {
      ar & boost::serialization::base_object<STP_Feature>(*this);
      ar & m_radius & m_center & m_VVR0 & m_VVR1 & m_VVR2;
      m_nextBV[0] = m_VVR0.m_outerSTP;
      m_nextBV[1] = m_VVR1.m_outerSTP;
      m_nextBV[2] = m_VVR2.m_outerSTP;
    }

  protected:
    Scalar m_radius;
    Point3 m_center;
    STP_VVR m_VVR0,m_VVR1,m_VVR2;
    int m_nextBV[3];
  };
}

#endif
