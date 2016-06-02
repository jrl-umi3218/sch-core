/*! This is a very fast and simple implementation
* of a 3D matrix class of double.
*
* (c) Olivier Stasse, JRL, CNRS-AIST, ISRI, 2007
*/

#ifndef _MATRIX3D_MAL_DEFAULT_
#define _MATRIX3D_MAL_DEFAULT_



namespace CD_Matrix
{

  template<typename U, bool b> struct Vector3T;
  template<typename U> class QuaternionT;

  /*! Template to handle a  3x3 matrix*/
  template <typename T>
  struct Matrix3x3T
  {



    /*! The data array. */
    T m[9];

    template<class Archive>
    void serialize(Archive & ar, const unsigned int /*version*/)
    {
      ar & m;
    }


    /*! Defaut constructor. */
    explicit Matrix3x3T<T>()
    {
      m[0]=0.0;
      m[1] = 0.0;
      m[2]=0.0;
      m[3]=0.0;
      m[4] = 0.0;
      m[5]=0.0;
      m[6]=0.0;
      m[7] = 0.0;
      m[8]=0.0;
    }

    /*! Constructor from a pointer */
    explicit Matrix3x3T<T> (const T* const  x)
    {
      m[0]=x[0];
      m[1]=x[1];
      m[2]=x[2];
      m[3]=x[3];
      m[4]=x[4];
      m[5]=x[5];
      m[6]=x[6];
      m[7]=x[7];
      m[8]=x[8];
    }

    /*! Constructor from a scalar */
    explicit Matrix3x3T<T> (const T& x)
    {
      m[0]=x;
      m[1] = x;
      m[2]=x;
      m[3]=x;
      m[4] = x;
      m[5]=x;
      m[6]=x;
      m[7] = x;
      m[8]=x;
    }

    /*! Constructor from 9 scalar */
    explicit Matrix3x3T<T> (
      const T x0, const T x1, const T x2,
      const T x3, const T x4, const T x5,
      const T x6, const T x7, const T x8
    )
    {
      m[0]=x0;
      m[1]=x1;
      m[2]=x2;
      m[3]=x3;
      m[4]=x4;
      m[5]=x5;
      m[6]=x6;
      m[7]=x7;
      m[8]=x8;
    }

    /*! Copy constructor */
    Matrix3x3T<T> (const struct Matrix3x3T<T> &v)
    {
      m[0] = v.m[0];
      m[1] = v.m[1];
      m[2] = v.m[2];
      m[3] = v.m[3];
      m[4] = v.m[4];
      m[5] = v.m[5];
      m[6] = v.m[6];
      m[7] = v.m[7];
      m[8] = v.m[8];
    }

    /*! Hybrid copy constructor */
    template <typename T2>
    Matrix3x3T<T> (const struct Matrix3x3T<T2> &v)
    {
      m[0] = v.m[0];
      m[1] = v.m[1];
      m[2] = v.m[2];
      m[3] = v.m[3];
      m[4] = v.m[4];
      m[5] = v.m[5];
      m[6] = v.m[6];
      m[7] = v.m[7];
      m[8] = v.m[8];
    }

    /*! constructor taking three columns vector*/
    template <bool b>
    explicit Matrix3x3T<T> (const Vector3T<T,b> V1,const Vector3T<T,b> V2,const Vector3T<T,b> V3)
    {
      m[0] = V1[0];
      m[1] =V2[0];
      m[2] = V3[0];
      m[3] = V1[1];
      m[4] =V2[1];
      m[5] = V3[1];
      m[6] = V1[2];
      m[7] =V2[2];
      m[8] = V3[2];

    }

    /*! quatrenion*/
    explicit Matrix3x3T<T> (const QuaternionT<T>& q)
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
    explicit Matrix3x3T<T> (const T &q0,const T &q1,const T &q2,const T &q3)
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

    /*! angle axis*/
    template <bool b>
    explicit Matrix3x3T<T> (const T &angle,const Vector3T<T,b>  &axis)
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


    /*!Euler
     * ROLL PITCH YAW - AROUND X, Y THEN Z */
    explicit Matrix3x3T<T> (const T &roll, const T &pitch, const T &yaw)
    {

      T cy(cos(yaw));
      T sy(sin(yaw));
      T cp(cos(pitch));
      T sp(sin(pitch));
      T cr(cos(roll));
      T sr(sin(roll));

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

    /*! \brief set from 9 scalar */
    void Set (
      const T x0, const T x1, const T x2,
      const T x3, const T x4, const T x5,
      const T x6, const T x7, const T x8
    )
    {
      this->m[0]=x0;
      this->m[1] = x1;
      this->m[2]=x2;
      this->m[3]=x3;
      this->m[4] = x4;
      this->m[5]=x5;
      this->m[6]=x6;
      this->m[7] = x7;
      this->m[8]=x8;
    }

    /*Set from a vector and an array*/
    template <bool b>
    void Set(const T &angle,const Vector3T<T,b>  &axis)
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
      this->m[0]=x[0];
      this->m[1] = x[1];
      this->m[2]=x[2];
      this->m[3]=x[3];
      this->m[4] = x[4];
      this->m[5]=x[5];
      this->m[6]=x[6];
      this->m[7] = x[7];
      this->m[8]=x[8];
    }


    /*!quatrenion*/
    void Set (const QuaternionT<T>& q)
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




    /*! ith element considering the matrix as an array. */
    inline T& operator[]( unsigned int i)
    {
      return m[i];
    }


    /*! ith element considering the matrix as an array. */
    inline T operator[]( unsigned int i) const
    {
      return m[i];
    }


