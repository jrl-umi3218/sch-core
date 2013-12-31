#include <SCD/S_Polyhedron/Polyhedron_algorithms.h>
#include "S_Object_gl.h"

namespace SCD
{
  class Polyhedron_algorithms_GL: public S_Object_GL
  {
  public:
    Polyhedron_algorithms_GL(Polyhedron_algorithms *);

    virtual void drawGLInLocalCordinates() const;

  private:
    Polyhedron_algorithms * pa_;

    void createDispList();
    int displayList_;
  };
}
