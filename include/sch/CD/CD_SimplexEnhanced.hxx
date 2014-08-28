inline CD_SimplexEnhanced::CD_SimplexEnhanced(const Point3& p)
  : CD_Simplex(p)
  , norm1_(p.normsquared())
  , norm2_(0)
  , norm3_(0)
  , norm4_(0)
{
}

inline CD_SimplexEnhanced::CD_SimplexEnhanced(const Point3& p1,const Point3& p2)
  : CD_Simplex(p1,p2)
  , norm1_(p1.normsquared())
  , norm2_(p2.normsquared())
  , norm3_(0)
  , norm4_(0)
{
}

inline CD_SimplexEnhanced::CD_SimplexEnhanced(const Point3& p1,const Point3& p2,const Point3& p3)
  :CD_Simplex(p1,p2,p3)
  , norm1_(p1.normsquared())
  , norm2_(p2.normsquared())
  , norm3_(p3.normsquared())
  , norm4_(0)
{
}

inline CD_SimplexEnhanced::CD_SimplexEnhanced(const Point3& p1,const Point3& p2,const Point3& p3,const Point3& p4)
  :CD_Simplex(p1,p2,p3,p4)
  , norm1_(p1.normsquared())
  , norm2_(p2.normsquared())
  , norm3_(p3.normsquared())
  , norm4_(p4.normsquared())
{
}

inline Scalar& CD_SimplexEnhanced::norms(const char i)
{
  return ((i==0) ? norm1_: (i==1)? norm2_: (i==2) ? norm3_ : norm4_);
}

inline Scalar CD_SimplexEnhanced::norms(const char i) const
{
  return ((i==0) ? norm1_: (i==1)? norm2_: (i==2) ? norm3_ : norm4_);
}

inline Scalar CD_SimplexEnhanced::square_(const Scalar& a)
{
  return a*a;
}

inline Scalar CD_SimplexEnhanced::cube_(const Scalar& a)
{
  return a*a*a;
}

inline void CD_SimplexEnhanced::filter(const CD_SimplexKeptPoints &f)
{

  switch (f.type)
  {
  case CD_None:
    return;

  case CD_Segment:
  {
    type_=CD_Segment;
    Vector3 cache;
    Scalar cache2;
    char a[]= {0,1,2,3};
    char b;

    CD_SimplexExchangeTest<Vector3>(s1_,(*this)[f.b1],cache);
    CD_SimplexExchange<Scalar>(norm1_,norms(f.b1),cache2);
    CD_SimplexExchange<char>(a[0],a[(int)f.b1],b);

    s2_=(*this)[a[(int)(f.b2)]];
    norm2_= norms(a[(int)f.b2]);
    return;
  }
  case CD_Triangle:
  {
    type_=CD_Triangle;
    Vector3 cache;
    Scalar cache2;
    char a[]= {0,1,2,3};
    char b;

    CD_SimplexExchangeTest<Vector3>(s1_,(*this)[f.b1],cache);
    CD_SimplexExchange<Scalar>(norm1_,norms(f.b1),cache2);
    CD_SimplexExchange<char>(a[0],a[(int)f.b1],b);

    CD_SimplexExchangeTest<Vector3>(s2_,(*this)[a[(int)f.b2]],cache);
    CD_SimplexExchange<Scalar>(norm2_,norms(a[(int)f.b2]),cache2);
    CD_SimplexExchange<char>(a[(int)a[1]],a[(int)a[(int)f.b2]],b);

    s3_=(*this)[a[(int)f.b3]];
    norm3_= norms(a[(int)f.b3]);
    return;

  }
  case CD_Point:
  {
    Vector3 cache;
    type_=CD_Point;
    s1_=(*this)[f.b1];
    norm1_= norms(f.b1);
    return;
  }
  default:
  {
    type_=CD_Tetrahedron;
    Vector3 cache;
    Scalar cache2;

    char a[]= {0,1,2,3};
    char b;
    CD_SimplexExchangeTest<Vector3>(s1_,(*this)[f.b1],cache);
    CD_SimplexExchange<Scalar>(norm1_,norms(f.b1),cache2);
    CD_SimplexExchange<char>(a[0],a[(int)f.b1],b);

    CD_SimplexExchangeTest<Vector3>(s2_,(*this)[a[(int)f.b2]],cache);
    CD_SimplexExchange<Scalar>(norm2_,norms(a[(int)f.b2]),cache2);
    CD_SimplexExchange<char>(a[(int)a[1]],a[(int)a[(int)f.b2]],b);

    CD_SimplexExchangeTest<Vector3>(s3_,(*this)[a[(int)f.b3]],cache);
    CD_SimplexExchange<Scalar>(norm3_,norms(a[(int)f.b3]),cache2);
    CD_SimplexExchange<char>(a[(int)a[2]],a[(int)a[(int)f.b3]],b);

    s4_=(*this)[a[(int)f.b4]];
    norm4_= norms(a[(int)f.b4]);
    return ;

  }
  }
}