    /*! Access by giving the (i,j) element. */
    inline T& operator()( unsigned int i,  unsigned int j)
    {
      return m[3*i+j];
    }

    /*! Access by giving the (i,j) element. */
    inline const T& operator()(unsigned int i, unsigned int j) const
    {
      return m[3*i+j];
    }

    /*! Set to zero matrix */
    inline void setZero(void)
    {
      m[0] = 0.0;
      m[1] = 0.0;
      m[2] = 0.0;
      m[3] = 0.0;
      m[4] = 0.0;
      m[5] = 0.0;
      m[6] = 0.0;
      m[7] = 0.0;
      m[8] = 0.0;
    }

    /*! Set to identity */
    void setIdentity(void)
    {
      m[0] = 1.0;
      m[1] = 0.0;
      m[2] = 0.0;
      m[3] = 0.0;
      m[4] = 1.0;
      m[5] = 0.0;
      m[6] = 0.0;
      m[7] = 0.0;
      m[8] = 1.0;
    }

    /*! Adition operator */
    Matrix3x3T<T>  operator+(const struct Matrix3x3T<T> & B)
    {
      struct Matrix3x3T<T> A;
      A.m[0] = m[0] + B.m[0];
      A.m[1] = m[1] + B.m[1];
      A.m[2] = m[2] + B.m[2];
      A.m[3] = m[3] + B.m[3];
      A.m[4] = m[4] + B.m[4];
      A.m[5] = m[5] + B.m[5];
      A.m[6] = m[6] + B.m[6];
      A.m[7] = m[7] + B.m[7];
      A.m[8] = m[8] + B.m[8];
      return A;
    }

    /*! Substraction operator */
    struct Matrix3x3T<T>  operator-(const struct Matrix3x3T<T> &B)
    {
      struct Matrix3x3T<T> A;
      A.m[0] = m[0] - B.m[0];
      A.m[1] = m[1] - B.m[1];
      A.m[2] = m[2] - B.m[2];
      A.m[3] = m[3] - B.m[3];
      A.m[4] = m[4] - B.m[4];
      A.m[5] = m[5] - B.m[5];
      A.m[6] = m[6] - B.m[6];
      A.m[7] = m[7] - B.m[7];
      A.m[8] = m[8] - B.m[8];
      return A;
    }

    void  CeqthismulB (const Matrix3x3T<T> &B, Matrix3x3T<T> &C) const
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
    Matrix3x3T<T> operator * (const double & r)
    {
      struct Matrix3x3T<T> result;
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

    template <bool b>
    Vector3T<T,b> operator *(const Vector3T<T,b>& v) const
    {
      Vector3T<T,b> vr(m[0]*v[0]+m[1]*v[1]+m[2]*v[2],
                       m[3]*v[0]+m[4]*v[1]+m[5]*v[2],
                       m[6]*v[0]+m[7]*v[1]+m[8]*v[2]);
      return vr;
    }


    /*! Multiplication operator with a vector */
    template <bool b>
    void CeqthismulB( Vector3T<T,b> &B,Vector3T<T,b> &C) const
    {

      C[0] = m[0]*B[0]+m[1]*B[1]+m[2]*B[2];
      C[1] = m[3]*B[0]+m[4]*B[1]+m[5]*B[2];
      C[2] = m[6]*B[0]+m[7]*B[1]+m[8]*B[2];
    }

    /*! Transposition */
    Matrix3x3T<T>& TransposeIt()
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
    Matrix3x3T<T> Transpose() const
    {
      return Matrix3x3T<T> (this->m[0],this->m[3],this->m[6],
                            this->m[1],this->m[4],this->m[7],
                            this->m[2],this->m[5],this->m[8]);
    }

    /*! Transposition */
    void Transpose(Matrix3x3T<T>& A) const
    {
      A.m[0] = m[0];
      A.m[1] = m[3];
      A.m[2] = m[6];
      A.m[3] = m[1];
      A.m[4] = m[4];
      A.m[5] = m[7];
      A.m[6] = m[2];
      A.m[7] = m[5];
      A.m[8] = m[8];
    }

    /*! Inversion */
    void Inversion(struct Matrix3x3T<T> &A) const
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
    void operator += (const Matrix3x3T<T>& B)
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
    void operator -= (const Matrix3x3T<T>& B)
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

    Matrix3x3T<T> operator *(const Matrix3x3T<T>& B) const
    {
      return Matrix3x3T<T>(
               m[0] * B.m[0] + m[1] * B.m[3] + m[2] * B.m[6],
               m[0] * B.m[1] + m[1] * B.m[4] + m[2] * B.m[7],
               m[0] * B.m[2] + m[1] * B.m[5] + m[2] * B.m[8],
               m[3] * B.m[0] + m[4] * B.m[3] + m[5] * B.m[6],
               m[3] * B.m[1] + m[4] * B.m[4] + m[5] * B.m[7],
               m[3] * B.m[2] + m[4] * B.m[5] + m[5] * B.m[8],
               m[6] * B.m[0] + m[7] * B.m[3] + m[8] * B.m[6],
               m[6] * B.m[1] + m[7] * B.m[4] + m[8] * B.m[7],
               m[6] * B.m[2] + m[7] * B.m[5] + m[8] * B.m[8]);
    }


    void operator *=(const Matrix3x3T<T>& B)
    {
      Matrix3x3T<T> temp(*this);

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


    inline friend std::ostream& operator <<(std::ostream &os,Matrix3x3T<T> const &A)
    {
      for (int i=0; i<3; i++)
      {
        for (int j=0; j<3; j++)
          os << A.m[i*3+j] << " ";
        os << std::endl;
      }
      return os;
    }
  };
}

#endif


