#pragma once

namespace CD_Matrix
{
  /*! Quaternion m_x*i + m_y*j + m_z*k+w    */
  template <typename T>
  class QuaternionT :
    private Vector4T<T>
  {
  public:

    QuaternionT<T>()
    {}

    explicit QuaternionT<T>(const T& x, const T& y, const T& z, const T& w):Vector4T<T>(x,y,z,w)
    {}

    template <bool b>
    explicit QuaternionT<T>(const Vector3T<T,b>& axis, const T& angle)
    {
      T d = axis.norm();
      T s = sin(angle * 0.5) / d;
      this->m_x=axis[0] * s;
      this->m_y=axis[1] * s;
      this->m_z=axis[2] * s;
      this->m_w=cos(angle * T(0.5));
    }


    using Vector4T<T>::operator[] ;
    using Vector4T<T>::operator+ ;
    using Vector4T<T>::operator+= ;
    using Vector4T<T>::operator- ;
    using Vector4T<T>::operator-= ;


    const QuaternionT<T>& operator=(const QuaternionT<T>& A)
    {
      this->m_w=A.m_w;
      this->m_x=A.m_x;
      this->m_y=A.m_y;
      this->m_z=A.m_z;
    }

    QuaternionT<T> Conjugate() const
    {
      return QuaternionD(-(this->m_x),-(this->m_y),-(this->m_y),this->m_t);
    }

    void ConjugateIt()
    {
      this->m_x=-this->m_x;
      this->m_y=-this->m_y;
      this->m_z=-this->m_z;
    }

    QuaternionT<T> operator*(const QuaternionT<T>& q )
    {
      return QuaternionD(this->m_w * q[0] + this->m_x * q[3] + this->m_y * q[2] - this->m_z * q[1],
                         this->m_w * q[1] + this->m_y * q[3] + this->m_z * q[0] - this->m_x * q[2],
                         this->m_w * q[2] + this->m_z * q[3] + this->m_x * q[1] - this->m_y * q[0],
                         this->m_w * q[3] - this->m_x * q[0] - this->m_y * q[1] - this->m_z * q[2]);
    }

    QuaternionT<T>& operator*=(const QuaternionT<T>& q )
    {
      T x=this->m_w * q[0] + this->m_x * q[3] + this->m_y * q[2] - this->m_z * q[1],
        y=this->m_w * q[0] + this->m_x * q[3] + this->m_y * q[2] - this->m_z * q[1],
        z=this->m_w * q[0] + this->m_x * q[3] + this->m_y * q[2] - this->m_z * q[1],
        w=this->m_w * q[0] + this->m_x * q[3] + this->m_y * q[2] - this->m_z * q[1];

      this->m_x=x;
      this->m_y=y;
      this->m_z=z;
      this->m_w=w;

      return *this;
    }

    virtual ~QuaternionT(void)
    {
    }
  };
}
