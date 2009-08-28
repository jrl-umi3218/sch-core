#pragma once

#ifndef _VECTOR3D_MAL_MOD_
#define _VECTOR3D_MAL_MOD_

#include <iostream>
#include <cmath>
#include <SCD/Matrix/SmallVector3Default.h>
#include <SCD/Matrix/SmallMatrix3x3Default.h>

#include <boost/serialization/base_object.hpp>

namespace MAL_Default
{
		
	/*! Template to handle 3 dimensional vector */
	template <typename T>
	class Vector3Mod :
		public Vector3D<T>
	{
	public:

		explicit Vector3Mod<T>()
		{}

		explicit Vector3Mod<T>(const T& x, const T& y, const T& z):Vector3D<T>(x,y,z)
		{}

	
		explicit Vector3Mod<T>(const T* const p):Vector3D<T>(p[0],p[1],p[2])
		{}

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
      ar & boost::serialization::base_object< Vector3D<T> >(*this);
    }

		void Set(const T& x, const T& y, const T& z)
		{
			this->m_x=x;
			this->m_y=y;
			this->m_z=z;
		}

	
		void Set(const T* const p)
		{
			this->m_x=p[0];
			this->m_y=p[1];
			this->m_z=p[2];
		}


		inline const Vector3Mod<T> operator= (const struct Vector3D<T> &v)
		{
			this->m_x = v.m_x;
			this->m_y = v.m_y;
			this->m_z = v.m_z;
			return *this;
		}

		/*! Unary operator - */
		inline const Vector3Mod<T> operator-() const
		{
			return Vector3Mod<T>(-(this->m_x), -(this->m_y), -(this->m_z));
		}


		inline const Vector3Mod<T> operator+ (const struct Vector3D<T> &v) const
		{
			Vector3Mod<T> vr;
			vr.m_x = this->m_x + v.m_x;
			vr.m_y = this->m_y + v.m_y;
			vr.m_z = this->m_z + v.m_z;
			return vr;
		}



		/*! Binary operator - */
		inline const Vector3Mod<T> operator- (const struct Vector3D<T> &v) const
		{
			Vector3Mod<T> vr;
			vr.m_x = this->m_x - v.m_x;
			vr.m_y = this->m_y - v.m_y;
			vr.m_z = this->m_z - v.m_z;
			return vr;
		}

		/*! multiplication */
		inline Vector3Mod<T> operator* (const T& t) const
		{
			Vector3Mod<T> vr;
			vr.m_x = this->m_x * t;
			vr.m_y = this->m_y * t;
			vr.m_z = this->m_z * t;
			return vr;
		}

		/*! Binary operator * : dot product */
		inline T operator* (const Vector3D<T>& v) const
		{
			return this->m_x * v.m_x + this->m_y * v.m_y + this->m_z * v.m_z ;
		}

		/*! Binary operator *= */
		inline void operator*= (const T &t) 
		{
			this->m_x = this->m_x*t;
			this->m_y = this->m_y*t;
			this->m_z = this->m_z*t;
		}


		/*! multiplication as a row vector by a left-hand matrix  */
		inline Vector3Mod<T> operator*(const Matrix3x3<T>& m)const 
		{

			Vector3Mod<T> vr(this->m_x*m[0]+this->m_y*m[3]+this->m_z*m[6],
						     this->m_x*m[1]+this->m_y*m[4]+this->m_z*m[7],
						     this->m_x*m[2]+this->m_y*m[5]+this->m_z*m[8]);
			return vr;
			
		}

		inline void operator*=(const Matrix3x3<T> m) 
		{

			T x=this->m_x*m[0]+this->m_y*m[3]+this->m_z*m[6],
			  y=this->m_x*m[1]+this->m_y*m[4]+this->m_z*m[7];
			 this->m_z=this->m_x*m[2]+this->m_y*m[5]+this->m_z*m[8];

			this->m_x = x;
			this->m_y = y;
			
		}




		


		inline Vector3Mod<T> operator/ (const T &t) const
		{
			Vector3Mod<T> vr;
			vr.m_x = this->m_x/t;
			vr.m_y = this->m_y/t;
			vr.m_z = this->m_z/t;
			return vr;
		}

		inline Vector3Mod<T> operator ^ (const Vector3D<T>& v2) const
		{
			Vector3Mod<T> vr;
			vr.m_x = this->m_y*v2.m_z - v2.m_y*this->m_z;
			vr.m_y = this->m_z*v2.m_x - v2.m_z*this->m_x;
			vr.m_z = this->m_x*v2.m_y - v2.m_x*this->m_y;
			return vr;
		}

		
		~Vector3Mod(void)
		{
		}

		inline friend std::ostream& operator<<(std::ostream &os,const Vector3Mod<T>  &v) 
		{
			os << v.m_x << " " << v.m_y << " " << v.m_z << " ";
			return os;
		}

	
	};
};

#include <SCD/Matrix/SmallMatrix3x3Mod.h>
#endif
