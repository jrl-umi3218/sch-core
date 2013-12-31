#ifndef _S_OBJECT_RAW_GL_H
#define _S_OBJECT_RAW_GL_H

#include <SCD/S_Object/S_Object.h>
#include "S_Object_gl.h"

namespace SCD
{
  class S_Object_Raw_GL: public S_Object_GL
  {
  public:
    S_Object_Raw_GL(S_Object *);
    ~S_Object_Raw_GL();

    virtual void drawGLInLocalCordinates() const;

  private:
    void computeDisplayList();
    int displist_;
  };
}

SCD::S_Object_GL* createGL(SCD::S_Object*);

#endif //_S_OBJECT_GL_H
