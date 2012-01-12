/*! This is a very fast and simple implementation
* of a 3D matrix class of double.
* 
* (c) Olivier Stasse, JRL, CNRS-AIST, ISRI, 2007
*/

#ifndef _MATRIX3D_MAL_DEFAULT_
#define _MATRIX3D_MAL_DEFAULT_

namespace MAL_Default
{
	/*! Template to handle a  3x3 matrix*/
	template <typename T> struct Matrix3x3
	{
		/*! The data array. */
		T m[9];

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
      ar & m;
    }
  
		/*! Defaut constructor. */
		explicit Matrix3x3<T>() 
		{ 
			m[0]=0.0; m[1] = 0.0; m[2]=0.0;
			m[3]=0.0; m[4] = 0.0; m[5]=0.0;
			m[6]=0.0; m[7] = 0.0; m[8]=0.0;
		}

		/*! Constructor from a scalar */
		explicit Matrix3x3<T> (const T x)
		{
			m[0]=x; m[1] = x; m[2]=x;
			m[3]=x; m[4] = x; m[5]=x;
			m[6]=x; m[7] = x; m[8]=x;
		}

		/*! Constructor from 9 scalar */
		explicit Matrix3x3<T> (
			const T x0, const T x1, const T x2, 
			const T x3, const T x4, const T x5, 
			const T x6, const T x7, const T x8
			)
		{
			m[0]=x0; m[1] = x1; m[2]=x2;
			m[3]=x3; m[4] = x4; m[5]=x5;
			m[6]=x6; m[7] = x7; m[8]=x8;
		}

		/*! Copy constructor */
		Matrix3x3<T> (const struct Matrix3x3<T> &v)
		{
			m[0] = v.m[0]; m[1] = v.m[1]; m[2] = v.m[2];
			m[3] = v.m[3]; m[4] = v.m[4]; m[5] = v.m[5];
			m[6] = v.m[6]; m[7] = v.m[7]; m[8] = v.m[8];
		}

		/*! Hybrid copy constructor */
		template <typename T2>
		Matrix3x3<T> (const struct Matrix3x3<T2> &v)
		{
			m[0] = v.m[0]; m[1] = v.m[1]; m[2] = v.m[2];
			m[3] = v.m[3]; m[4] = v.m[4]; m[5] = v.m[5];
			m[6] = v.m[6]; m[7] = v.m[7]; m[8] = v.m[8];
		}

		/*! ith element considering the matrix as an array. */
		inline T& operator[]( unsigned int i) 
		{ return m[i];}


		/*! ith element considering the matrix as an array. */
		inline T operator[]( unsigned int i) const
		{ return m[i];}


		/*! Access by giving the (i,j) element. */
		inline T& operator()( unsigned int i,  unsigned int j) 
		{ return m[3*i+j]; }

		/*! Access by giving the (i,j) element. */
		inline const T& operator()(unsigned int i, unsigned int j) const
		{ return m[3*i+j]; }

		/*! Set to zero matrix */
		inline void setZero(void) 
		{
			m[0] = 0.0; m[1] = 0.0; m[2] = 0.0;
			m[3] = 0.0; m[4] = 0.0; m[5] = 0.0;
			m[6] = 0.0; m[7] = 0.0; m[8] = 0.0;
		}

		/*! Set to identity */
		void setIdentity(void)
		{
			m[0] = 1.0; m[1] = 0.0; m[2] = 0.0;
			m[3] = 0.0; m[4] = 1.0; m[5] = 0.0;
			m[6] = 0.0; m[7] = 0.0; m[8] = 1.0;
		}

		/*! Adition operator */
		Matrix3x3<T>  operator+(const struct Matrix3x3<T> & B)
		{
			struct Matrix3x3<T> A;
			A.m[0] = m[0] + B.m[0]; A.m[1] = m[1] + B.m[1]; A.m[2] = m[2] + B.m[2];
			A.m[3] = m[3] + B.m[3]; A.m[4] = m[4] + B.m[4]; A.m[5] = m[5] + B.m[5];
			A.m[6] = m[6] + B.m[6]; A.m[7] = m[7] + B.m[7]; A.m[8] = m[8] + B.m[8];
			return A;
		}

		/*! Substraction operator */
		struct Matrix3x3<T>  operator-(const struct Matrix3x3<T> &B)
		{
			struct Matrix3x3<T> A;
			A.m[0] = m[0] - B.m[0]; A.m[1] = m[1] - B.m[1]; A.m[2] = m[2] - B.m[2];
			A.m[3] = m[3] - B.m[3]; A.m[4] = m[4] - B.m[4]; A.m[5] = m[5] - B.m[5];
			A.m[6] = m[6] - B.m[6]; A.m[7] = m[7] - B.m[7]; A.m[8] = m[8] - B.m[8];
			return A;
		}