inline CD_SimplexEnhanced::CD_SimplexEnhanced(const Point3& p,Scalar norm):CD_Simplex(p),norm1_(norm)
{
}

inline CD_SimplexEnhanced::CD_SimplexEnhanced(const Point3& p1,const Point3& p2,Scalar norm1,Scalar norm2):CD_Simplex(p1,p2),norm1_(norm1),norm2_(norm2)
{
}

inline CD_SimplexEnhanced::CD_SimplexEnhanced(const Point3& p1,const Point3& p2,const Point3& p3,Scalar norm1,Scalar norm2,Scalar norm3):CD_Simplex(p1,p2,p3),norm1_(norm1),norm2_(norm2),norm3_(norm3)
{
}

inline CD_SimplexEnhanced::CD_SimplexEnhanced(const Point3& p1,const Point3& p2,const Point3& p3,const Point3& p4,Scalar norm1,Scalar norm2,Scalar norm3,Scalar norm4):CD_Simplex(p1,p2,p3,p4),norm1_(norm1),norm2_(norm2),norm3_(norm3),norm4_(norm4)
{
}



inline CD_SimplexEnhanced& CD_SimplexEnhanced::operator=(const CD_SimplexEnhanced& s)
{
  if (this==&s)
    return *this;

  type_=s.type_;
  switch (type_)
  {

  case CD_Triangle:
    s1_=s.s1_;
    s2_=s.s2_;
    s3_=s.s3_;
    norm1_=s.norm1_;
    norm2_=s.norm2_;
    norm3_=s.norm3_;

    return *this;
  case CD_Segment:
    s1_=s.s1_;
    s2_=s.s2_;
    norm1_=s.norm1_;
    norm2_=s.norm2_;

    return *this;
  case CD_Point:
    s1_=s.s1_;
    norm1_=s.norm1_;

    return *this;
  default:
    s1_=s.s1_;
    s2_=s.s2_;
    s3_=s.s3_;
    s4_=s.s4_;
    norm1_=s.norm1_;
    norm2_=s.norm2_;
    norm3_=s.norm3_;
    norm4_=s.norm4_;

    return *this;
  }
}

inline CD_SimplexEnhanced& CD_SimplexEnhanced::operator+=(const Point3& p)
{

  switch (type_)
  {
  case CD_Point:
    s2_=p;
    norm2_=s2_.normsquared();
    type_=CD_Segment;
    return *this;
  case CD_Segment:
    s3_=p;
    type_=CD_Triangle;
    norm3_=s3_.normsquared();
    return *this;
  default:
    s4_=p;
    type_=CD_Tetrahedron;
    norm4_=s4_.normsquared();
    return *this;
  }
  return *this;


}


inline CD_SimplexEnhanced CD_SimplexEnhanced::operator+(const Point3& p) const
{

  if (type_==CD_Point)
  {
    return CD_SimplexEnhanced(s1_,p);
  }
  else if (type_==CD_Segment)
  {
    return CD_SimplexEnhanced(s1_,s2_,p);
  }
  else if (type_==CD_Triangle)
  {
    return CD_SimplexEnhanced(s1_,s2_,s3_,p);
  }
  return *this;

}


inline Scalar CD_SimplexEnhanced::farthestPointDistance() const

{

  switch (type_)
  {

  case CD_Triangle:
    if (norm1_>norm2_)
    {
      if (norm1_>norm3_)
      {
        return norm1_;
      }
      else
      {
        return norm3_;
      }
    }
    else
    {
      if (norm2_>norm3_)
      {
        return norm2_;
      }
      else
      {
        return norm3_;
      }
    }

  case CD_Segment:

    if (norm1_>norm2_)
    {
      return norm1_;
    }
    else
    {
      return norm2_;
    }


  case CD_Point:
    return norm1_;

  default:
    if (norm1_>norm2_)
    {
      if (norm1_>norm3_)
      {
        if (norm1_>norm4_)
        {
          return norm1_;
        }
        else
        {
          return norm4_;
        }
      }
      else
      {
        if (norm3_>norm4_)
        {
          return norm3_;
        }
        else
        {
          return norm4_;
        }

      }
    }
    else
    {
      if (norm2_>norm3_)
      {
        if (norm2_>norm4_)
        {
          return norm2_;
        }
        else
        {
          return norm4_;
        }
      }
      else
      {
        if (norm3_>norm4_)
        {
          return norm3_;
        }
        else
        {
          return norm4_;
        }

      }
    }


  }

}

inline bool CD_SimplexEnhanced::isAffinelyDependent() const
{
  switch (type_)
  {
  case CD_Segment:
    return ab_.normsquared()<=zero_*farthestPointDistance();
  case CD_Triangle:
  {
    return (ab_^ac_).normsquared()<=square_(zero_*farthestPointDistance());
  }
  case CD_Tetrahedron:
    return square_(fabs(Matrix3x3(ab_,ac_,ad_).determinant()))<=cube_(zero_*farthestPointDistance());
  default:
    return false;
  }
}
