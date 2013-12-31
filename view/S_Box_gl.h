#ifndef _S_BOX_GL_H
#define _S_BOX_GL_H

#include "S_Object_gl.h"
#include <SCD/S_Object/S_Box.h>

namespace SCD
{
  class S_Box_GL: public S_Object_GL
  {
  public:
    S_Box_GL(S_Box * obj);
    ~S_Box_GL();

    virtual void drawGLInLocalCordinates() const;

  private:
    void createDispList();

    S_Box * box_;
    int displist_;
  };
}

#endif // _S_BOX_GL_H
