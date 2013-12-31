#include "S_Object_gl.h"
//#include "S_Box_gl.h"
//#include "S_Sphere_gl.h"
//#include "S_Supperellipsoid_gl.h"
//#include "Polyhedron_algorithms_gl.h"
//#include "STPBV_gl.h"

#include <boost/math/constants/constants.hpp>
#include <vector>

#if defined __APPLE__
# include <GLUT/glut.h>
#else
# include <GL/glut.h>
#endif // __APPLE__

using boost::math::constants::pi;
using namespace SCD;

S_Object_GL::S_Object_GL(S_Object * obj)
: obj_(obj)
{}

void S_Object_GL::drawGL()
{
  glPushMatrix();
  double d[16];
  if(obj_ != 0x0)
    obj_->getTransformationMatrix(d);
  glMultMatrixd(d);
  drawGLInLocalCordinates();
  glPopMatrix();
}




S_Object_Raw_GL::S_Object_Raw_GL(S_Object * obj)
: S_Object_GL(obj)
, displist_(-1)
{}

void S_Object_Raw_GL::drawGLInLocalCordinates()
{
  if (displist_==-1)
  {
    std::vector<Point3> points;
    std::vector<Vector3> normals;

    int lastfeature=-1;

    displist_=glGenLists(1);

    points.push_back(obj_->l_Support(Vector3(0,0,1),lastfeature));
    normals.push_back(Vector3(0,0,1));

    normals.push_back(Vector3(0,0,-1));
    points.push_back(obj_->l_Support(Vector3(0,0,-1),lastfeature));

    Scalar c2,c1,s1,s2;

    Scalar longit=0;

    int slices_ = obj_->getSlices();
    int stacks_ = obj_->getStacks();

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

        points.push_back(obj_->l_Support(Vector3(c1*c2,c1*s2,s1),lastfeature));

        Vector3 n(c1*c2,c1*s2,s1);

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

  glCallList(displist_);
}

SCD::S_Object_GL* createGL(SCD::S_Object* obj)
{
  if (obj == 0x0)
    return 0x0;

  S_Object::S_ObjectType type = obj->getType();
  std::cout<<"wut  type " << type << std::endl;

  switch(type)
  {
  case(S_Object::TS_Object):
  {
    return (new S_Object_Raw_GL(obj));
  }
/*
  case(S_Object::TPolyhedron):
  {
    Polyhedron_algorithms * polyhedron = dynamic_cast<Polyhedron_algorithms *>(obj);
    return (new Polyhedron_algorithms_GL(polyhedron));
  }
  case(S_Object::TSTP_BV):
  {
    STP_BV * stp = dynamic_cast<STP_BV *>(obj);
    return (new STP_BV_GL(stp));
  }
  case(S_Object::TSphere):
  {
    S_Sphere * sphere = dynamic_cast<S_Sphere *>(obj);
    return (new S_Sphere_GL(sphere));
  }
  case(S_Object::TBox):
  {
    S_Box * box = dynamic_cast<S_Box *>(obj);
    return (new S_Box_GL(box));
  }
  case(S_Object::TSuperellipsoid):
  {
    S_Superellipsoid * ellipse = dynamic_cast<S_Superellipsoid *>(obj);
    return (new S_Superellipsoid_GL(ellipse));
  }
  case(S_Object::TSTP_BV_WithPolyhedron):
  {
  STP_BV * stp = dynamic_cast<STP_BV *>(obj);
  return (new STP_BV_GL(stp));
  }
*/
  }
  return 0x0;
}
