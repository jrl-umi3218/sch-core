#include "S_Object_gl.h"
#include "S_Object_Raw_gl.h"
#include "S_Box_gl.h"
#include "S_Sphere_gl.h"
#include "S_Supperellipsoid_gl.h"
#include "Polyhedron_algorithms_gl.h"
#include "STPBV_gl.h"

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

void S_Object_GL::drawGL() const
{
  glPushMatrix();
  double d[16];
  if(obj_ != 0x0)
    obj_->getTransformationMatrix(d);
  glMultMatrixd(d);
  drawGLInLocalCordinates();
  glPopMatrix();
}


SCD::S_Object_GL* createGL(SCD::S_Object* obj)
{
  if (obj == 0x0)
    return 0x0;

  S_Object::S_ObjectType type = obj->getType();

  switch(type)
  {
  case(S_Object::TS_Object):
  {
    return (new S_Object_Raw_GL(obj));
  }
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
  }
  return 0x0;
}
