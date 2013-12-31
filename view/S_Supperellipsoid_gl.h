#ifndef _S_SUPERELLIPSOID_GL
#define _S_SUPERELLIPSOID_GL

#include "S_Object_gl.h"
#include <SCD/S_Object/S_Superellipsoid.h>

namespace SCD
{
  class S_Superellipsoid_GL: public S_Object_GL
  {
  public:
    S_Superellipsoid_GL(S_Superellipsoid * obj);
    ~S_Superellipsoid_GL();

    virtual void drawGLInLocalCordinates() const;

  private:
    void createDispList();

    S_Superellipsoid * ellipse_;
    int displist_;
  };
}

#endif // _S_SUPERELLIPSOID_GL
