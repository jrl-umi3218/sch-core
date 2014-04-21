#ifndef _STP_SMALLSPHERE
#define _STP_SMALLSPHERE

#pragma once
#include <sch/sch_api.h>
#include <sch/STP-BV/STP_Feature.h>
#include <vector>

#ifdef WITH_BOOST_1_36
#include <sch/boost/archive/detail/oserializer.hpp>
#endif
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/split_member.hpp>



/*!  \class STP_SmallSphere
*  \brief
*  \author Cochet-Grasset Amelie
*  \date    july 2007
*
*
*/
namespace sch
{
  class STP_SmallSphere :
    public STP_Feature
  {
  public:
    sch_API STP_SmallSphere();
    sch_API STP_SmallSphere(Scalar radius, Point3 center);
    sch_API STP_SmallSphere(const STP_SmallSphere& s);

    sch_API ~STP_SmallSphere();

    sch_API STP_SmallSphere & operator =(const STP_SmallSphere &s);

    sch_API const Point3& getCenter() const;
    sch_API const Scalar& getRadius() const;
    sch_API void setVVR(const std::vector<STP_VVR>& vvr);

    sch_API virtual void print() const;

    sch_API virtual bool isHere(const Vector3& v) const;
    sch_API virtual bool isHereFarthestNeighbour(const Vector3& v);
    sch_API virtual bool isHereFarthestNeighbourPrime(const Vector3& v);
    sch_API virtual bool isHereFirstNeighbour(const Vector3& v);
    sch_API virtual bool isHereFirstNeighbourPrime(const Vector3& v,int idp);
    sch_API virtual bool isHereHybrid(const Vector3& v,int idp) ;
    sch_API virtual int getNextBV(unsigned int id) const;
    sch_API virtual Scalar supportH(const Vector3& v) const;
    sch_API virtual Point3 support(const Vector3& v) const;

    sch_API virtual bool ray_cast(const Point3& source, const Point3& target,
                                  Scalar& param, Vector3& normal) const;

    sch_API virtual STP_Feature* clone() const;

    sch_API virtual int getNextBVPrime() const
    {
      return m_nextBVPrime;
    }



    template<class Archive>
    void save(Archive & ar, unsigned int /*version*/) const
    {
      ar & boost::serialization::base_object<STP_Feature>(*this);
      ar & m_radius & m_center & m_VVR & m_nextBV & m_nextBVPrime;
    }

    template<class Archive>
    void load(Archive & ar, unsigned int /*version*/)
    {
      ar & boost::serialization::base_object<STP_Feature>(*this);
      ar & m_radius & m_center & m_VVR & m_nextBV & m_nextBVPrime;
      updateVector();
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()

  protected:
    Scalar m_radius;
    Point3 m_center;
    std::vector<STP_VVR> m_VVR;
    std::vector<int> m_nextBV;
    int m_nextBVPrime;

    STP_VVR * m_neighbors;
    STP_VVR * m_endneighbors;
    void updateVector();
  };
}

#endif
