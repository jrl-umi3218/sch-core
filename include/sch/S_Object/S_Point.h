#ifndef _S_POINT_H
#define _S_POINT_H

#include <sch/S_Object/S_ObjectNonNormalized.h>

namespace sch
{
  class S_Point :
    public S_ObjectNonNormalized
  {
  public:
    SCH_API S_Point();
    SCH_API ~S_Point();

    SCH_API void setDisplayRadius( Scalar r);
    SCH_API Scalar getDisplayRadius() const ;


  protected:
    SCH_API virtual Point3 l_Support(const Vector3& v, int& lastFeature)const;
    SCH_API virtual	S_ObjectType getType() const;

    Scalar displayRadius_;
  };
}
#endif
