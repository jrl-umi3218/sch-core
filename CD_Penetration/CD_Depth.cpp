#include "CD_Depth.h"
#include "DT_triEdge.h"
#include <algorithm>


const int       MaxSupportPoints = 100;
const int       MaxFacets         = 200;

static Point3  pBuf[MaxSupportPoints];
static Point3  qBuf[MaxSupportPoints];
static Vector3 yBuf[MaxSupportPoints];

static Triangle *triangleHeap[MaxFacets];
static int  num_triangles;

int furthestAxis(Vector3 v)
{
	Vector3 vp(fabs(v[0]),fabs(v[1]),fabs(v[2]));

	return v[0] < v[1] ? (v[0] < v[2] ? 0 : 2) : (v[1] < v[2] ? 1 : 2);

}

inline int originInTetrahedron(const Vector3& p1, const Vector3& p2, 
                               const Vector3& p3, const Vector3& p4)
{
    Vector3 normal1 = (p2 - p1)^( p3 - p1);
	if ((normal1* p1) > Scalar(0.0) == (normal1* p4) > Scalar(0.0))
    {
        return 4;
    }
    
    Vector3 normal2 = (p4 - p2)^( p3 - p2);
    if ((normal2* p2) > Scalar(0.0) == (normal2* p1) > Scalar(0.0))
    {
        return 1;
    }
    
    Vector3 normal3 = (p4 - p3)^( p1 - p3);
    if ((normal3* p3) > Scalar(0.0) == (normal3* p2) > Scalar(0.0))
    {
        return 2;
    }
    
    Vector3 normal4 = (p2 - p4)^( p1 - p4);
    if ((normal4* p4) > Scalar(0.0) == (normal4* p3) > Scalar(0.0))
    {
        return 3; 
    }
    
    return 0;
}

class TriangleComp
{
public:
    
    bool operator()(const Triangle *face1, const Triangle *face2) 
    { 
        return face1->getDist2() > face2->getDist2();
    }
} triangleComp;