		/*! Multiplication operator with another matrix */
		Matrix3x3<T>  operator* (const struct Matrix3x3<T> &B) const
		{
			Matrix3x3<T> A;
			A.m[0] = m[0] * B.m[0] + m[1] * B.m[3] + m[2] * B.m[6];
			A.m[1] = m[0] * B.m[1] + m[1] * B.m[4] + m[2] * B.m[7];
			A.m[2] = m[0] * B.m[2] + m[1] * B.m[5] + m[2] * B.m[8];
			A.m[3] = m[3] * B.m[0] + m[4] * B.m[3] + m[5] * B.m[6];
			A.m[4] = m[3] * B.m[1] + m[4] * B.m[4] + m[5] * B.m[7];
			A.m[5] = m[3] * B.m[2] + m[4] * B.m[5] + m[5] * B.m[8];
			A.m[6] = m[6] * B.m[0] + m[7] * B.m[3] + m[8] * B.m[6];
			A.m[7] = m[6] * B.m[1] + m[7] * B.m[4] + m[8] * B.m[7];
			A.m[8] = m[6] * B.m[2] + m[7] * B.m[5] + m[8] * B.m[8];
			return A;
		}

		void  CeqthismulB (const Matrix3x3<T> &B, Matrix3x3<T> &C) const
		{
			C.m[0] = m[0] * B.m[0] + m[1] * B.m[3] + m[2] * B.m[6];
			C.m[1] = m[0] * B.m[1] + m[1] * B.m[4] + m[2] * B.m[7];
			C.m[2] = m[0] * B.m[2] + m[1] * B.m[5] + m[2] * B.m[8];
			C.m[3] = m[3] * B.m[0] + m[4] * B.m[3] + m[5] * B.m[6];
			C.m[4] = m[3] * B.m[1] + m[4] * B.m[4] + m[5] * B.m[7];
			C.m[5] = m[3] * B.m[2] + m[4] * B.m[5] + m[5] * B.m[8];
			C.m[6] = m[6] * B.m[0] + m[7] * B.m[3] + m[8] * B.m[6];
			C.m[7] = m[6] * B.m[1] + m[7] * B.m[4] + m[8] * B.m[7];
			C.m[8] = m[6] * B.m[2] + m[7] * B.m[5] + m[8] * B.m[8];
		}

		/*! Multiplication operator with a constant */
		Matrix3x3<T> operator * (const double & r) 	
		{	
			struct Matrix3x3<T> result;
			result.m[0] = m[0] * r;
			result.m[1] = m[1] * r;
			result.m[2] = m[2] * r;
			result.m[3] = m[3] * r;
			result.m[4] = m[4] * r;
			result.m[5] = m[5] * r;
			result.m[6] = m[6] * r;
			result.m[7] = m[7] * r;
			result.m[8] = m[8] * r;
			return result;
		}



		/*! Multiplication operator with a vector */
		Vector3D<T> operator *(const Vector3D<T>& v) 
		{
			Vector3D<T> vr;
			vr[0] = m[0]*v[0]+m[1]*v[1]+m[2]*v[2];
			vr[1] = m[3]*v[0]+m[4]*v[1]+m[5]*v[2];
			vr[2] = m[6]*v[0]+m[7]*v[1]+m[8]*v[2];
			return vr;
		}

		/*! Multiplication operator with a vector */
		Vector3D<T> operator *(const Vector3D<T>& v) const
		{
			Vector3D<T> vr;
			vr[0] = m[0]*v[0]+m[1]*v[1]+m[2]*v[2];
			vr[1] = m[3]*v[0]+m[4]*v[1]+m[5]*v[2];
			vr[2] = m[6]*v[0]+m[7]*v[1]+m[8]*v[2];
			return vr;
		}

		/*! Multiplication operator with a vector */
		void CeqthismulB( Vector3D<T> &B,Vector3D<T> &C) const
		{

			C[0] = m[0]*B[0]+m[1]*B[1]+m[2]*B[2];
			C[1] = m[3]*B[0]+m[4]*B[1]+m[5]*B[2];
			C[2] = m[6]*B[0]+m[7]*B[1]+m[8]*B[2];
		}

		/*! Transposition */
		Matrix3x3<T> Transpose() const
		{
			struct Matrix3x3<T> A;
			A.m[0] = m[0]; A.m[1] = m[3]; A.m[2] = m[6];
			A.m[3] = m[1]; A.m[4] = m[4]; A.m[5] = m[7];
			A.m[6] = m[2]; A.m[7] = m[5]; A.m[8] = m[8];
			return A;
		}

		/*! Transposition */
		void Transpose(Matrix3x3<T>& A) const
		{
			A.m[0] = m[0]; A.m[1] = m[3]; A.m[2] = m[6];
			A.m[3] = m[1]; A.m[4] = m[4]; A.m[5] = m[7];
			A.m[6] = m[2]; A.m[7] = m[5]; A.m[8] = m[8];
		}

