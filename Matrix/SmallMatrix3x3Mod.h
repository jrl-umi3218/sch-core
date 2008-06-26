#pragma once

#ifndef _MATRIX3D_MAL_MOD_
#define _MATRIX3D_MAL_MOD_

#include <cassert>
#include "SmallMatrix3x3Default.h"

#include "QuaternionM.h"

namespace MAL_Default
{
	template<typename T>
	class Matrix3x3Mod :
		public Matrix3x3<T>
	{
	public:

		/*! Defaut constructor. */
		explicit Matrix3x3Mod<T>() 
		{ 
			m[0]=0.0; m[1] = 0.0; m[2]=0.0;
			m[3]=0.0; m[4] = 0.0; m[5]=0.0;
			m[6]=0.0; m[7] = 0.0; m[8]=0.0;
		}

		/*! Constructor from a scalar */
		explicit Matrix3x3Mod<T> (const T& x)
		{
			m[0]=x; m[1] = x; m[2]=x;
			m[3]=x; m[4] = x; m[5]=x;
			m[6]=x; m[7] = x; m[8]=x;
		}

		/*! Constructor from a pointer */
		explicit Matrix3x3Mod<T> (const T* const  x)
		{
			m[0]=x[0]; m[1] = x[1]; m[2]=x[2];
			m[3]=x[3]; m[4] = x[4]; m[5]=x[5];
			m[6]=x[6]; m[7] = x[7]; m[8]=x[8];
		}

		/*! Constructor from 9 scalar */
		explicit Matrix3x3Mod<T> (
			const T x0, const T x1, const T x2, 
			const T x3, const T x4, const T x5, 
			const T x6, const T x7, const T x8
			)
		{
			m[0]=x0; m[1] = x1; m[2]=x2;
			m[3]=x3; m[4] = x4; m[5]=x5;
			m[6]=x6; m[7] = x7; m[8]=x8;
		}

		/*! constructor */
		Matrix3x3Mod<T> (const struct Matrix3x3<T> &v)
		{
			m[0] = v.m[0]; m[1] = v.m[1]; m[2] = v.m[2];
			m[3] = v.m[3]; m[4] = v.m[4]; m[5] = v.m[5];
			m[6] = v.m[6]; m[7] = v.m[7]; m[8] = v.m[8];
		}

		/*! constructor taking three columns vector*/

		explicit Matrix3x3Mod<T> (const Vector3D<T> V1,const Vector3D<T> V2,const Vector3D<T> V3)
		{
			m[0] = V1[0]; m[1] =V2[0]; m[2] = V3[0];
			m[3] = V1[1]; m[4] =V2[1]; m[5] = V3[1];
			m[6] = V1[2]; m[7] =V2[2]; m[8] = V3[2];

		}

		/*! quatrenion*/
		explicit Matrix3x3Mod<T> (const QuaternionM<T>& q)
		{
			T q0=q[0],q1=q[1],q2=q[2],q3=q[3];
			T d = q0*q0+q1*q1+q2*q2+q3*q3;
			assert (d != T(0.0));
			T s = T(2.0) / d;
			T xs = q0 * s,   ys = q1 * s,   zs = q2 * s;
			T wx = q3 * xs,  wy = q3 * ys,  wz = q3 * zs;
			T xx = q0 * xs,  xy = q0 * ys,  xz = q0 * zs;
			T yy = q1 * ys,  yz = q1 * zs,  zz = q2 * zs;
			m[0]=T(1.0) - (yy + zz), 
				m[1]=xy - wz, 
				m[2]=xz + wy,
				m[3]=xy + wz, 
				m[4]=T(1.0) - (xx + zz), 
				m[5]=yz - wx,
				m[6]=xz - wy, 
				m[7]=yz + wx, 
				m[8]=T(1.0) - (xx + yy);
		}


		
		/*! quatrenion*/
		explicit Matrix3x3Mod<T> (const T &q0,const T &q1,const T &q2,const T &q3)
		{
			T d = q0*q0+q1*q1+q2*q2+q3*q3;
			assert(d != T(0.0));
			T s = T(2.0) / d;
			T xs = q0 * s,   ys = q1 * s,   zs = q2 * s;
			T wx = q3 * xs,  wy = q3 * ys,  wz = q3 * zs;
			T xx = q0 * xs,  xy = q0 * ys,  xz = q0 * zs;
			T yy = q1 * ys,  yz = q1 * zs,  zz = q2 * zs;
			m[0]=T(1.0) - (yy + zz); 
			m[1]=xy - wz; 
			m[2]=xz + wy;
			m[3]=xy + wz; 
			m[4]=T(1.0) - (xx + zz); 
			m[5]=yz - wx;
			m[6]=xz - wy; 
			m[7]=yz + wx; 
			m[8]=T(1.0) - (xx + yy);
		}


		/*! quatrenion*/
		explicit Matrix3x3Mod<T> (const T &angle,const Vector3D<T>  &axis)
		{
			T sin_a = sin(angle / 2), 
			  cos_a = cos(angle / 2);

			T q0 = axis[0] * sin_a;
			T q1 = axis[1] * sin_a;
			T q2 = axis[2] * sin_a;
			T q3 = cos_a;
			
			T d = q0*q0+q1*q1+q2*q2+q3*q3;

			assert(d != T(0.0));
			T s = T(2.0) / d;
			T xs = q0 * s,   ys = q1 * s,   zs = q2 * s;
			T wx = q3 * xs,  wy = q3 * ys,  wz = q3 * zs;
			T xx = q0 * xs,  xy = q0 * ys,  xz = q0 * zs;
			T yy = q1 * ys,  yz = q1 * zs,  zz = q2 * zs;
			m[0]=T(1.0) - (yy + zz); 
			m[1]=xy - wz; 
			m[2]=xz + wy;
			m[3]=xy + wz; 
			m[4]=T(1.0) - (xx + zz); 
			m[5]=yz - wx;
			m[6]=xz - wy; 
			m[7]=yz + wx; 
			m[8]=T(1.0) - (xx + yy);
		}

		
		/*!Euler*/
		explicit Matrix3x3Mod<T> (const T &yaw,const T &pitch,const T &roll)
		{
			T cy(cos(double(yaw))); 
			T sy(sin(double(yaw))); 
			T cp(cos(double(pitch))); 
			T sp(sin(double(pitch))); 
			T cr(cos(double(roll)));
			T sr(sin(double(roll)));
			T cc = cy * cr; 
			T cs = cy * sr; 
			T sc = sy * cr; 
			T ss = sy * sr;
			
			m[0]= cc + sp * ss;
			m[1]= cs - sp * sc;
			m[2]= -sy * cp;
			m[3]= -cp * sr;
			m[4]= cp * cr;
			m[5]=  -sp;
			m[6]= sc - sp * cs;
			m[7]= ss + sp * cc;
			m[8]= cy * cp;
		}

						/*! set from 9 scalar */
		void Set (
			const T x0, const T x1, const T x2, 
			const T x3, const T x4, const T x5, 
			const T x6, const T x7, const T x8
			)
		{
			m[0]=x0; m[1] = x1; m[2]=x2;
			m[3]=x3; m[4] = x4; m[5]=x5;
			m[6]=x6; m[7] = x7; m[8]=x8;
		}


		/*Set from a vector and an array*/
		void Set(const T &angle,const Vector3D<T>  &axis)
		{
			T sin_a = sin(angle / 2), 
			  cos_a = cos(angle / 2);

			T q0 = axis[0] * sin_a;
			T q1 = axis[1] * sin_a;
			T q2 = axis[2] * sin_a;
			T q3 = cos_a;
			
			T d = q0*q0+q1*q1+q2*q2+q3*q3;

			assert(d != T(0.0));
			T s = T(2.0) / d;
			T xs = q0 * s,   ys = q1 * s,   zs = q2 * s;
			T wx = q3 * xs,  wy = q3 * ys,  wz = q3 * zs;
			T xx = q0 * xs,  xy = q0 * ys,  xz = q0 * zs;
			T yy = q1 * ys,  yz = q1 * zs,  zz = q2 * zs;
			m[0]=T(1.0) - (yy + zz); 
			m[1]=xy - wz; 
			m[2]=xz + wy;
			m[3]=xy + wz; 
			m[4]=T(1.0) - (xx + zz); 
			m[5]=yz - wx;
			m[6]=xz - wy; 
			m[7]=yz + wx; 
			m[8]=T(1.0) - (xx + yy);
		}


		
		/*! Set from a pointer */
		void Set(const T* const x)
		{
			m[0]=x[0]; m[1] = x[1]; m[2]=x[2];
			m[3]=x[3]; m[4] = x[4]; m[5]=x[5];
			m[6]=x[6]; m[7] = x[7]; m[8]=x[8];
		}


		/*!quatrenion*/
		void Set (const QuaternionM<T>& q)
		{
			T q0=q[0],q1=q[0],q2=q[0],q3=q[0];
			T d = q0*q0+q1*q1+q2*q2+q3*q3;
			assert(d != T(0.0));
			T s = T(2.0) / d;
			T xs = q0 * s,   ys = q1 * s,   zs = q2 * s;
			T wx = q3 * xs,  wy = q3 * ys,  wz = q3 * zs;
			T xx = q0 * xs,  xy = q0 * ys,  xz = q0 * zs;
			T yy = q1 * ys,  yz = q1 * zs,  zz = q2 * zs;
			m[0]=T(1.0) - (yy + zz), 
			m[1]=xy - wz, 
			m[2]=xz + wy,
			m[3]=xy + wz, 
			m[4]=T(1.0) - (xx + zz), 
			m[5]=yz - wx,
			m[6]=xz - wy, 
			m[7]=yz + wx, 
			m[8]=T(1.0) - (xx + yy);
		}

		/*! quatrenion*/
		void Set (const T &q0,const T &q1,const T &q2,const T &q3)
		{
			T d = q0*q0+q1*q1+q2*q2+q3*q3;
			assert(d != T(0.0));
			T s = T(2.0) / d;
			T xs = q0 * s,   ys = q1 * s,   zs = q2 * s;
			T wx = q3 * xs,  wy = q3 * ys,  wz = q3 * zs;
			T xx = q0 * xs,  xy = q0 * ys,  xz = q0 * zs;
			T yy = q1 * ys,  yz = q1 * zs,  zz = q2 * zs;
			m[0]=T(1.0) - (yy + zz); 
			m[1]=xy - wz; 
			m[2]=xz + wy;
			m[3]=xy + wz; 
			m[4]=T(1.0) - (xx + zz); 
			m[5]=yz - wx;
			m[6]=xz - wy; 
			m[7]=yz + wx; 
			m[8]=T(1.0) - (xx + yy);
		}

		/*!Euler*/
		void Set(const T &yaw,const T &pitch,const T &roll)
		{
			T cy(cos(double(yaw))); 
			T sy(sin(double(yaw))); 
			T cp(cos(double(pitch))); 
			T sp(sin(double(pitch))); 
			T cr(cos(double(roll)));
			T sr(sin(double(roll)));
			T cc = cy * cr; 
			T cs = cy * sr; 
			T sc = sy * cr; 
			T ss = sy * sr;
			
			m[0]= cc + sp * ss;
			m[1]= cs - sp * sc;
			m[2]= -sy * cp;
			m[3]= -cp * sr;
			m[4]= cp * cr;
			m[5]=  -sp;
			m[6]= sc - sp * cs;
			m[7]= ss + sp * cc;
			m[8]= cy * cp;
		}

		/*! Transposition */
		Matrix3x3<T>& TransposeIt()
		{
			T t;
			t=m[1];
			m[1]=m[3];
			m[3]=t;

			t=m[2];
			m[2]=m[6];
			m[6]=t;
			
			t=m[5];
			m[5]=m[7];
			m[7]=t;

			return *this;
		}

		/*! Transposition */
		Matrix3x3<T> Transpose() const
		{
			return Matrix3x3<T> (m[0],m[3],m[6],
								  m[1],m[4],m[7],
								  m[2],m[5],m[8]);
		}

		Vector3Mod<T> operator *(const Vector3D<T>& v) const
		{
			Vector3Mod<T> vr(m[0]*v[0]+m[1]*v[1]+m[2]*v[2],
									m[3]*v[0]+m[4]*v[1]+m[5]*v[2],
									m[6]*v[0]+m[7]*v[1]+m[8]*v[2]);
			return vr;
		}




	};
};

#endif