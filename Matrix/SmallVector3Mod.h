#pragma once

#ifndef _VECTOR3D_MAL_MOD_
#define _VECTOR3D_MAL_MOD_

#include <iostream>
#include <cmath>
#include "smallvector3default.h"
#include "smallmatrix3x3Default.h"


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

		explicit Vector3Mod<T>(const T& x, const T& y, const T& z):Vector3D(x,y,z)
		{}

	
		explicit Vector3Mod<T>(const T* const p):Vector3D(p[0],p[1],p[2])
		{}

		void Set(const T& x, const T& y, const T& z)
		{
			m_x=x;
			m_y=y;
			m_z=z;
		}

	
		void Set(const T* const p)
		{
			m_x=p[0];
			m_y=p[1];
			m_z=p[2];
		}


		inline const Vector3Mod<T> operator= (const struct Vector3D<T> &v)
		{
			m_x = v.m_x;
			m_y = v.m_y;
			m_z = v.m_z;
			return *this;
		}

		/*! Unary operator - */
		inline const Vector3Mod<T> operator-() const
		{
			return Vector3Mod<T>(-m_x, -m_y, -m_z);
		}


		inline const Vector3Mod<T> operator+ (const struct Vector3D<T> &v) const
		{
			Vector3Mod<T> vr;
			vr.m_x = m_x + v.m_x;
			vr.m_y = m_y + v.m_y;
			vr.m_z = m_z + v.m_z;
			return vr;
		}



		/*! Binary operator - */
		inline const Vector3Mod<T> operator- (const struct Vector3D<T> &v) const
		{
			Vector3Mod<T> vr;
			vr.m_x = m_x - v.m_x;
			vr.m_y = m_y - v.m_y;
			vr.m_z = m_z - v.m_z;
			return vr;
		}

		/*! multiplication */
		inline Vector3Mod<T> operator* (const T& t) const
		{
			Vector3Mod<T> vr;
			vr.m_x = m_x * t;
			vr.m_y = m_y * t;
			vr.m_z = m_z * t;
			return vr;
		}

		/*! Binary operator * : dot product */
		inline T operator* (const Vector3D<T>& v) const
		{
			return m_x * v.m_x + m_y * v.m_y + m_z * v.m_z ;
		}

		/*! Binary operator *= */
		inline void operator*= (const T &t) 
		{
			m_x = m_x*t;
			m_y = m_y*t;
			m_z = m_z*t;
		}


		/*! multiplication as a row vector by a left-hand matrix  */
		inline Vector3Mod<T> operator*(const Matrix3x3<T>& m)const 
		{

			Vector3Mod<T> vr(m_x*m[0]+m_y*m[3]+m_z*m[6],
						     m_x*m[1]+m_y*m[4]+m_z*m[7],
						     m_x*m[2]+m_y*m[5]+m_z*m[8]);
			return vr;
			
		}

		inline void operator*=(const Matrix3x3<T> m) 
		{

			T x=m_x*m[0]+m_y*m[3]+m_z*m[6],
			  y=m_x*m[1]+m_y*m[4]+m_z*m[7];
			 m_z=m_x*m[2]+m_y*m[5]+m_z*m[8];

			m_x = x;
			m_y = y;
			
		}




		


		inline Vector3Mod<T> operator/ (const T &t) const
		{
			Vector3Mod<T> vr;
			vr.m_x = m_x/t;
			vr.m_y = m_y/t;
			vr.m_z = m_z/t;
			return vr;
		}

		inline Vector3Mod<T> operator ^ (const Vector3D<T>& v2) const
		{
			Vector3Mod<T> vr;
			vr.m_x = m_y*v2.m_z - v2.m_y*m_z;
			vr.m_y = m_z*v2.m_x - v2.m_z*m_x;
			vr.m_z = m_x*v2.m_y - v2.m_x*m_y;
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

#include "SmallMatrix3x3Mod.h"
#endif