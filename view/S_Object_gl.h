#ifndef _S_OBJECT_GL_H
#define _S_OBJECT_GL_H

#include <SCD/S_Object/S_Object.h>
#include <boost/noncopyable.hpp>

namespace SCD
{
  class S_Object_GL: boost::noncopyable
  {
  public:
    S_Object_GL(S_Object *);

    /*!
    * \brief Displays the objects in openGl. default is to load unviverse cordinates and call drawGLInLocalCordinates()
    */
    virtual void drawGL() const;

  protected:
    /*!
    * \brief displays the object in its cordinates using OpenGl. Default is support-mapping based display method.
    */
    virtual void drawGLInLocalCordinates() const = 0;

  protected:
    S_Object * obj_;
  };
}

SCD::S_Object_GL* createGL(SCD::S_Object*);

#endif //_S_OBJECT_GL_H
