/*! This is a very fast and simple implementation
* of a 3D vector class of double.
*
* (c) Olivier Stasse, JRL, CNRS-AIST, ISRI, 2007
*/

#ifndef _VECTOR3DEFAULT_MAL_DEFAULT_
#define _VECTOR3DEFAULT_MAL_DEFAULT_




namespace CD_Matrix
{


  template <typename T> struct Matrix3x3T;

  template <typename T, bool normOptimization>
  struct Norm
  {
  protected:
    T norm_;
    bool normOutdated_;
  public:
    Norm():normOutdated_(true)
    {
    }

    inline void setNorm(const T& n)
    {
      norm_=n;
      normOutdated_=false;
    }

    inline void outdateNorm()
    {
      normOutdated_=true;
    }

    inline bool normOutdated() const
    {
      return normOutdated_;
    }

    inline T getNorm() const
    {
      return norm_;
    }
  };


  template <typename T>
  struct Norm<T,false>
  {
  public:
    inline void setNorm(const T& n)
    {
    }

    inline T getNorm()const
    {
      return 0;
    }

    inline void outdateNorm()
    {
    }

    inline bool normOutdated() const
    {
      return true;
    }


  };



  /*! Template to handle 3 dimensional vector */
  template <typename T, bool normOptimization>
  struct Vector3T: protected Norm<T,normOptimization>
  {
  public:

    T m_x,m_y,m_z;

    typedef Vector3T< T, normOptimization> Vector;

  public:

    template<class Archive>
    void serialize(Archive & ar, const unsigned int /*version*/)
    {
      ar & m_x;
      ar & m_y;
      ar & m_z;

      Norm<T,normOptimization>::outdateNorm();
    }

    /*! Basic constructor: all the field
    are set to zero. */
    explicit Vector3T():m_x(0.0), m_y(0.0), m_z(0.0)
    {}

    explicit Vector3T(const T& x, const T& y, const T& z):m_x(x),m_y(y),m_z(z)
    {}

    explicit Vector3T(const T* const p): m_x(p[0]),m_y(p[1]), m_z(p[2])
    {
    }

    void Set(const T& x, const T& y, const T& z)
    {
      this->m_x=x;
      this->m_y=y;
      this->m_z=z;

      Norm<T,normOptimization>::outdateNorm();
    }

    void Set(const T* const p)
    {
      this->m_x=p[0];
      this->m_y=p[1];
      this->m_z=p[2];

      Norm<T,normOptimization>::outdateNorm();
    }

    /*! copy constructor */
    template <bool b>
    inline Vector3T (const struct Vector3T<T,b> &v):
      m_x( v.m_x),m_y( v.m_y),m_z( v.m_z)
    {

    }


    /*! Assignement operator */
    template <bool b>
    inline Vector3T operator= (const struct Vector3T<T,b> &v)
    {
      m_x = v.m_x;
      m_y = v.m_y;
      m_z = v.m_z;

      Norm<T,normOptimization>::outdateNorm();
      return *this;
    }

    /*! Unary operator - */
    inline Vector3T operator-() const
    {
      return Vector3T(-m_x, -m_y, -m_z);
    }

    /*! Array operator */
    inline T& operator[](unsigned i)
    {
      Norm<T,normOptimization>::outdateNorm();
      return ((i==0) ? m_x: (i==1)? m_y:m_z);
    }

    /*! Array operator */
    inline const T& operator[](unsigned i) const
    {
      return ((i==0) ? m_x: (i==1)? m_y:m_z);
    }


    /*! Array operator */
    inline T& operator()(unsigned i)
    {
      Norm<T,normOptimization>::outdateNorm();
      return ((i==0) ? m_x: (i==1)? m_y:m_z);
    }

    /*! Binary operator == */
    template <bool b>
    inline bool operator==(const struct Vector3T<T,b> &v) const
    {
      return ((v.m_x==m_x) &&
              (v.m_y==m_y) &&
              (v.m_z==m_z));
    }

    /*! Binary operator + */
    template <bool b>
    inline Vector3T operator+ (const struct Vector3T<T,b> &v) const
    {
      Vector3T vr;
      vr.m_x = m_x + v.m_x;
      vr.m_y = m_y + v.m_y;
      vr.m_z = m_z + v.m_z;
      return vr;
    }

    /*! Binary operator - */
    template <bool b>
    inline Vector3T operator- (const struct Vector3T<T,b> &v) const
    {
      Vector3T vr;
      vr.m_x = m_x - v.m_x;
      vr.m_y = m_y - v.m_y;
      vr.m_z = m_z - v.m_z;
      return vr;
    }

