#include "S_Supperellipsoid_gl.h"

#if defined __APPLE__
# include <GLUT/glut.h>
#else
# include <GL/glut.h>
#endif // __APPLE__

#include <boost/math/constants/constants.hpp>
#include <vector>

using boost::math::constants::pi;
using namespace SCD;

inline short sign(Scalar i)
{
  return (i>0)? 1:-1;
}

S_Superellipsoid_GL::S_Superellipsoid_GL(S_Superellipsoid * obj)
: S_Object_GL(obj)
, ellipse_(obj)
, displist_(-1)
{
  createDispList();
}

void S_Superellipsoid_GL::drawGLInLocalCordinates()
{
  glCallList(displist_);
}

void S_Superellipsoid_GL::createDispList()
{
  std::vector<Point3> points;
  std::vector<Vector3> normals;

  displist_=glGenLists(1);

  Scalar a_, b_, c_;
  Scalar epsilon1_, epsilon2_;
  int slices_ = ellipse_->getSlices();
  int stacks_ = ellipse_->getStacks();

  ellipse_->getEllipsoidParameter(a_, b_, c_, epsilon1_, epsilon2_);

  points.push_back(Point3(0,0,c_));
  normals.push_back(Vector3(0,0,1));

  normals.push_back(Vector3(0,0,-1));
  points.push_back(Point3(0,0,-c_));

  Scalar c2,c1,s1,s2;

  Scalar longit=0;

  double p1=pi<double>()*2/slices_;
  double p2=pi<double>()/(stacks_-1);


  for (int i=0;i<slices_;i++)
  {
    Scalar latt=pi<double>()/2-p2;
    for (int j=0;j<stacks_-2;j++)
    {
      c1=cos(latt);
      c2=cos(longit);
      s1=sin(latt);
      s2=sin(longit);

      points.push_back(Point3(a_*pow(fabs(c1),epsilon1_)*pow(fabs(c2),epsilon2_)*sign(c1)*sign(c2),
        b_*pow(fabs(c1),epsilon1_)*pow(fabs(s2),epsilon2_)*sign(s2)*sign(c1),
        c_*pow(fabs(s1),epsilon1_)*sign(s1)));


      Vector3 n((1/a_)*pow(fabs(c1),2-epsilon1_)*pow(fabs(c2),2-epsilon2_)*sign(c1)*sign(c2),
        (1/b_)*pow(fabs(c1),2-epsilon1_)*pow(fabs(s2),2-epsilon2_)*sign(s2)*sign(c1),
        (1/c_)*pow(fabs(s1),2-epsilon1_)*sign(s1));

      n.normalize();

      normals.push_back(n);

      latt-=p2;
    }
    longit+=p1;
  }



  glNewList(displist_,GL_COMPILE);
  glBegin(GL_TRIANGLES);

  for (int i=0;i<slices_;i++)
  {
    glNormal3d(normals[0][0],normals[0][1],normals[0][2]);
    glVertex3d(points[0][0],points[0][1],points[0][2]);


    glNormal3d(normals[2+(i*(stacks_-2))][0],normals[2+(i*(stacks_-2))][1],normals[2+(i*(stacks_-2))][2]);
    glVertex3d(points[2+(i*(stacks_-2))][0],points[2+(i*(stacks_-2))][1],points[2+(i*(stacks_-2))][2]);


    glNormal3d(normals[2+(((i+1)%(slices_))*(stacks_-2))][0],normals[2+(((i+1)%(slices_))*(stacks_-2))][1],normals[2+(((i+1)%(slices_))*(stacks_-2))][2]);
    glVertex3d(points[2+(((i+1)%(slices_))*(stacks_-2))][0],points[2+(((i+1)%(slices_))*(stacks_-2))][1],points[2+(((i+1)%(slices_))*(stacks_-2))][2]);


    glNormal3d(normals[1][0],normals[1][1],normals[1][2]);
    glVertex3d(points[1][0],points[1][1],points[1][2]);

    glNormal3d(normals[stacks_-1+(((i+1)%(slices_))*(stacks_-2))][0],normals[stacks_-1+(((i+1)%(slices_))*(stacks_-2))][1],normals[stacks_-1+(((i+1)%(slices_))*(stacks_-2))][2]);
    glVertex3d(points[stacks_-1+(((i+1)%(slices_))*(stacks_-2))][0],points[stacks_-1+(((i+1)%(slices_))*(stacks_-2))][1],points[stacks_-1+(((i+1)%(slices_))*(stacks_-2))][2]);

    glNormal3d(normals[stacks_-1+(i*(stacks_-2))][0],normals[stacks_-1+(i*(stacks_-2))][1],normals[stacks_-1+(i*(stacks_-2))][2]);
    glVertex3d(points[stacks_-1+(i*(stacks_-2))][0],points[stacks_-1+(i*(stacks_-2))][1],points[stacks_-1+(i*(stacks_-2))][2]);
  }

  for (int i=0;i<slices_;i++)
  {
    for (int j=0;j<stacks_-3;j++)
    {
      glNormal3d(normals[2+(i*(stacks_-2))+j][0],normals[2+(i*(stacks_-2))+j][1],normals[2+(i*(stacks_-2))+j][2]);
      glVertex3d(points[2+(i*(stacks_-2))+j][0],points[2+(i*(stacks_-2))+j][1],points[2+(i*(stacks_-2))+j][2]);

      glNormal3d(normals[2+(i*(stacks_-2))+j+1][0],normals[2+(i*(stacks_-2))+j+1][1],normals[2+(i*(stacks_-2))+j+1][2]);
      glVertex3d(points[2+(i*(stacks_-2))+j+1][0],points[2+(i*(stacks_-2))+j+1][1],points[2+(i*(stacks_-2))+j+1][2]);

      glNormal3d(normals[2+(((i+1)%(slices_))*(stacks_-2))+j][0],normals[2+(((i+1)%(slices_))*(stacks_-2))+j][1],normals[2+(((i+1)%(slices_))*(stacks_-2))+j][2]);
      glVertex3d(points[2+(((i+1)%(slices_))*(stacks_-2))+j][0],points[2+(((i+1)%(slices_))*(stacks_-2))+j][1],points[2+(((i+1)%(slices_))*(stacks_-2))+j][2]);


      glNormal3d(normals[stacks_-1+(i*(stacks_-2))-j][0],normals[stacks_-1+(i*(stacks_-2))-j][1],normals[stacks_-1+(i*(stacks_-2))-j][2]);
      glVertex3d(points[stacks_-1+(i*(stacks_-2))-j][0],points[stacks_-1+(i*(stacks_-2))-j][1],points[stacks_-1+(i*(stacks_-2))-j][2]);

      glNormal3d(normals[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j][0],normals[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j][1],normals[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j][2]);
      glVertex3d(points[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j][0],points[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j][1],points[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j][2]);

      glNormal3d(normals[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j-1][0],normals[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j-1][1],normals[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j-1][2]);
      glVertex3d(points[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j-1][0],points[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j-1][1],points[stacks_-1+(((i+1)%(slices_))*(stacks_-2))-j-1][2]);
    }
  }
  glEnd();
  glEndList();
}
