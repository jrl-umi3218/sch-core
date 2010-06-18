#pragma once

#ifndef _MATRIX3D_MAL_MOD_
#define _MATRIX3D_MAL_MOD_

#include <cassert>
#include <SCD/Matrix/SmallMatrix3x3Default.h>

#include <SCD/Matrix/QuaternionM.h>

#ifdef WITH_BOOST_1_36
#include <SCD/boost/archive/detail/oserializer.hpp>
#endif
#include <boost/serialization/base_object.hpp>

namespace MAL_Default
{
	template<typename T>
	class Matrix3x3Mod :
		public Matrix3x3<T>
	{
	public:

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
      ar & boost::serialization::base_object< Matrix3x3<T> >(*this);
    }

		/*! Defaut constructor. */
		explicit Matrix3x3Mod<T>() 
		{ 
			this->m[0]=0.0; this->m[1] = 0.0; this->m[2]=0.0;
			this->m[3]=0.0; this->m[4] = 0.0; this->m[5]=0.0;
			this->m[6]=0.0; this->m[7] = 0.0; this->m[8]=0.0;
		}

		/*! Constructor from a scalar */
		explicit Matrix3x3Mod<T> (const T& x)
		{
			this->m[0]=x; this->m[1] = x; this->m[2]=x;
			this->m[3]=x; this->m[4] = x; this->m[5]=x;
			this->m[6]=x; this->m[7] = x; this->m[8]=x;
		}

		/*! Constructor from a pointer */
		explicit Matrix3x3Mod<T> (const T* const  x)
		{
			this->m[0]=x[0]; this->m[1] = x[1]; this->m[2]=x[2];
			this->m[3]=x[3]; this->m[4] = x[4]; this->m[5]=x[5];
			this->m[6]=x[6]; this->m[7] = x[7]; this->m[8]=x[8];
		}

		/*! Constructor from 9 scalar */
		explicit Matrix3x3Mod<T> (
			const T x0, const T x1, const T x2, 
			const T x3, const T x4, const T x5, 
			const T x6, const T x7, const T x8
			)
		{
			this->m[0]=x0; this->m[1] = x1; this->m[2]=x2;
			this->m[3]=x3; this->m[4] = x4; this->m[5]=x5;
			this->m[6]=x6; this->m[7] = x7; this->m[8]=x8;
		}

		/*! constructor */
		Matrix3x3Mod<T> (const struct Matrix3x3<T> &v)
		{
		 this->m[0] = v.m[0]; this->m[1] = v.m[1]; this->m[2] = v.m[2];
		 this->m[3] = v.m[3]; this->m[4] = v.m[4]; this->m[5] = v.m[5];
		 this->m[6] = v.m[6]; this->m[7] = v.m[7]; this->m[8] = v.m[8];
		}

		/*! constructor taking three columns vector*/

