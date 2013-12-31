#include "S_Sphere_gl.h"

#if defined __APPLE__
# include <GLUT/glut.h>
#else
# include <GL/glut.h>
#endif // __APPLE__

using namespace SCD;

S_Sphere_GL::S_Sphere_GL(S_Sphere * obj)
: S_Object_GL(obj)
, sphere_(obj)
, displist_(-1)
{
  createDispList();
}

void S_Sphere_GL::drawGLInLocalCordinates() const
{
  glCallList(displist_);
}

void S_Sphere_GL::createDispList()
{
  displist_=glGenLists(1);
  glNewList(displist_,GL_COMPILE);
  glutSolidSphere(sphere_->getRadius(),sphere_->getSlices(),sphere_->getStacks());
  glEndList();
}
