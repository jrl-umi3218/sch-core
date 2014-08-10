

inline CD_Simplex::CD_Simplex(const Point3& p):type_(CD_Point),s1_(p)
{
}

inline CD_Simplex::CD_Simplex(const Point3& p1,const Point3& p2):type_(CD_Segment),s1_(p1),s2_(p2)
{
}

inline CD_Simplex::CD_Simplex(const Point3& p1,const Point3& p2,const Point3& p3):type_(CD_Triangle),s1_(p1),s2_(p2),s3_(p3)
{
}

inline CD_Simplex::CD_Simplex(const Point3& p1,const Point3& p2,const Point3& p3,const Point3& p4):type_(CD_Tetrahedron),s1_(p1),s2_(p2),s3_(p3),s4_(p4)
{
}


template <typename T>
inline void CD_SimplexExchangeTest(T &a,T &b,T &c)
{
  if (&a!=&b)
  {
    c=a;
    a=b;
    b=c;
  }
}

template <typename T>
inline void CD_SimplexExchange(T &a,T &b,T &c)
{
  c=a;
  a=b;
  b=c;
}


inline const Vector3& CD_Simplex::AB() const
{
  return ab_;
}

inline const Vector3& CD_Simplex::AC() const
{
  return ac_;
}

inline const Vector3& CD_Simplex::AD() const
{
  return ad_;
}




inline void CD_Simplex::updateVectors()
{
  switch (type_)
  {
  case CD_Tetrahedron:
  {
    ab_=s1_-s4_;
    ac_=s2_-s4_;
    ad_=s3_-s4_;
    return;
  }
  case CD_Segment:
    ab_=s1_-s2_;
    return;
  case CD_Triangle:
  {
    ab_=s1_-s3_;
    ac_=s2_-s3_;
    return;
  }

  default:
    return;
  }

}


inline CD_SimplexType CD_Simplex::getType() const
{
  return type_;

}



inline Point3& CD_Simplex::operator[](unsigned char i)
{
  return ((i==0) ? s1_: (i==1)? s2_: (i==2) ? s3_ : s4_);
}


inline const Point3& CD_Simplex:: operator[](unsigned char i) const
{
  return ((i==0) ? s1_: (i==1)? s2_: (i==2) ? s3_ : s4_);
}

inline CD_Simplex& CD_Simplex::operator=(const CD_Simplex& s)
{
  type_=s.type_;
  switch (type_)
  {
  case CD_Triangle:
    s1_=s.s1_;
    s2_=s.s2_;
    s3_=s.s3_;
    ab_ = s.ab_;
    ac_ = s.ac_;
    return *this;
  case CD_Segment:
    s1_=s.s1_;
    s2_=s.s2_;
    ab_ = s.ab_;
    return *this;
  case CD_Point:
    s1_=s.s1_;
    return *this;
  default:
    s1_=s.s1_;
    s2_=s.s2_;
    s3_=s.s3_;
    s4_=s.s4_;
    ab_ = s.ab_;
    ac_ = s.ac_;
    ad_ = s.ad_;
    return *this;
  }
}


inline CD_Simplex& CD_Simplex::operator=(const Point3& p)
{
  type_=CD_Point;
  s1_=p;
  return *this;
}


inline bool CD_Simplex::operator==(const CD_Simplex& s)
{
  if (type_!=s.type_)
    return false;
  switch (type_)
  {
  case CD_Triangle:
    return (s1_==s.s1_)&&(s2_==s.s2_)&&(s3_==s.s3_);
  case CD_Segment:
    return (s1_==s.s1_)&&(s2_==s.s2_);
  case CD_Point:
    return (s1_==s.s1_);
  default:
    return (s1_==s.s1_)&&(s2_==s.s2_)&&(s3_==s.s3_)&&(s4_==s.s4_);
  }
}



inline bool CD_Simplex::operator!=(const CD_Simplex& s)
{
  return !((*this)==s);
}

inline CD_Simplex& CD_Simplex::operator+=(const Point3& p)
{

  switch (type_)
  {
  case CD_Point:
    s2_=p;
    type_=CD_Segment;
    return *this;
  case CD_Segment:
    s3_=p;
    type_=CD_Triangle;
    return *this;
  default:
    s4_=p;
    type_=CD_Tetrahedron;
    return *this;
  }
  return *this;


}


inline CD_Simplex CD_Simplex::operator+(const Point3& p) const
{

  if (type_==CD_Point)
  {
    return CD_Simplex(s1_,p);
  }
  else if (type_==CD_Segment)
  {
    return CD_Simplex(s1_,s2_,p);
  }
  else if (type_==CD_Triangle)
  {
    return CD_Simplex(s1_,s2_,s3_,p);
  }
  return *this;

}

inline void CD_Simplex::filter(const CD_SimplexKeptPoints &f)
{

  switch (f.type)
  {
  case CD_None:
    return;

  case CD_Segment:
  {
    type_=CD_Segment;
    Vector3 cache;
    char a[]= {0,1,2,3};
    char b;
    CD_SimplexExchangeTest<Vector3>(s1_,(*this)[f.b1],cache);
    CD_SimplexExchange<char>(a[0],a[(int)f.b1],b);

    s2_=(*this)[a[(int)f.b2]];
    return;
  }
  case CD_Triangle:
  {
    type_=CD_Triangle;
    Vector3 cache;
    char a[]= {0,1,2,3};
    char b;
    CD_SimplexExchangeTest<Vector3>(s1_,(*this)[(int)f.b1],cache);
    CD_SimplexExchange<char>(a[0],a[(int)f.b1],b);

    CD_SimplexExchangeTest<Vector3>(s2_,(*this)[a[(int)f.b2]],cache);
    CD_SimplexExchange<char>(a[(int)a[1]],a[(int)a[(int)f.b2]],b);

    s3_=(*this)[a[(int)f.b3]];
    return;

  }
  case CD_Point:
  {
    Vector3 cache;
    type_=CD_Point;
    s1_=(*this)[(int)f.b1];
    return;
  }
  default:
  {
    type_=CD_Tetrahedron;
    Vector3 cache;
    char a[]= {0,1,2,3};
    char b;
    CD_SimplexExchangeTest<Vector3>(s1_,(*this)[(int)f.b1],cache);
    CD_SimplexExchange<char>(a[0],a[(int)f.b1],b);

    CD_SimplexExchangeTest<Vector3>(s2_,(*this)[a[(int)f.b2]],cache);
    CD_SimplexExchange<char>(a[(int)a[1]],a[(int)a[(int)f.b2]],b);

    CD_SimplexExchangeTest<Vector3>(s3_,(*this)[a[(int)f.b3]],cache);
    CD_SimplexExchange<char>(a[(int)a[2]],a[(int)a[(int)f.b3]],b);

    s4_=(*this)[a[(int)f.b4]];
    return ;
  }
  }
}

inline Scalar CD_Simplex::squareDistanceAtOrigin(const Vector3 &v)const
{
  switch (type_)
  {
  case CD_Point:
    return s1_.normsquared();

  default:
    Scalar d(v*s2_);
    return d*d/v.normsquared();

  }

}