		explicit Matrix3x3Mod<T> (const Vector3D<T> V1,const Vector3D<T> V2,const Vector3D<T> V3)
		{
		 this->m[0] = V1[0]; this->m[1] =V2[0]; this->m[2] = V3[0];
		 this->m[3] = V1[1]; this->m[4] =V2[1]; this->m[5] = V3[1];
		 this->m[6] = V1[2]; this->m[7] =V2[2]; this->m[8] = V3[2];

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
		 this->m[0]=T(1.0) - (yy + zz), 
			 this->m[1]=xy - wz, 
			 this->m[2]=xz + wy,
			 this->m[3]=xy + wz, 
			 this->m[4]=T(1.0) - (xx + zz), 
			 this->m[5]=yz - wx,
			 this->m[6]=xz - wy, 
			 this->m[7]=yz + wx, 
			 this->m[8]=T(1.0) - (xx + yy);
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
		    this->m[0]=T(1.0) - (yy + zz); 
		    this->m[1]=xy - wz; 
		    this->m[2]=xz + wy;
		    this->m[3]=xy + wz; 
		    this->m[4]=T(1.0) - (xx + zz); 
		    this->m[5]=yz - wx;
		    this->m[6]=xz - wy; 
		    this->m[7]=yz + wx; 
		    this->m[8]=T(1.0) - (xx + yy);
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
			this->m[0]=T(1.0) - (yy + zz); 
			this->m[1]=xy - wz; 
			this->m[2]=xz + wy;
			this->m[3]=xy + wz; 
			this->m[4]=T(1.0) - (xx + zz); 
			this->m[5]=yz - wx;
			this->m[6]=xz - wy; 
			this->m[7]=yz + wx; 
			this->m[8]=T(1.0) - (xx + yy);
		}

		
		/*!Euler
         * ROLL PITCH YAW (R = Ry * Rp * Rr) */
		explicit Matrix3x3Mod<T> (const T &roll, const T &pitch, const T &yaw)
        {

            T cy(cos(yaw)); 
            T sy(sin(yaw)); 
            T cp(cos(pitch)); 
            T sp(sin(pitch)); 
            T cr(cos(roll));
            T sr(sin(roll));

            T cc = cy * cr; 
            T cs = cy * sr; 
            T sc = sy * cr; 
            T ss = sy * sr;

            T sysp = sy * sp;
            T cysp = cy * sp;
            T sysr = sy * sr;
            T sycr = sy * cr;

            this->m[0] = cy*cp;
            this->m[1] = cysp*sr-sycr;
            this->m[2] = cysp*cr+sysr;

            this->m[3] = sy*cp;
            this->m[4] = sysp*sr+cy*cr;
            this->m[5] = sysp*cr-cy*sr;

            this->m[6] = -sp;
            this->m[7] = cp*sr;
            this->m[8] = cp*cr;
        }

						/*! set from 9 scalar */
		void Set (
			const T x0, const T x1, const T x2, 
			const T x3, const T x4, const T x5, 
			const T x6, const T x7, const T x8
			)
		{
			this->m[0]=x0; this->m[1] = x1; this->m[2]=x2;
			this->m[3]=x3; this->m[4] = x4; this->m[5]=x5;
			this->m[6]=x6; this->m[7] = x7; this->m[8]=x8;
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
			this->m[0]=T(1.0) - (yy + zz); 
			this->m[1]=xy - wz; 
			this->m[2]=xz + wy;
			this->m[3]=xy + wz; 
			this->m[4]=T(1.0) - (xx + zz); 
			this->m[5]=yz - wx;
			this->m[6]=xz - wy; 
			this->m[7]=yz + wx; 
			this->m[8]=T(1.0) - (xx + yy);
		}


		
		/*! Set from a pointer */
		void Set(const T* const x)
		{
			this->m[0]=x[0]; this->m[1] = x[1]; this->m[2]=x[2];
			this->m[3]=x[3]; this->m[4] = x[4]; this->m[5]=x[5];
			this->m[6]=x[6]; this->m[7] = x[7]; this->m[8]=x[8];
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
			this->m[0]=T(1.0) - (yy + zz), 
			this->m[1]=xy - wz, 
			this->m[2]=xz + wy,
			this->m[3]=xy + wz, 
			this->m[4]=T(1.0) - (xx + zz), 
			this->m[5]=yz - wx,
			this->m[6]=xz - wy, 
			this->m[7]=yz + wx, 
			this->m[8]=T(1.0) - (xx + yy);
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
			this->m[0]=T(1.0) - (yy + zz); 
			this->m[1]=xy - wz; 
			this->m[2]=xz + wy;
			this->m[3]=xy + wz; 
			this->m[4]=T(1.0) - (xx + zz); 
			this->m[5]=yz - wx;
			this->m[6]=xz - wy; 
			this->m[7]=yz + wx; 
			this->m[8]=T(1.0) - (xx + yy);
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
			
			this->m[0]= cc + sp * ss;
			this->m[1]= cs - sp * sc;
			this->m[2]= -sy * cp;
			this->m[3]= -cp * sr;
			this->m[4]= cp * cr;
			this->m[5]=  -sp;
			this->m[6]= sc - sp * cs;
			this->m[7]= ss + sp * cc;
			this->m[8]= cy * cp;
		}

