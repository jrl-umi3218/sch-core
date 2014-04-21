#include <sch/CD_Penetration/CD_Depth.h>
#include <sch/CD_Penetration/DT_TriEdge.h>
#include <algorithm>

#define _EPSILON_ 1e-24
#define _PRECISION_ 1e-6


using namespace sch;

const int       MaxSupportPoints = 100;
const int       MaxFacets         = 200;

class TriangleComp
{
public:

  bool operator()(const  Depth_Triangle *face1, const  Depth_Triangle *face2)
  {
    return face1->getDist2() > face2->getDist2();
  }
} triangleComp;

struct TriangleHeap
{
  TriangleHeap()
    : num_triangles(0)
  {}

  Depth_Triangle* first() const
  {
    return triangleHeap[0];
  }

  Depth_Triangle* last() const
  {
    return triangleHeap[num_triangles];
  }

  void pop()
  {
    std::pop_heap(&triangleHeap[0], &triangleHeap[num_triangles], triangleComp);
    --num_triangles;
  }

  void addCandidate(Depth_Triangle *triangle, Scalar upper2)
  {
    if (triangle->isClosestInternal() && triangle->getDist2() <= upper2)
    {
      triangleHeap[num_triangles++] = triangle;
      std::push_heap(&triangleHeap[0], &triangleHeap[num_triangles], triangleComp);
#ifdef sch_DEBUG
      std::cout << " accepted" << std::endl;
#endif
    }
    else
    {
#ifdef sch_DEBUG
      std::cout << " rejected, ";
      if (!triangle->isClosestInternal())
      {
        std::cout << "closest point not internal";
      }
      else
      {
        std::cout << "triangle is further than upper bound";
      }
      std::cout << std::endl;
#endif
    }
  }

  Depth_Triangle *triangleHeap[MaxFacets];
  int  num_triangles;
};


int furthestAxis(Vector3 v)
{
  Vector3 vp(fabs(v[0]),fabs(v[1]),fabs(v[2]));

  return vp[0] < vp[1] ? (vp[0] < vp[2] ? 0 : 2) : (vp[1] < vp[2] ? 1 : 2);

}

inline int originInTetrahedron(const Vector3& p1, const Vector3& p2,
                               const Vector3& p3, const Vector3& p4)
{
  Vector3 normal1 = (p2 - p1)^( p3 - p1);
  if (((normal1* p1) >= Scalar(0.0)) == ((normal1* p4) > Scalar(0.0)))
  {
    return 4;
  }

  Vector3 normal2 = (p4 - p2)^( p3 - p2);
  if (((normal2* p2) >= Scalar(0.0)) == ((normal2* p1) > Scalar(0.0)))
  {
    return 1;
  }

  Vector3 normal3 = (p4 - p3)^( p1 - p3);
  if (((normal3* p3) >= Scalar(0.0)) == ((normal3* p2) > Scalar(0.0)))
  {
    return 2;
  }

  Vector3 normal4 = (p2 - p4)^( p1 - p4);
  if (((normal4* p4) >= Scalar(0.0)) == ((normal4* p3) > Scalar(0.0)))
  {
    return 3;
  }

  return 0;
}


template <class T>
inline void GEN_set_min(T& a, const T& b)
{
  if (b < a)
  {
    a = b;
  }
}

template <class T>
inline const T& GEN_max(const T& a, const T& b)
{
  return  a < b ? b : a;
}


CD_Depth::~CD_Depth(void)
{
}



