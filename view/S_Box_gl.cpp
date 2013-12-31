#include "S_Box_gl.h"

#if defined __APPLE__
# include <GLUT/glut.h>
#else
# include <GL/glut.h>
#endif // __APPLE__

using namespace SCD;

S_Box_GL::S_Box_GL(S_Box * obj)
: S_Object_GL(obj)
, box_(obj)
, displist_(-1)
{
  createDispList();
}

void S_Box_GL::drawGLInLocalCordinates() const
{
  glCallList(displist_);
}

void S_Box_GL::createDispList()
{
  displist_=glGenLists(1);
  glNewList(displist_,GL_COMPILE);

  Scalar a_,b_,c_;
  box_->getBoxParameters(a_, b_, c_);

  Point3 x(a_,b_,c_), n(-a_,-b_,-c_);

  glBegin(GL_QUADS);

  glNormal3d(0,0,1);
  glVertex3d(n[0],x[1],x[2]);
  glVertex3d(n[0],n[1],x[2]);
  glVertex3d(x[0],n[1],x[2]);
  glVertex3d(x[0],x[1],x[2]);

  glNormal3d(0,0,-1);
  glVertex3d(x[0],x[1],n[2]);
  glVertex3d(x[0],n[1],n[2]);
  glVertex3d(n[0],n[1],n[2]);
  glVertex3d(n[0],x[1],n[2]);

  glNormal3d(1,0,0);
  glVertex3d(x[0],x[1],x[2]);
  glVertex3d(x[0],n[1],x[2]);
  glVertex3d(x[0],n[1],n[2]);
  glVertex3d(x[0],x[1],n[2]);

  glNormal3d(-1,0,0);
  glVertex3d(n[0],x[1],n[2]);
  glVertex3d(n[0],n[1],n[2]);
  glVertex3d(n[0],n[1],x[2]);
  glVertex3d(n[0],x[1],x[2]);

  glNormal3d(0,1,0);
  glVertex3d(n[0],x[1],n[2]);
  glVertex3d(n[0],x[1],x[2]);
  glVertex3d(x[0],x[1],x[2]);
  glVertex3d(x[0],x[1],n[2]);

  glNormal3d(0,-1,0);
  glVertex3d(x[0],n[1],n[2]);
  glVertex3d(x[0],n[1],x[2]);
  glVertex3d(n[0],n[1],x[2]);
  glVertex3d(n[0],n[1],n[2]);

  glEnd();
  glEndList();
}