		/*! Transposition */
		Matrix3x3<T>& TransposeIt()
		{
			T t;
			t=this->m[1];
			this->m[1]=this->m[3];
			this->m[3]=t;

			t=this->m[2];
			this->m[2]=this->m[6];
			this->m[6]=t;
			
			t=this->m[5];
			this->m[5]=this->m[7];
			this->m[7]=t;

			return *this;
		}

		/*! Transposition */
		Matrix3x3<T> Transpose() const
		{
			return Matrix3x3<T> (this->m[0],this->m[3],this->m[6],
								  this->m[1],this->m[4],this->m[7],
								  this->m[2],this->m[5],this->m[8]);
		}

		Vector3Mod<T> operator *(const Vector3D<T>& v) const
		{
			Vector3Mod<T> vr(this->m[0]*v[0]+this->m[1]*v[1]+this->m[2]*v[2],
									this->m[3]*v[0]+this->m[4]*v[1]+this->m[5]*v[2],
									this->m[6]*v[0]+this->m[7]*v[1]+this->m[8]*v[2]);
			return vr;
		}

		Matrix3x3<T> operator *(const Matrix3x3<T>& B) const
		{
			return Matrix3x3<T>( 
			 this->m[0] * B.m[0] + this->m[1] * B.m[3] + this->m[2] * B.m[6],
			 this->m[0] * B.m[1] + this->m[1] * B.m[4] + this->m[2] * B.m[7],
			 this->m[0] * B.m[2] + this->m[1] * B.m[5] + this->m[2] * B.m[8],
			 this->m[3] * B.m[0] + this->m[4] * B.m[3] + this->m[5] * B.m[6],
			 this->m[3] * B.m[1] + this->m[4] * B.m[4] + this->m[5] * B.m[7],
			 this->m[3] * B.m[2] + this->m[4] * B.m[5] + this->m[5] * B.m[8],
			 this->m[6] * B.m[0] + this->m[7] * B.m[3] + this->m[8] * B.m[6],
			 this->m[6] * B.m[1] + this->m[7] * B.m[4] + this->m[8] * B.m[7],
			 this->m[6] * B.m[2] + this->m[7] * B.m[5] + this->m[8] * B.m[8]);
			 
		}

		void operator *=(const Matrix3x3<T>& B) 
		{
			Matrix3x3<T> temp(*this);
			this->m[0] = temp.m[0] * B.m[0] + temp.m[1] * B.m[3] + temp.m[2] * B.m[6];
			this->m[1] = temp.m[0] * B.m[1] + temp.m[1] * B.m[4] + temp.m[2] * B.m[7];
			this->m[2] = temp.m[0] * B.m[2] + temp.m[1] * B.m[5] + temp.m[2] * B.m[8];
			this->m[3] = temp.m[3] * B.m[0] + temp.m[4] * B.m[3] + temp.m[5] * B.m[6];
			this->m[4] = temp.m[3] * B.m[1] + temp.m[4] * B.m[4] + temp.m[5] * B.m[7];
			this->m[5] = temp.m[3] * B.m[2] + temp.m[4] * B.m[5] + temp.m[5] * B.m[8];
			this->m[6] = temp.m[6] * B.m[0] + temp.m[7] * B.m[3] + temp.m[8] * B.m[6];
			this->m[7] = temp.m[6] * B.m[1] + temp.m[7] * B.m[4] + temp.m[8] * B.m[7];
			this->m[8] = temp.m[6] * B.m[2] + temp.m[7] * B.m[5] + temp.m[8] * B.m[8]; 

		}




	};
};

#endif
