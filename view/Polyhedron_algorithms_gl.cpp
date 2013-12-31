#include "Polyhedron_algorithms_gl.h"

#if defined __APPLE__
# include <GLUT/glut.h>
#else
# include <GL/glut.h>
#endif // __APPLE__

using namespace SCD;
Polyhedron_algorithms_GL::Polyhedron_algorithms_GL(Polyhedron_algorithms *pa)
: S_Object_GL(0x0)
, pa_(pa)
, displayList_(-1)
{
  createDispList();
}

void Polyhedron_algorithms_GL::drawGLInLocalCordinates() const
{
  glCallList(displayList_);
}

void Polyhedron_algorithms_GL::createDispList()
{
  const std::vector<S_PolyhedronVertex*> & vertexes = pa_->vertexes_;
  const std::vector<PolyhedronTriangle> & triangles = pa_->triangles_;

  if (vertexes.size()>0)
  {
    /*OpenGL displaylist*/

    displayList_=glGenLists(1);
    glNewList(displayList_,GL_COMPILE);
    glBegin(GL_TRIANGLES);
    glColor3d(0.6,0.8,0.7);

    for (unsigned i=0;i<triangles.size();i++)
    {
      glNormal3d(triangles[i].normal[0],triangles[i].normal[1],triangles[i].normal[2]);

      glVertex3d(
        vertexes[triangles[i].a]->getCordinates()[0],
        vertexes[triangles[i].a]->getCordinates()[1],
        vertexes[triangles[i].a]->getCordinates()[2]);

      glVertex3d(
        vertexes[triangles[i].b]->getCordinates()[0],
        vertexes[triangles[i].b]->getCordinates()[1],
        vertexes[triangles[i].b]->getCordinates()[2]);

      glVertex3d(
        vertexes[triangles[i].c]->getCordinates()[0],
        vertexes[triangles[i].c]->getCordinates()[1],
        vertexes[triangles[i].c]->getCordinates()[2]);
    }

    glEnd();
    glEndList();
  }
}
