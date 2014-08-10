#include <sch/S_Object/S_Superellipsoid.h>
#include <vector>

using namespace sch;

inline short sign(Scalar i)
{
  return (i>0)? 1:-1;
}

S_Superellipsoid::S_Superellipsoid(Scalar _a, Scalar _b, Scalar _c, Scalar _epsilon1, Scalar _epsilon2):a_(_a),b_(_b),c_(_c),epsilon1_(_epsilon1),epsilon2_(_epsilon2),
  _2_e1on2((2-_epsilon1)/2),_2_e2on2((2-_epsilon2)/2),_2on2_e1(2/(2-_epsilon1)),_2on2_e2(2/(2-_epsilon2))
{
  slices_ = 100;
  stacks_ = 50;

  if (epsilon1_>2||epsilon2_>2||
      epsilon1_<0||epsilon2_<0)
  {
    std::cout<<"SUPERELLIPSOIDS EPSILON1 AND EPSILON2 MUST BE BETWEEN 0 AND 2";
    throw;
  }
}

S_Superellipsoid::~S_Superellipsoid(void)
{
}

Point3 S_Superellipsoid::l_Support(const Vector3& v, int& /*lastFeature*/)const
{
  Scalar anx,bny,cnz;

  anx=a_*fabs(v[0]);
  bny=b_*fabs(v[1]);
  cnz=c_*fabs(v[2]);

  Scalar cp2,sp2,sp2e,cp2e,spe,cpe,
         tt1,tt2,ct2;


  if (anx==0)
  {
    if (bny==0)
    {
      return Point3(0,0,c_*sign(v[2]));
    }
    else
    {
      cp2=0;
      sp2=1;
      cp2e=0;
      sp2e=1;
      cpe=0;
      spe=1;
      tt1=cnz/bny;
    }
  }
  else
  {
    Scalar tp1=bny/anx;
    Scalar tp2=pow(tp1,_2on2_e2);
    cp2=1/(tp2+1);

    if (cp2==1)
    {
      sp2=0;
      cp2e=1;
      sp2e=0;
      cpe=1;
      spe=0;
      tt1=cnz/anx;
    }
    else
    {
      sp2=1-cp2;
      sp2e=pow(sp2,_2_e2on2);
      cp2e=sp2e/tp1;
      spe=sp2/sp2e;
      cpe=cp2/cp2e;
      tt1=cnz*sp2e/bny;
    }
  }

  tt2=pow(tt1,_2on2_e1);
  ct2=1/(tt2+1);

  if (ct2==1)
  {
    return Point3(a_*cpe*sign(v[0]),b_*spe*sign(v[1]),0);
  }
  else
  {
    Scalar st2=1-ct2;
    Scalar st2e=pow(st2,_2_e1on2);
    Scalar ct2e=st2e/tt1;
    Scalar ste=st2/st2e;
    Scalar cte=ct2/ct2e;
    return Point3(a_*cte*cpe*sign(v[0]),
                  b_*cte*spe*sign(v[1]),
                  c_*ste*sign(v[2]));
  }
}

S_Object::S_ObjectType S_Superellipsoid::getType() const
{
  return S_Object::TSuperellipsoid;
}

void S_Superellipsoid::getEllipsoidParameter(
  Scalar & a, Scalar & b, Scalar & c, Scalar & epsilon1, Scalar & epsilon2) const
{
  a=a_;
  b=b_;
  c=c_;
  epsilon1=epsilon1_;
  epsilon2=epsilon2_;
}

