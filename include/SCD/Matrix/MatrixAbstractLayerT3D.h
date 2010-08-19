/*! This is an implementation of MatrixAbstractLayerSmall using
 * T3D, R3D and V3D
 * 
 * (c) LAAS, CNRS, 2007
 */

/*T3D which implements SmallMatrix4x4*/
#include "t3d/t3d.h"

typedef T3D matrix4d;

#define MAL_S4x4_MATRIX(name,type) \
  T3D name


#define MAL_S4x4_MATRIX_CLEAR(name) \
  /*Clear don't have any sense*/ 

#define MAL_S4x4_MATRIX_SET_IDENTITY(name) \
  name=t3dMatrixIdentity

#define MAL_S4x4_INVERSE(name,inv_matrix,type)	\
  inv_matrix=~name; 

#define MAL_S4x4_RET_TRANSPOSE(matrix) \
  /*Transpose don't have any sense*/ 

#define MAL_S4x4_TRANSPOSE_A_in_At(A,At)		\
  /*Transpose don't have any sense*/ 

#define MAL_S4x4_RET_A_by_B(A,B) \
  (A)*(B)

#define MAL_S4x4_C_eq_A_by_B(C,A,B) \
  (C)=(A)*(B)

#define MAL_S4x4_MATRIX_ACCESS_I(name, i) \
  name.matrix[i]

#define MAL_S4x4_MATRIX_ACCESS_I_J(name, i, j) \
  name.matrix(i,j)


#include "t3d/v3d.h"
#include <cmath>

/*V3D which implements SmallVector3*/
typedef V3D vector3d;

#define MAL_S3_VECTOR(name,type)		\
  V3D name

#define MAL_S3_VECTOR_SIZE(name)		\
  3 

#define MAL_S3_VECTOR_FILL(name,value)		\
  { name[0] = value;				\
    name[1] = value;				\
    name[2] = value; }

#define MAL_S3_VECTOR_NORM(name)		\
    sqrt(name[0]*name[0]+			\
    name[1]*name[1]+				\
    name[2]*name[2])

#define MAL_S3_VECTOR_CROSS_PRODUCT(res,v1,v2)	\
  { res[0] = v1[1]*v2[2]-v1[2]*v2[1];		\
    res[1] = v1[2]*v2[0]-v1[0]*v2[2];		\
    res[2] = v1[0]*v2[1]-v1[1]*v2[0];}		

#define MAL_S3_RET_VECTOR_DATABLOCK(name)	\
  &name

#define MAL_S3_VECTOR_ACCESS(name, i)  		\
  name[i]


/*V3D which implements SmallVector4*/
typedef V3D vector4d;

#define MAL_S4_VECTOR(name,type)		\
  V3D name

#define MAL_S4_VECTOR_SIZE(name)		\
  3 

#define MAL_S4_VECTOR_FILL(name,value)		\
  { name[0] = value;				\
    name[1] = value;				\
    name[2] = value; 				\
    name[3] = value; }

#define MAL_S4_VECTOR_NORM(name)		\
  { sqrt(name[0]*name[0]+			\
    name[1]*name[1]+				\
    name[2]*name[2]+				\
    name[3]*name[3])}

#define MAL_S4_RET_VECTOR_DATABLOCK(name)	\
  &name

#define MAL_S4_VECTOR_ACCESS(name, i)  		\
  name[i]



//typedef R3D matrix3d;

/*SmallMatrix3x3. It has to be replaced by R3D once it'd been created*/
namespace PatternGeneratorJRL
{
  /*! Template to handle a  3x3 matrix*/
  template <typename T> struct Matrix3x3
    {
      /*! The data array. */
      T m[9];

      /*! Defaut constructor. */
      Matrix3x3<T>() 
      { m[0]=0.0; m[1] = 0.0; m[2]=0.0;
	m[3]=0.0; m[4] = 0.0; m[5]=0.0;
	m[6]=0.0; m[7] = 0.0; m[8]=0.0;
      }

      /*! Constructor form a scalar */
      Matrix3x3<T> (const T x)
      {
	m[0]=x; m[1] = x; m[2]=x;
	m[3]=x; m[4] = x; m[5]=x;
	m[6]=x; m[7] = x; m[8]=x;
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
      inline T& operator[](unsigned int i) 
	 { return m[i];}
      
      /*! Access by giving the (i,j) element. */
      inline T& operator()(unsigned int i, unsigned int j) 
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
      MAL_S3_VECTOR(,T) operator *(MAL_S3_VECTOR(v,T)) 
      {
	MAL_S3_VECTOR(vr,T);
	vr[0] = m[0]*v[0]+m[1]*v[1]+m[2]*v[2];
	vr[1] = m[3]*v[0]+m[4]*v[1]+m[5]*v[2];
	vr[2] = m[6]*v[0]+m[7]*v[1]+m[8]*v[2];
	return vr;
      }

      /*! Multiplication operator with a vector */
      void CeqthismulB( MAL_S3_VECTOR(,T) &B,MAL_S3_VECTOR(,T) &C) const
      {

	C[0] = m[0]*B[0]+m[1]*B[1]+m[2]*B[2];
	C[1] = m[3]*B[0]+m[4]*B[1]+m[5]*B[2];
	C[2] = m[6]*B[0]+m[7]*B[1]+m[8]*B[2];
      }
      
      /*! Transposition */
      Matrix3x3<T> Transpose()
      {
	struct Matrix3x3<T> A;
	A.m[0] = m[0]; A.m[1] = m[3]; A.m[2] = m[6];
	A.m[3] = m[1]; A.m[4] = m[4]; A.m[5] = m[7];
	A.m[6] = m[2]; A.m[7] = m[5]; A.m[8] = m[8];
	return A;
      }

      /*! Transposition */
      void Transpose(Matrix3x3<T> A)
      {
	A.m[0] = m[0]; A.m[1] = m[3]; A.m[2] = m[6];
	A.m[3] = m[1]; A.m[4] = m[4]; A.m[5] = m[7];
	A.m[6] = m[2]; A.m[7] = m[5]; A.m[8] = m[8];
      }
      
      /*! Inversion */
      void Inversion(struct Matrix3x3 &A)
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
	return  m[0]*m[4]*m[8]
	  + m[1]*m[5]*m[6]
	  + m[2]*m[3]*m[7]
	  - m[2]*m[4]*m[6]
	  - m[0]*m[5]*m[7]
	  - m[1]*m[3]*m[8]; 
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

};

typedef PatternGeneratorJRL::Matrix3x3<double> matrix3d;

#define MAL_S3x3_MATRIX(name,type) \
  PatternGeneratorJRL::Matrix3x3<type> name

#define MAL_S3x3_MATRIX_CLEAR(name) \
  name.setZero()

#define MAL_S3x3_MATRIX_SET_IDENTITY(name) \
  name.setIdentity()

#define MAL_S3x3_INVERSE(name,inv_matrix,type)	\
  name.Inversion(inv_matrix);

#define MAL_S3x3_RET_TRANSPOSE(matrix) \
  matrix.Transpose();

#define MAL_S3x3_TRANSPOSE_A_in_At(A,At)		\
  A.Transpose(At);

#define MAL_S3x3_RET_A_by_B(A,B) \
  A*B

#define MAL_S3x3_C_eq_A_by_B(C,A,B) \
  A.CeqthismulB(B,C);


#define MAL_S3x3_MATRIX_ACCESS_I(name, i) \
  name[i]

#define MAL_S3x3_MATRIX_ACCESS_I_J(name, i, j) \
  name(i,j)