    /*! Binary operator += */
    template <bool b>
    inline void operator+= (const struct Vector3T<T,b> &v)
    {
      Norm<T,normOptimization>::outdateNorm();

      m_x += v.m_x;
      m_y += v.m_y;
      m_z += v.m_z;
    }

    /*! Binary operator -= */
    template <bool b>
    inline void operator-= (const struct Vector3T<T,b> &v)
    {
      Norm<T,normOptimization>::outdateNorm();

      m_x -= v.m_x;
      m_y -= v.m_y;
      m_z -= v.m_z;
    }

    /*! Binary operator * */
    inline Vector3T operator* (const T& t) const
    {
      Vector3T vr;
      vr.m_x = m_x * t;
      vr.m_y = m_y * t;
      vr.m_z = m_z * t;
      return vr;
    }

    /*! Binary operator * : dot product */
    template <bool b>
    inline T operator* (const Vector3T<T,b>& v) const
    {
      return m_x * v.m_x + m_y * v.m_y + m_z * v.m_z ;
    }

    /*! multiplication as a row vector by a left-hand matrix  */
    inline Vector3T operator*(const Matrix3x3T<T>& m)const
    {

      Vector3T vr(m_x*m[0]+m_y*m[3]+m_z*m[6],
                  m_x*m[1]+m_y*m[4]+m_z*m[7],
                  m_x*m[2]+m_y*m[5]+m_z*m[8]);
      return vr;
    }

    inline void operator*=(const Matrix3x3T<T> m)
    {
      Norm<T,normOptimization>::outdateNorm();

      m_x=m_x*m[0]+m_y*m[3]+m_z*m[6];
      m_y=m_x*m[1]+m_y*m[4]+m_z*m[7];
      m_z=m_x*m[2]+m_y*m[5]+m_z*m[8];

    }

    /*! Binary operator / */
    inline Vector3T operator/ (const T &t) const
    {
      Vector3T vr;
      vr.m_x = m_x/t;
      vr.m_y = m_y/t;
      vr.m_z = m_z/t;
      return vr;
    }

    /*! Binary operator *= */
    inline void operator*= (const T &t)
    {
      Norm<T,normOptimization>::outdateNorm();
      m_x = m_x*t;
      m_y = m_y*t;
      m_z = m_z*t;
    }


    /*! Binary operator /= */
    inline void operator/= (const T &t)
    {
      Norm<T,normOptimization>::outdateNorm();
      m_x = m_x/t;
      m_y = m_y/t;
      m_z = m_z/t;
    }


    /*! Normalize . */
    inline void normalize()
    {
      Norm<T,normOptimization>::outdateNorm();
      T in = static_cast<T> (1.0/sqrt(m_x*m_x+m_y*m_y+m_z*m_z));
      m_x *= in;
      m_y *= in;
      m_z *= in;
    }

    /*! Get the norm. */
    inline T norm()  const
    {
      return static_cast<T>(sqrt(m_x*m_x+m_y*m_y+m_z*m_z));
    }

    /*! Get the norm. */
    inline T optimizedNorm()
    {
      if (normOptimization)
      {
        if (Norm<T,normOptimization>::normOutdated())
          setNorm(static_cast<T>(sqrt(m_x*m_x+m_y*m_y+m_z*m_z)));
        return Norm<T,normOptimization>::getNorm();
      }
      else
        return static_cast<T>(sqrt(m_x*m_x+m_y*m_y+m_z*m_z));
    }


    /*! Get the norm squared */
    inline T normsquared() const
    {
      return (m_x*m_x+m_y*m_y+m_z*m_z);
    }

    inline bool IsZero() const
    {
      return ((m_x == 0) && (m_y == 0) && (m_z == 0));
    }

    /*! Cross product */
    template <bool b>
    inline Vector3T operator^ (const Vector3T<T, b>& v2) const
    {
      struct Vector3T vr;
      vr.m_x = m_y*v2.m_z - v2.m_y*m_z;
      vr.m_y = m_z*v2.m_x - v2.m_z*m_x;
      vr.m_z = m_x*v2.m_y - v2.m_x*m_y;
      return vr;
    }

    inline friend std::ostream& operator<<
    (std::ostream &os,Vector3T<T,normOptimization> const &v)
    {
      os << v.m_x << " " << v.m_y << " " << v.m_z << " ";
      return os;
    }
  };
}


#endif /* _VECTOR3D_PATTERNGENERATOR_JRL_ */
