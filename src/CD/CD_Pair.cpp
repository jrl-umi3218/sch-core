#include <sch/CD/CD_Pair.h>
#include <sch/CD/CD_Simplex.h>
#include <sch/CD/CD_SimplexEnhanced.h>

#include <iostream>

//#ifndef NOGLUT
//#define SHOW_LAST_SIMLPEX
//#endif

//#define CD_SAFE_VERSION //use when the scalar has a perfect precision
#define PENETRATION_DEPTH
//#define CD_PAIR_VERBOUS_MODE
//#define CD_ITERATION_LIMIT 50 //use when the real-time constraints are too high fo current performances while keeping the same global precision.
//no theoretical guarantee on the precision nor the collision-safeness when used - Default value is 20


#define _EPSILON_ 1e-24
#define _PRECISION_ 1e-6

using namespace sch;

inline Vector3 LinearSystem(Matrix3x3& A, Vector3& y)
{
  Matrix3x3 B;
  A.Inversion(B);
  return (B*y);
}


CD_Pair::CD_Pair(S_Object *obj1, S_Object *obj2):sObj1_(obj1),sObj2_(obj2),lastDirection_(1.0,0.0,0.0),
  lastFeature1_(-1),lastFeature2_(-1),distance_(0),stamp1_(sObj1_->checkStamp()),stamp2_(sObj2_->checkStamp()),
  precision_(_PRECISION_),epsilon_(_EPSILON_),witPointsAreComputed_(false),s1_(Point3()),s2_(Point3()),s_(Point3()),sp_(Point3()),depthPair(obj1,obj2)
{
  --stamp1_;
  --stamp2_;

  depthPair.setRelativePrecision(_PRECISION_);
  depthPair.setEpsilon(_EPSILON_);
}


CD_Pair::~CD_Pair(void)
{
}

Scalar CD_Pair::getDistance()
{
  if ((stamp1_==sObj1_->checkStamp())&&(stamp2_==sObj2_->checkStamp()))
  {
    if (distance_==0)
      penetrationDepth();
    return distance_;
  }
  else
  {
    stamp1_=sObj1_->checkStamp();
    stamp2_=sObj2_->checkStamp();
    GJK();
    penetrationDepth();
    return distance_;
  }
}

Scalar CD_Pair::getDistanceWithoutPenetrationDepth()
{
  if ((stamp1_==sObj1_->checkStamp())&&(stamp2_==sObj2_->checkStamp()))
  {
    if (distance_ > 0)
      return distance_;
    return 0;
  }
  else
  {
    stamp1_=sObj1_->checkStamp();
    stamp2_=sObj2_->checkStamp();
    GJK();
    return distance_;
  }
}



Scalar CD_Pair::reComputeClosestPoints(Point3& p1,Point3& p2)
{
  stamp1_=sObj1_->checkStamp();
  stamp2_=sObj2_->checkStamp();
  GJK();
  penetrationDepth();
  witPoints(p1,p2);
  return distance_;
}


void CD_Pair::setRelativePrecision(Scalar s)
{
  --stamp1_;
  --stamp2_;
  precision_=s*s;
  depthPair.setRelativePrecision(s);
}

void CD_Pair::setEpsilon(Scalar s)
{
  --stamp1_;
  --stamp2_;
  epsilon_=s;
  depthPair.setEpsilon(s);
}

Scalar CD_Pair::getClosestPoints(Point3 &p1, Point3 &p2)
{
  if ((stamp1_==sObj1_->checkStamp())&&(stamp2_==sObj2_->checkStamp()))
  {
    if (!witPointsAreComputed_)
    {
      witPointsAreComputed_=true;
      witPoints(p1,p2);
    }
    p1=p1_;
    p2=p2_;
    return distance_;
  }
  else
  {
    stamp1_=sObj1_->checkStamp();
    stamp2_=sObj2_->checkStamp();
    GJK();
    penetrationDepth();
    witPoints(p1,p2);
    witPointsAreComputed_=true;
    return distance_;
  }
}


Scalar CD_Pair::penetrationDepth()
{
#ifdef PENETRATION_DEPTH
  if (collision_)//Objects are in collision
  {
    distance_=-depthPair.getPenetrationDepth(lastDirection_,p1_,p2_,sp_,s1_,s2_);
    if (distance_<0)
    {
      lastDirection_.Set(0,1,0);
    }

    return distance_;
  }
  else
  {
    return distance_;
  }
#else
  return distance_;
#endif
}

