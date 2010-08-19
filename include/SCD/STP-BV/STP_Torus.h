#ifndef _STP_TORUS
#define _STP_TORUS

#pragma once
#include <SCD/STP-BV/STP_Feature.h>

namespace SCD
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

		s_STP_Circle(const Vector3& normal, const Point3& center, Scalar radius);
		s_STP_Circle(){}
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
		STP_Torus(const Vector3& cNormal, const Point3& cCenter, Scalar cRadius, Scalar sRadius);
		STP_Torus(const STP_Torus& t);
		~STP_Torus();

		void setVVR(const STP_VVR* vvr);

		virtual void print() const;
		void GLdisplayBVVVRaxes() const;
		virtual void GLdisplayVVR() const;

		virtual bool isHere(const Vector3& v) const;
		virtual bool isHereFarthestNeighbour(const Vector3& v);
		virtual bool isHereFarthestNeighbourPrime(const Vector3& v);
		virtual bool isHereFirstNeighbour(const Vector3& v);
		virtual bool isHereFirstNeighbourPrime(const Vector3& v,int idp);
		virtual bool isHereHybrid(const Vector3& v,int idp) ;
		virtual int getNextBV(unsigned int id) const;
		virtual int getNextBVPrime() const
		{
			return m_nextBVPrime;	
		}
		virtual Scalar supportH(const Vector3& v) const;
		virtual Point3 support(const Vector3& v) const;

		virtual STP_Feature* clone() const;


	protected:
		STP_Circle m_circle;
		Scalar m_sphereRadius;
		STP_VVR m_VVR0,m_VVR1,m_VVR2,m_VVR3;
		int m_nextBV[4];
	};

}
#endif
