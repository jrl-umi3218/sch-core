#pragma once
#ifndef _S_CONE_H_SCH
#  define _S_CONE_H_SCH

#  include <sch/S_Object/S_ObjectNonNormalized.h>

namespace sch
{

class S_Cone : public S_ObjectNonNormalized
{
public:
  /*!
   * \brief constructor
   *  the cone centered at the apex and having its axis aligned on the z axis
   * and directed above
   * \param angle is the angle between the axis of the cone and the side of
   *         the cone. Make sure the angle is less than pi/2
   * \param height is the height of the cone.
   */
  SCH_API S_Cone(const Scalar & angle, const Scalar & height);
  SCH_API virtual ~S_Cone();

  SCH_API virtual S_Cone * clone() const;

  SCH_API virtual Point3 l_Support(const Vector3 & v, int & lastFeature) const;

  SCH_API virtual S_ObjectType getType() const;

  SCH_API virtual Scalar getAngle() const;
  SCH_API virtual Scalar getHeight() const;

protected:
  Scalar angle_;
  Scalar height_;
  Scalar angleTan_;
  Scalar baseRadius_;
};
} // namespace sch

#endif ///_S_CONE_H_SCH

/**
 * \example      example0.cpp
 * This example shows the normal use of the SCH library.
 */