Scalar CD_Pair::GJK()
{
  Vector3& v=lastDirection_;

#ifdef CD_PAIR_VERBOUS_MODE
  std::cout<<"#####GJK START######"<<std::endl;
#endif

  witPointsAreComputed_=false;

  int& lf1=lastFeature1_;
  int& lf2=lastFeature2_;

  Point3 sup1=sObj1_->support(v,lf1);
  Point3 sup2=sObj2_->support(-v,lf2);



#ifdef CD_PAIR_VERBOUS_MODE
  std::cout<<"Last features"<<lf1<<" "<<lf2<<std::endl;
#endif

  Point3 sup(sup1);

  sup-=sup2;

  CD_Simplex s1(sup1),s2(sup2),s(sup);

  sp_=sup;

  CD_SimplexKeptPoints k;

  projectionComputed_=false;

  bool cont=true;
  bool useLastSimplex=true;

  Point3 proj;

  Vector3 S01;
  Vector3 S02;

  Scalar a1,a2,a3,a4,a5,a6;

  distance_=infinity;

#ifdef CD_ITERATION_LIMIT
  int	cnt=0;
#endif

  while (cont)
  {

#ifdef CD_ITERATION_LIMIT

    if (++cnt>CD_ITERATION_LIMIT)
      break;		//the iterations number limit has been reached
#endif

    switch (s.getType())
    {

    case CD_Triangle:
    {
      S01=s[1];
      S01-=s[2];
      S02=s[0];
      S02-=s[2];
      a1=S01*s[0],a2=S01*s[1],a3=S01*s[2],a4=S02*s[0],a5=S02*s[1],a6=S02*s[2];

      lambda0_=a2*a6-a3*a5;
      lambda1_=a3*a4-a1*a6;
      lambda2_=a1*a5-a2*a4;
      det_=1/(lambda0_+lambda1_+lambda2_);
      lambda0_*=det_;
      lambda1_*=det_;
      lambda2_*=det_;

      proj=s[0]*lambda0_+s[1]*lambda1_+s[2]*lambda2_;
      break;
    }

    case CD_Segment:
    {
      S01=s[1];
      S01-=s[0];

      lambda0_=S01*s[1];
      lambda1_=-(S01*s[0]);
      det_=1/(lambda0_+lambda1_);
      lambda0_*=det_;
      lambda1_*=det_;

      proj=s[0]*lambda0_+s[1]*lambda1_;
      break;
    }
    default:
    {
      proj=s[0];
    }

    }
    Scalar newdist=proj.normsquared();

    if (distance_ <= newdist) //the distance is not monotonous
    {
      cont=false;
      useLastSimplex=false;
    }
    else
    {
      v=-proj;
      distance_= newdist;

      s_=s;
      s1_=s1;
      s2_=s2;

      if ( distance_<=sp_.farthestPointDistance()*epsilon_)//v is considered zero
      {
        collision_=true;
        cont=false;
      }
      else
      {
        sup1=sObj1_->support(v,lf1);
        sup2=sObj2_->support(-v,lf2);

#ifdef CD_PAIR_VERBOUS_MODE

        std::cout<<"Last features"<<lf1<<" "<<lf2<<std::endl;
        std::cout<<"supports"<<sup1<<" "<<sup2<<std::endl;
#	ifdef CD_ITERATION_LIMIT
        std::cout<<"Iterations"<<cnt<<std::endl;
#	endif
#endif

        sup=sup1;
        sup-=sup2;

        if ((distance_-proj*sup)<(precision_*distance_))//precision reached
        {
          collision_=false;
          cont=false;
          projectionComputed_=true;
        }
        else
        {
          sp_+=sup;
          sp_.updateVectors();
#ifndef SAFE_VERSION
          if (sp_.isAffinelyDependent())
          {
            cont=false;
            collision_=false;
            projectionComputed_=true;
          }
          else
#endif
          {
            sp_.getClosestSubSimplexGJK(k);
            sp_.filter(k);
            s1+=sup1;
            s2+=sup2;

            if (sp_.getType()==CD_Tetrahedron)
            {
              cont=false;
              s1+=sup1;
              s2+=sup2;
              collision_=true;
              distance_=0.;
            }
            else
            {
              s=sp_;
              s1.filter(k);
              s2.filter(k);
            }
          }
        }
      }
    }
  }


#ifdef CD_PAIR_VERBOUS_MODE
  std::cout<<"#####GJK END######"<<std::endl;
#endif

  if (useLastSimplex)
  {
    s_=s;
    s1_=s1;
    s2_=s2;
  }

  return distance_;


}