		/*! Inversion */
		void Inversion(struct Matrix3x3 &A) const
		{
			T det = 1/determinant();
			A.m[0] = (m[4]*m[8] - m[5]*m[7]) *det;
			A.m[1] = (m[2]*m[7] - m[1]*m[8]) *det;
			A.m[2] = (m[1]*m[5] - m[2]*m[4]) *det;
			A.m[3] = ( m[5]*m[6] - m[3]*m[8] ) * det;
			A.m[4] = ( m[0]*m[8] - m[2]*m[6] ) * det;
			A.m[5] = ( m[2]*m[3] - m[0]*m[5] ) * det;
			A.m[6] = ( m[3]*m[7] - m[4]*m[6] ) * det;
			A.m[7] = ( m[1]*m[6] - m[0]*m[7] ) * det;
			A.m[8] = ( m[0]*m[4] - m[1]*m[3] ) * det;
		}

		/*! Determinant */
		T determinant() const	
		{ 
		  T det = m[0]*m[4]*m[8];
		  det += m[1]*m[5]*m[6];
		  det += m[2]*m[3]*m[7];
		  det -= m[2]*m[4]*m[6];
		  det -= m[0]*m[5]*m[7];
		  det -= m[1]*m[3]*m[8];
		  return det;
		}

		/*! fills with value */
		void Fill(T value)
		{
			m[0] = value;
			m[1] = value;
			m[2] = value;
			m[3] = value;
			m[4] = value;
			m[5] = value;
			m[6] = value;
			m[7] = value;
			m[8] = value;
		}

		/*! returns true if matrix is identity */
		bool IsIdentity()
		{
			return((m[0] == 1) && (m[4] == 1) && (m[8] == 1) && (m[1] == 0)
				&& (m[2] == 0) && (m[3] == 0) && (m[5] == 0) && (m[6] == 0)
				&& (m[7] == 0));
		}

		/*! Self matrix addition */
		void operator += (const Matrix3x3<T>& B)	
		{	
			m[0] += B.m[0];
			m[1] += B.m[1];
			m[2] += B.m[2];
			m[3] += B.m[3];
			m[4] += B.m[4];
			m[5] += B.m[5];
			m[6] += B.m[6];
			m[7] += B.m[7];
			m[8] += B.m[8]; 
		}

		/*! Local matrix substraction */
		void operator -= (const Matrix3x3<T>& B)	
		{	
			m[0] -= B.m[0];
			m[1] -= B.m[1];
			m[2] -= B.m[2];
			m[3] -= B.m[3];
			m[4] -= B.m[4];
			m[5] -= B.m[5];
			m[6] -= B.m[6];
			m[7] -= B.m[7];
			m[8] -= B.m[8]; 
		}

		///Local matrix multiplication
		void operator *= (const Matrix3x3<T>& B)	
		{	Matrix3x3<T> temp(*this);
		m[0] = temp.m[0] * B.m[0] + temp.m[1] * B.m[3] + temp.m[2] * B.m[6];
		m[1] = temp.m[0] * B.m[1] + temp.m[1] * B.m[4] + temp.m[2] * B.m[7];
		m[2] = temp.m[0] * B.m[2] + temp.m[1] * B.m[5] + temp.m[2] * B.m[8];
		m[3] = temp.m[3] * B.m[0] + temp.m[4] * B.m[3] + temp.m[5] * B.m[6];
		m[4] = temp.m[3] * B.m[1] + temp.m[4] * B.m[4] + temp.m[5] * B.m[7];
		m[5] = temp.m[3] * B.m[2] + temp.m[4] * B.m[5] + temp.m[5] * B.m[8];
		m[6] = temp.m[6] * B.m[0] + temp.m[7] * B.m[3] + temp.m[8] * B.m[6];
		m[7] = temp.m[6] * B.m[1] + temp.m[7] * B.m[4] + temp.m[8] * B.m[7];
		m[8] = temp.m[6] * B.m[2] + temp.m[7] * B.m[5] + temp.m[8] * B.m[8]; 
		}

		/*! Matrix product with a scalar */
		void operator *= (const T& t)	
		{	
			m[0] *= t;
			m[1] *= t;
			m[2] *= t;
			m[3] *= t;
			m[4] *= t;
			m[5] *= t;
			m[6] *= t;
			m[7] *= t;
			m[8] *= t;
		}


		inline friend std::ostream& operator <<(std::ostream &os,Matrix3x3<T> const &A)
		{
			for(int i=0;i<3;i++)
			{
				for(int j=0;j<3;j++)
					os << A.m[i*3+j] << " ";
				os << std::endl;
			}
			return os;
		}



	};

}

#endif


