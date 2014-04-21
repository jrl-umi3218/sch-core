#include <sch/CD/CD_SimplexEnhanced.h>

using namespace sch;

inline char sign(Scalar i)
{
  return (i>0)? 1:-1;
}

inline void GetClosestSubSimplexCCKWTriangle(
  const Vector3& AB,const Vector3& AC,
  const Vector3& ABC,const Vector3& AO,
  CD_SimplexKeptPoints &k,
  unsigned char bA,unsigned char bB,unsigned char bC)
{
  if ((ABC^AC)*AO>=0)
  {
    if (AC*AO>=0)
    {
      k.b1=bC;
      k.b2=bA;
      k.type=CD_Segment;
      return;
    }
    else
    {
      if (AB*AO>=0)
      {
        k.b1=bA;
        k.b2=bB;
        k.type=CD_Segment;
        return;

      }
      else
      {
        k.b1=bA;
        k.type=CD_Point;
        return;
      }
    }
  }
  else
  {
    if ((AB^ABC)*AO>=0)
    {
      if (AB*AO>=0)
      {
        k.b1=bA;
        k.b2=bB;
        k.type=CD_Segment;
        return;

      }
      else
      {
        k.b1=bA;
        k.type=CD_Point;
        return;
      }
    }
    else
    {
      k.b1=bB;
      k.b2=bC;
      k.b3=bA;
      k.type=CD_Triangle;
      return;
    }
  }
}

CD_SimplexEnhanced::~CD_SimplexEnhanced(void)
{
}


void CD_SimplexEnhanced::getClosestSubSimplexGJK(CD_SimplexKeptPoints &k) const
{
  switch (type_)
  {

  case (CD_Segment):
  {
    Vector3 AO(-s2_);

    if (ab_*AO>=0)
    {
      k.type=CD_None;
      return;
    }
    else
    {
      k.b1=1;
      k.type=CD_Point;
      return ;
    }
  }
  case (CD_Triangle):
  {
    Vector3 AO(-s3_);
    Vector3 ABC(ab_^ac_);
    if ((ABC^ac_)*AO>=0)
    {
      if (ac_*AO>=0)
      {
        k.b1=1;
        k.b2=2;
        k.type=CD_Segment;
        return ;
      }
      else
      {
        if (ab_*AO>=0)
        {
          k.b1=2;
          k.b2=0;
          k.type=CD_Segment;
          return;

        }
        else
        {
          k.b1=2;
          k.type=CD_Point;
          return;
        }
      }
    }
    else
    {
      if ((ab_^ABC)*AO>=0)
      {
        if (ab_*AO>=0)
        {
          k.b1=2;
          k.b2=0;
          k.type=CD_Segment;
          return;

        }
        else
        {
          k.b1=2;
          k.type=CD_Point;
          return;
        }
      }
      else
      {
        if (ABC*AO>=0)
        {
          k.type=CD_None;
          return;
        }
        else
        {
          k.b1=1;
          k.b2=0;
          k.b3=2;
          k.type=CD_Triangle;
          return;
        }
      }


    }

  }
  case (CD_Tetrahedron):
  {

    Vector3 AO(-s4_);
    Vector3 ABC(ab_^ac_),ACD(ac_^ad_),ADB(ad_^ab_);
    Scalar d_abc(ABC*AO),d_acd(ACD*AO),d_adb(ADB*AO);
    d_abc=(d_abc*d_abc)/ABC.normsquared()*sign(d_abc);
    d_acd=(d_acd*d_acd)/ACD.normsquared()*sign(d_acd);
    d_adb=(d_adb*d_adb)/ADB.normsquared()*sign(d_adb);


    if (d_abc>d_acd)
    {
      if (d_abc>d_adb)
      {
        if (d_abc>=0)
        {
          GetClosestSubSimplexCCKWTriangle(ab_,ac_,ABC,AO,k,3,0,1);
          return;

        }
        else
        {
          k.type=CD_None;
          return ;
        }
      }
      else
      {
        if (d_adb>=0)
        {
          GetClosestSubSimplexCCKWTriangle(ad_,ab_,ADB,AO,k,3,2,0);
          return;
        }
        else
        {
          k.type=CD_None;
          return ;
        }
      }
    }
    else
    {
      if (d_acd>d_adb)
      {
        if (d_acd>=0)
        {
          GetClosestSubSimplexCCKWTriangle(ac_,ad_,ACD,AO,k,3,1,2);
          return;
        }
        else
        {
          k.type=CD_None;
          return ;
        }

      }
      else
      {
        if (d_adb>=0)
        {
          GetClosestSubSimplexCCKWTriangle(ad_,ab_,ADB,AO,k,3,2,0);
          return;
        }
        else
        {
          k.type=CD_None;
          return ;
        }
      }
    }
  }

  default:
  {
    k.type=CD_None;
    return ;
  }
  }

  return ;
}