inline void addCandidate(Triangle *triangle, Scalar upper2) 
{
    if (triangle->isClosestInternal() && triangle->getDist2() <= upper2)
    {
        triangleHeap[num_triangles++] = triangle;
        std::push_heap(&triangleHeap[0], &triangleHeap[num_triangles], triangleComp);
#ifdef DEBUG
        std::cout << " accepted" << std::endl;
#endif
    }
    else 
    {
#ifdef DEBUG
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

CD_Depth::CD_Depth(void)
{
}

CD_Depth::~CD_Depth(void)
{
}



Scalar CD_Depth::getPenetrationDepth(const S_Object* O1, const S_Object* O2,Vector3& v, Point3 &p1,  Point3 &p2,const CD_SimplexEnhanced& s,
									 const CD_Simplex& s1, const CD_Simplex& s2, Scalar precision,Scalar epsilon)
{
	int num_verts;

	switch (s.getType())
	{
	case CD_Simplex::point:
		pBuf[0]=s1[0];
		qBuf[0]=s2[0];
		yBuf[0]=s[0];
		num_verts=1;
		break;
	case CD_Simplex::segment:
		pBuf[0]=s1[0];
		qBuf[0]=s2[0];
		yBuf[0]=s[0];
		pBuf[1]=s1[1];
		qBuf[1]=s2[1];
		yBuf[1]=s[1];
		num_verts=2;
		break;
	case CD_Simplex::triangle:
		pBuf[0]=s1[0];
		qBuf[0]=s2[0];
		yBuf[0]=s[0];
		pBuf[1]=s1[1];
		qBuf[1]=s2[1];
		yBuf[1]=s[1];
		pBuf[2]=s1[2];
		qBuf[2]=s2[2];
		yBuf[2]=s[2];
		num_verts=3;
		break;
	default:
		pBuf[0]=s1[0];
		qBuf[0]=s2[0];
		yBuf[0]=s[0];
		pBuf[1]=s1[1];
		qBuf[1]=s2[1];
		yBuf[1]=s[1];
		pBuf[2]=s1[2];
		qBuf[2]=s2[2];
		yBuf[2]=s[2];
		pBuf[3]=s1[3];
		qBuf[3]=s2[3];
		yBuf[3]=s[3];
		num_verts=4;

	}
	Scalar tolerance = epsilon*s.farthestPointDistance();
    
    num_triangles = 0;
    
    g_triangleStore.clear();
	
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
        
        pBuf[2] = O1->Support(aux1);
        qBuf[2] = O2->Support(-aux1);
        yBuf[2] = pBuf[2] - qBuf[2];
	    
        pBuf[3] = O1->Support(aux2);
        qBuf[3] = O2->Support(-aux2);
        yBuf[3] = pBuf[3] - qBuf[3];
	    
        pBuf[4] = O1->Support(aux3);
        qBuf[4] = O2->Support(-aux3);
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
            Triangle *f0 = g_triangleStore.newTriangle(yBuf, 0, 1, 2);
            Triangle *f1 = g_triangleStore.newTriangle(yBuf, 0, 3, 1);
            Triangle *f2 = g_triangleStore.newTriangle(yBuf, 0, 2, 3);
            Triangle *f3 = g_triangleStore.newTriangle(yBuf, 1, 3, 2);
            
            if (!(f0 && f0->getDist2() > Scalar(0.0) &&
                  f1 && f1->getDist2() > Scalar(0.0) &&
                  f2 && f2->getDist2() > Scalar(0.0) &&
                  f3 && f3->getDist2() > Scalar(0.0)))
			{
				return 0;
			}
            
            link(Edge(f0, 0), Edge(f1, 2));
            link(Edge(f0, 1), Edge(f3, 2));
            link(Edge(f0, 2), Edge(f2, 0));
            link(Edge(f1, 0), Edge(f2, 2));
            link(Edge(f1, 1), Edge(f3, 0));
            link(Edge(f2, 1), Edge(f3, 1));
            
            addCandidate(f0, INFINITY);
            addCandidate(f1, INFINITY);
            addCandidate(f2, INFINITY);
            addCandidate(f3, INFINITY);
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
	    
        pBuf[3] = O1->Support(vv);
        qBuf[3] = O2->Support(-vv);
        yBuf[3] = pBuf[3] - qBuf[3];
        pBuf[4] = O1->Support(-vv);
        qBuf[4] = O2->Support(vv);
        yBuf[4] = pBuf[4] - qBuf[4];
	    
        Triangle* f0 = g_triangleStore.newTriangle(yBuf, 0, 1, 3);
        Triangle* f1 = g_triangleStore.newTriangle(yBuf, 1, 2, 3);
        Triangle* f2 = g_triangleStore.newTriangle(yBuf, 2, 0, 3); 
        Triangle* f3 = g_triangleStore.newTriangle(yBuf, 0, 2, 4);
        Triangle* f4 = g_triangleStore.newTriangle(yBuf, 2, 1, 4);
        Triangle* f5 = g_triangleStore.newTriangle(yBuf, 1, 0, 4);
        
        if (!(f0 && f0->getDist2() > Scalar(0.0) &&
              f1 && f1->getDist2() > Scalar(0.0) &&
              f2 && f2->getDist2() > Scalar(0.0) &&
              f3 && f3->getDist2() > Scalar(0.0) &&
              f4 && f4->getDist2() > Scalar(0.0) &&
              f5 && f5->getDist2() > Scalar(0.0)))
        {
            return false;
        }
        
        link(Edge(f0, 1), Edge(f1, 2));
        link(Edge(f1, 1), Edge(f2, 2));
        link(Edge(f2, 1), Edge(f0, 2));
        
        link(Edge(f0, 0), Edge(f5, 0));
        link(Edge(f1, 0), Edge(f4, 0));
        link(Edge(f2, 0), Edge(f3, 0));
        
        link(Edge(f3, 1), Edge(f4, 2));
        link(Edge(f4, 1), Edge(f5, 2));
        link(Edge(f5, 1), Edge(f3, 2));
	    
        addCandidate(f0, INFINITY);
        addCandidate(f1, INFINITY);
        addCandidate(f2, INFINITY);
        addCandidate(f3, INFINITY);  
        addCandidate(f4, INFINITY);
        addCandidate(f5, INFINITY);
	    
        num_verts = 5;
    }
    break;
    }
    
    // We have a polytope inside the Minkowski sum containing
    // the origin.
    
    if (num_triangles == 0)
    {
        return 0;
    }
    
    // at least one triangle on the heap.	
    
    Triangle *triangle = 0;
    
    Scalar upper_bound2 = INFINITY; 	
    
    do 
    {
        triangle = triangleHeap[0];
        std::pop_heap(&triangleHeap[0], &triangleHeap[num_triangles], triangleComp);
        --num_triangles;
		
        if (!triangle->isObsolete()) 
        {
            if (num_verts == MaxSupportPoints)
            {
#ifdef DEBUG
                std::cout << "Ouch, no convergence!!!" << std::endl;
#endif 
                assert(false);	
                break;
            }
			
            pBuf[num_verts] = O1->Support( triangle->getClosest());
            qBuf[num_verts] = O2->Support(-triangle->getClosest());
            yBuf[num_verts] = pBuf[num_verts] - qBuf[num_verts];
			
            int index = num_verts++;
            Scalar far_dist = (yBuf[index]* triangle->getClosest());
			
            // Make sure the support mapping is OK.
            assert(far_dist > Scalar(0.0));
            Scalar far_dist2 = far_dist * far_dist / triangle->getDist2();
            GEN_set_min(upper_bound2, far_dist2);
			
            Scalar error = far_dist - triangle->getDist2();
            if (error <= GEN_max(precision * far_dist, epsilon)
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
			
            int i = g_triangleStore.getFree();
            
            if (!triangle->silhouette(yBuf, index, g_triangleStore))
            {
                break;
            }
			
            while (i != g_triangleStore.getFree())
            {
                Triangle *newTriangle = &g_triangleStore[i];
                //assert(triangle->getDist2() <= newTriangle->getDist2());
                
                addCandidate(newTriangle, upper_bound2);
                
                ++i;
            }
        }
    }
    while (num_triangles > 0 && triangleHeap[0]->getDist2() <= upper_bound2);
	
#ifdef DEBUG    
    std::cout << "#triangles left = " << num_triangles << std::endl;
#endif
    
    v = triangle->getClosest();
    p1 = triangle->getClosestPoint(pBuf);    
    p2 = triangle->getClosestPoint(qBuf);    
	return (p1-p2).normsquared();
	
}