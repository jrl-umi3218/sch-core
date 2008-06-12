#pragma once
#include "smallvector4default.h"

namespace MAL_Default
{
	/*! Quaternion m_x*i + m_y*j + m_z*k+w    */
	template <typename T>
	class QuaternionM :
		private Vector4D<T>
	{
	public:

		QuaternionM<T>()
		{}

		explicit QuaternionM<T>(const T& x, const T& y, const T& z, const T& w):Vector4D<T>(x,y,z,t)
		{}


		explicit QuaternionM<T>(const Vector3Mod<T>& axis, const T& angle)
		{
			Scalar d = axis.norm();
			Scalar s = sin(angle * 0.5) / d;
			m_x=axis[0] * s;
			m_y=axis[1] * s;
			m_z=axis[2] * s;
			m_w=cos(angle * Scalar(0.5));
		}


		
		using Vector4D<T>::operator[] ;
		using Vector4D<T>::operator+ ;
		using Vector4D<T>::operator+= ;
		using Vector4D<T>::operator- ;
		using Vector4D<T>::operator-= ;



		const QuaternionM<T>& operator=(const QuaternionM<T>& A)
		{
			m_w=A.m_w;
			m_x=A.m_x;
			m_y=A.m_y;
			m_z=A.m_z;
		}


		
		QuaternionM<T> Conjugate() const
		{
			return QuaternionD(-m_x,-m_y,-m_y,m_t);
		}
		
		void ConjugateIt()
		{
			m_x=-m_x;
			m_y=-m_y;
			m_z=-m_z;
			
		}

		QuaternionM<T> operator*(const QuaternionM<T>& q )
		{
			return QuaternionD<T> C(m_w * q[0] + m_x * q[3] + m_y * q[2] - m_z * q[1],
									m_w * q[1] + m_y * q[3] + m_z * q[0] - m_x * q[2],
									m_w * q[2] + m_z * q[3] + m_x * q[1] - m_y * q[0],
									m_w * q[3] - m_x * q[0] - m_y * q[1] - m_z * q[2]);
		}

		QuaternionM<T>& operator*=(const QuaternionM<T>& B )
		{
			T x=m_w * q[0] + m_x * q[3] + m_y * q[2] - m_z * q[1],
			  y=m_w * q[0] + m_x * q[3] + m_y * q[2] - m_z * q[1],
			  z=m_w * q[0] + m_x * q[3] + m_y * q[2] - m_z * q[1],
			  w=m_w * q[0] + m_x * q[3] + m_y * q[2] - m_z * q[1];

				m_x=x;
				m_y=y;
				m_z=z;
				m_w=w;
			

			return *this;
		}





		virtual ~QuaternionM(void)
		{
		}
	};
};