void CD_Pair::setVector(const Vector3 &v)
{
  lastDirection_=v;
}

void CD_Pair::witPoints(Point3 &p1, Point3 &p2)
{
  Point3 proj;
  Vector3& v=lastDirection_;

  if (collision_)
  {
    p1=p1_;
    p2=p2_;
    return;

  }

  switch (s_.getType())
  {

  case CD_Triangle:
  {

    {
      if (!projectionComputed_)
      {
        Vector3 S01(s_[1]-s_[2]), S02(s_[0]-s_[2]);

        Scalar a1=S01*s_[0],a2=S01*s_[1],a3=S01*s_[2],a4=S02*s_[0],a5=S02*s_[1],a6=S02*s_[2];

        lambda0_=a2*a6-a3*a5;
        lambda1_=a3*a4-a1*a6;
        lambda2_=a1*a5-a2*a4;
        det_=1/(lambda0_+lambda1_+lambda2_);

        lambda0_*=det_;
        lambda1_*=det_;
        lambda2_*=det_;
        proj=s_[0]*lambda0_+s_[1]*lambda1_+s_[2]*lambda2_;
        v=-proj;
      }

      p1_=p1=s1_[0]*lambda0_+s1_[1]*lambda1_+s1_[2]*lambda2_;
      p2_=p2=s2_[0]*lambda0_+s2_[1]*lambda1_+s2_[2]*lambda2_;
    }

#ifdef SHOW_LAST_SIMLPEX
    glDisable(GL_DEPTH_TEST);
    glColor4d(0,0.5,1,0.5);
    glBegin(GL_TRIANGLES);
    glVertex3d(s1_[0][0],s1_[0][1],s1_[0][2]);
    glVertex3d(s1_[1][0],s1_[1][1],s1_[1][2]);
    glVertex3d(s1_[2][0],s1_[2][1],s1_[2][2]);

    glVertex3d(s2_[0][0],s2_[0][1],s2_[0][2]);
    glVertex3d(s2_[1][0],s2_[1][1],s2_[1][2]);
    glVertex3d(s2_[2][0],s2_[2][1],s2_[2][2]);


    glEnd();

    glEnable(GL_DEPTH_TEST);
#endif

    return;
  }

  case CD_Segment:
  {
    if (!projectionComputed_)
    {
      Vector3 S01(s_[1]-s_[0]);

      lambda1_=-(S01*s_[0]);
      lambda0_=S01*s_[1];

      det_=1/(lambda0_+lambda1_);

      lambda0_*=det_;
      lambda1_*=det_;

      proj=s_[0]*lambda0_+s_[1]*lambda1_;
      v=-proj;
    }

    p1_=p1=s1_[0]*lambda0_+s1_[1]*lambda1_;
    p2_=p2=s2_[0]*lambda0_+s2_[1]*lambda1_;

#ifdef SHOW_LAST_SIMLPEX

    glDisable(GL_DEPTH_TEST);
    glColor4d(0,0.5,1,0.5);
    glBegin(GL_LINES);
    glVertex3d(s1_[0][0],s1_[0][1],s1_[0][2]);
    glVertex3d(s1_[1][0],s1_[1][1],s1_[1][2]);


    glVertex3d(s2_[0][0],s2_[0][1],s2_[0][2]);
    glVertex3d(s2_[1][0],s2_[1][1],s2_[1][2]);

    glEnd();

    glEnable(GL_DEPTH_TEST);


#endif
    return ;
  }
  default:
  {
    p1_=p1=s1_[0];
    p2_=p2=s2_[0];

    return ;
  }
  }
}


bool CD_Pair::isInCollision()
{
  if ((stamp1_==sObj1_->checkStamp())&&(stamp2_==sObj2_->checkStamp()))
  {
    return collision_;
  }
  else
  {
    Scalar prec=precision_;
    precision_=1;
    GJK();
    precision_=prec;
    return collision_;
  }
}