Scalar CD_Depth::getPenetrationDepth(Vector3& v, Point3 &p1,  Point3 &p2,const CD_SimplexEnhanced& s,
                                     const CD_Simplex& s1_, const CD_Simplex& s2_)
{
  Point3  pBuf[MaxSupportPoints];
  Point3  qBuf[MaxSupportPoints];
  Vector3 yBuf[MaxSupportPoints];
  TriangleHeap tHeap;

  int num_verts;

  switch (s.getType())
  {
  case CD_Point:
    pBuf[0]=s1_[0];
    qBuf[0]=s2_[0];
    yBuf[0]=s[0];
    num_verts=1;
    break;
  case CD_Segment:
    pBuf[0]=s1_[0];
    qBuf[0]=s2_[0];
    yBuf[0]=s[0];
    pBuf[1]=s1_[1];
    qBuf[1]=s2_[1];
    yBuf[1]=s[1];
    num_verts=2;
    break;
  case CD_Triangle:
    pBuf[0]=s1_[0];
    qBuf[0]=s2_[0];
    yBuf[0]=s[0];
    pBuf[1]=s1_[1];
    qBuf[1]=s2_[1];
    yBuf[1]=s[1];
    pBuf[2]=s1_[2];
    qBuf[2]=s2_[2];
    yBuf[2]=s[2];
    num_verts=3;
    break;
  default:
    pBuf[0]=s1_[0];
    qBuf[0]=s2_[0];
    yBuf[0]=s[0];
    pBuf[1]=s1_[1];
    qBuf[1]=s2_[1];
    yBuf[1]=s[1];
    pBuf[2]=s1_[2];
    qBuf[2]=s2_[2];
    yBuf[2]=s[2];
    pBuf[3]=s1_[3];
    qBuf[3]=s2_[3];
    yBuf[3]=s[3];
    num_verts=4;

  }

  Depth_TriangleStore triangleStore;

  switch (num_verts)
  {
  case 1:
    // Touching contact. Yes, we have a collision,
    // but no penetration.
    return 0;
  case 2:
  {
    // We have a line segment inside the Minkowski sum containing the
    // origin. Blow it up by adding three additional support points.

    Vector3 dir  = yBuf[1] - yBuf[0];

    dir /= dir.norm();
    int        axis = furthestAxis(dir);

    static const Scalar sin_60 = sqrt(Scalar(3.0)) * Scalar(0.5);

    Quaternion rot(dir[0] * sin_60, dir[1] * sin_60, dir[2] * sin_60, Scalar(0.5));
    Matrix3x3 rot_mat(rot);

    Vector3 aux1 = dir ^ Vector3(axis == 0, axis == 1, axis == 2);
    Vector3 aux2 = rot_mat * aux1;
    Vector3 aux3 = rot_mat * aux2;

    pBuf[2] = sObj1_->support(aux1);
    qBuf[2] = sObj2_->support(-aux1);
    yBuf[2] = pBuf[2] - qBuf[2];

    pBuf[3] = sObj1_->support(aux2);
    qBuf[3] = sObj2_->support(-aux2);
    yBuf[3] = pBuf[3] - qBuf[3];

    pBuf[4] = sObj1_->support(aux3);
    qBuf[4] = sObj2_->support(-aux3);
    yBuf[4] = pBuf[4] - qBuf[4];

    if (originInTetrahedron(yBuf[0], yBuf[2], yBuf[3], yBuf[4]) == 0)
    {
      pBuf[1] = pBuf[4];
      qBuf[1] = qBuf[4];
      yBuf[1] = yBuf[4];
    }
    else if (originInTetrahedron(yBuf[1], yBuf[2], yBuf[3], yBuf[4]) == 0)
    {
      pBuf[0] = pBuf[4];
      qBuf[0] = qBuf[4];
      yBuf[0] = yBuf[4];
    }
    else
    {
      // Origin not in initial polytope
      return false;
    }

    num_verts = 4;

  }
  // Fall through allowed!!
  case 4:
  {
    int bad_vertex = originInTetrahedron(yBuf[0], yBuf[1], yBuf[2], yBuf[3]);

    if (bad_vertex == 0)
    {
      Depth_Triangle *f0 = triangleStore.newTriangle(yBuf, 0, 1, 2);
      Depth_Triangle *f1 = triangleStore.newTriangle(yBuf, 0, 3, 1);
      Depth_Triangle *f2 = triangleStore.newTriangle(yBuf, 0, 2, 3);
      Depth_Triangle *f3 = triangleStore.newTriangle(yBuf, 1, 3, 2);

      if (!(f0 && f0->getDist2() > Scalar(0.0) &&
            f1 && f1->getDist2() > Scalar(0.0) &&
            f2 && f2->getDist2() > Scalar(0.0) &&
            f3 && f3->getDist2() > Scalar(0.0)))
      {
        return 0;
      }

      link(Depth_Edge(f0, 0), Depth_Edge(f1, 2));
      link(Depth_Edge(f0, 1), Depth_Edge(f3, 2));
      link(Depth_Edge(f0, 2), Depth_Edge(f2, 0));
      link(Depth_Edge(f1, 0), Depth_Edge(f2, 2));
      link(Depth_Edge(f1, 1), Depth_Edge(f3, 0));
      link(Depth_Edge(f2, 1), Depth_Edge(f3, 1));

      tHeap.addCandidate(f0, infinity);
      tHeap.addCandidate(f1, infinity);
      tHeap.addCandidate(f2, infinity);
      tHeap.addCandidate(f3, infinity);
      break;
    }

    if (bad_vertex < 4)
    {
      pBuf[bad_vertex - 1] = pBuf[4];
      qBuf[bad_vertex - 1] = qBuf[4];
      yBuf[bad_vertex - 1] = yBuf[4];

    }

    num_verts = 3;

  }
  // Fall through allowed!!
  case 3:
  {
    // We have a triangle inside the Minkowski sum containing
    // the origin. First blow it up.

    Vector3 v1     = yBuf[1] - yBuf[0];
    Vector3 v2     = yBuf[2] - yBuf[0];
    Vector3 vv     = (v1^ v2);

    pBuf[3] = sObj1_->support(vv);
    qBuf[3] = sObj2_->support(-vv);
    yBuf[3] = pBuf[3] - qBuf[3];
    pBuf[4] = sObj1_->support(-vv);
    qBuf[4] = sObj2_->support(vv);
    yBuf[4] = pBuf[4] - qBuf[4];

    Depth_Triangle* f0 = triangleStore.newTriangle(yBuf, 0, 1, 3);
    Depth_Triangle* f1 = triangleStore.newTriangle(yBuf, 1, 2, 3);
    Depth_Triangle* f2 = triangleStore.newTriangle(yBuf, 2, 0, 3);
    Depth_Triangle* f3 = triangleStore.newTriangle(yBuf, 0, 2, 4);
    Depth_Triangle* f4 = triangleStore.newTriangle(yBuf, 2, 1, 4);
    Depth_Triangle* f5 = triangleStore.newTriangle(yBuf, 1, 0, 4);

    if (!(f0 && f0->getDist2() > Scalar(0.0) &&
          f1 && f1->getDist2() > Scalar(0.0) &&
          f2 && f2->getDist2() > Scalar(0.0) &&
          f3 && f3->getDist2() > Scalar(0.0) &&
          f4 && f4->getDist2() > Scalar(0.0) &&
          f5 && f5->getDist2() > Scalar(0.0)))
    {
      return 0;
    }

    link(Depth_Edge(f0, 1), Depth_Edge(f1, 2));
    link(Depth_Edge(f1, 1), Depth_Edge(f2, 2));
    link(Depth_Edge(f2, 1), Depth_Edge(f0, 2));

    link(Depth_Edge(f0, 0), Depth_Edge(f5, 0));
    link(Depth_Edge(f1, 0), Depth_Edge(f4, 0));
    link(Depth_Edge(f2, 0), Depth_Edge(f3, 0));

    link(Depth_Edge(f3, 1), Depth_Edge(f4, 2));
    link(Depth_Edge(f4, 1), Depth_Edge(f5, 2));
    link(Depth_Edge(f5, 1), Depth_Edge(f3, 2));

    tHeap.addCandidate(f0, infinity);
    tHeap.addCandidate(f1, infinity);
    tHeap.addCandidate(f2, infinity);
    tHeap.addCandidate(f3, infinity);
    tHeap.addCandidate(f4, infinity);
    tHeap.addCandidate(f5, infinity);

    num_verts = 5;
  }
  break;
  }

  // We have a polytope inside the Minkowski sum containing
  // the origin.

  if (tHeap.num_triangles == 0)
  {
    return 0;
  }

  // at least one triangle on the heap.

  Depth_Triangle *triangle = 0;

  Scalar upper_bound2 = infinity;

  do
  {
    triangle = tHeap.first();
    tHeap.pop();

    if (!triangle->isObsolete())
    {
      if (num_verts == MaxSupportPoints)
      {
#ifdef sch_DEBUG
        std::cout << "Ouch, no convergence!!!" << std::endl;
#endif
        assert(false);
        break;
      }

      pBuf[num_verts] = sObj1_->support( triangle->getClosest());
      qBuf[num_verts] = sObj2_->support(-triangle->getClosest());
      yBuf[num_verts] = pBuf[num_verts] - qBuf[num_verts];

      int index = num_verts++;
      Scalar far_dist = (yBuf[index]* triangle->getClosest());

      // Make sure the support mapping is OK.
      if (far_dist < Scalar(0.0))
      {
        break;
      }
      Scalar far_dist2 = far_dist * far_dist / triangle->getDist2();
      GEN_set_min(upper_bound2, far_dist2);

      Scalar error = far_dist - triangle->getDist2();
      if (error <= GEN_max(precision_ * far_dist, epsilon_)
#if 1
          || yBuf[index] == yBuf[(*triangle)[0]]
          || yBuf[index] == yBuf[(*triangle)[1]]
          || yBuf[index] == yBuf[(*triangle)[2]]
#endif
         )
      {
        break;
      }


      // Compute the silhouette cast by the new vertex
      // Note that the new vertex is on the positive side
      // of the current triangle, so the current triangle will
      // not be in the convex hull. Start local search
      // from this triangle.

      int i = triangleStore.getFree();

      if (!triangle->silhouette(yBuf, index, triangleStore))
      {
        break;
      }

      while (i != triangleStore.getFree())
      {
        Depth_Triangle *newTriangle = &triangleStore[i];
        //assert(triangle->getDist2() <= newTriangle->getDist2());

        tHeap.addCandidate(newTriangle, upper_bound2);

        ++i;
      }
    }
  }
  while (tHeap.num_triangles > 0 && tHeap.first()->getDist2() <= upper_bound2);

#ifdef sch_DEBUG
  std::cout << "#triangles left = " << num_triangles << std::endl;
#endif

  v = triangle->getClosest();
  p1 = triangle->getClosestPoint(pBuf);
  p2 = triangle->getClosestPoint(qBuf);
  return v.normsquared();

}

CD_Depth::CD_Depth(S_Object *Obj1, S_Object *Obj2):sObj1_(Obj1),sObj2_(Obj2),precision_(_PRECISION_),epsilon_(_EPSILON_)
{

}

void CD_Depth::setEpsilon(Scalar s)
{
  epsilon_=s;
}

void CD_Depth::setRelativePrecision(Scalar s)
{
  precision_=s*s;
}
