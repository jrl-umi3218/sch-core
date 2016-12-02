#pragma once

#ifndef _S_OBJECT
#define _S_OBJECT

#include <sch/sch_api.h>
#include <sch/Matrix/SCH_Types.h>

namespace sch
{

  /*!
  * \struct S_ObjectTimeStamp
  * the time stamp is used to check if objects moved or not between two proximity queries, if they didn't, computing the distance between them becomes useless.
  */
  typedef struct _TimeStamp
  {
    unsigned long int value1,value2,value3,value4;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int /*version*/)
    {
      ar & value1 & value2 & value3 & value4;
    }

    explicit _TimeStamp():value1(0),value2(0),value3(0),value4(0)
    {}

    bool operator==(const _TimeStamp & t)const
    {
      return ((value1==t.value1)&&(value2==t.value2));
    }

    void operator++()
    {
      value1++;
      if (!value1)
      {
        value2++;
        if (!value2)
        {
          value3++;
          if (!value3)
          {
            value4++;
          }
        }
      }
    }

    void operator--()
    {
      value1--;
      if (value1==(unsigned long int)(-1))
      {
        value2--;
        if (value2==(unsigned long int)(-1))
        {
          value3--;
          if (value3==(unsigned long int)(-1))
          {
            value4--;
          }
        }
      }
    }
  } S_ObjectTimeStamp;

  /*IMPORTANT !!!! DO NOT INHERIT FROM THIS CLASS, YOU MUST CHOOSE IF YOU NEED VECTOR NORMALIZATION OR NOT IN YOUR SUPPORT FUNCTION AND INHERIT FROM S_ObjectNormalized or S_ObjectNonNormalized*/
  class S_Object
  {

  public:
    /*!
    *  \brief gives the support point for a given vector in local cordinates and a given last feature. MUST BE OVERLOADED.
    *  \param v direction vector (normalized)
    *  \param lastFeature tells in which feature we were in last query, amd returns the new one. very important in spatio-temporal coherence
    *  \return returns the support point.
    */

    SCH_API virtual Point3 l_Support(const Vector3& v, int& lastFeature)const=0;

  public:

    SCH_API S_Object(void);
    SCH_API virtual ~S_Object(void);

    /*!
    *  \brief put it in objects coordinates, then calls l_support. DO NOT OVERLOAD IT UNLESS YOU KNOW WHAT YOU ARE DOING (if you want to define the support function, overload l_support)
    *  \param v direction vector
    *  \return returns the support point.
    */
    SCH_API virtual Point3 support(const Vector3& v) const=0;

    /*!
    *  \brief version of support with last feature optimization
    *  \param v direction vector
    *  \param lastFeature tells in which feature we were in last query, and returns the new one. very important in spatio-temporal coherence
    *  \return returns the support point.
    */
    SCH_API virtual Point3 support(const Vector3& v, int & LastFeature) const=0;


    /*
    *  \brief Constructs the Object from a file
    */
    SCH_API virtual void constructFromFile(const std::string& filename);

    /*
    *  \brief Sets the Orientation
    */
    SCH_API void setOrientation(const Matrix3x3& Rotation);

    SCH_API void setOrientation(const Scalar& r00,const Scalar& r01,const Scalar& r02,
                                const Scalar& r10,const Scalar& r11,const Scalar& r12,
                                const Scalar& r20,const Scalar& r21,const Scalar& r22);

    SCH_API void setOrientation(const Quaternion quaternion);

    SCH_API void setOrientation(const Scalar& q0,const Scalar& q1,const  Scalar& q2,const  Scalar& q3);

    /*!Euler
         * ROLL PITCH YAW - AROUND X, Y THEN Z */
    SCH_API void setOrientation(const Scalar& yaw,const Scalar& pitch,const Scalar& roll);

    SCH_API void setOrientation(const Scalar* const p);

    SCH_API void setOrientation(const Scalar& angle, const Vector3& axe);


    /*!
    * \brief Sets the position
    */
    SCH_API void setPosition(const Vector3& v);

    SCH_API void setPosition(const Scalar& x,const Scalar& y, const Scalar& z);

    SCH_API void setPosition(const Scalar* const v);

    /*!
    * \brief Sets the transformation matrix
    */

    SCH_API void setTransformation(const Matrix4x4& transformation);

    /*!
    * \brief composes the current orientation with a Rotation
    */

    SCH_API void addRotation(const Matrix3x3& Rotation);

    SCH_API void addRotation(const Scalar& r00,const Scalar& r01,const Scalar& r02,
                             const Scalar& r10,const Scalar& r11,const Scalar& r12,
                             const Scalar& r20,const Scalar& r21,const Scalar& r22);

    SCH_API void addRotation(const Quaternion quaternion);

    SCH_API void addRotation(const Scalar& q0,const Scalar& q1,const  Scalar& q2,const  Scalar& q3);

    SCH_API void addRotation(const Scalar& angle, const Vector3& axe);

    /*!Euler
         * ROLL PITCH YAW - AROUND X, Y THEN Z */
    SCH_API void addRotation(const Scalar& yaw,const Scalar& pitch,const Scalar& roll);

    SCH_API void addRotation(const Scalar  * const p);


    /*!
    * \name Adds a translation
    * @{
    */

    SCH_API void addTranslation(const Vector3& v);

    SCH_API void addTranslation(const Scalar* const v);

    SCH_API void addTranslation(const Scalar& x,const Scalar& y, const Scalar& z);

    /*! @} */

    /*!
    * \brief composes the current transfornation with a scale
    */

    SCH_API void addScale(const Scalar& x,const Scalar& y, const Scalar& z);

    /*!
    * \brief composes the current transfornation with transformation matrix one
    */

    SCH_API void addTransformation(const Matrix4x4& transformation);


    /*!
    * \brief loads Identity
    */
    SCH_API void resetTransformation();

    /*!
    * \brief returns the position
    */
    SCH_API const Vector3& getPosition()const;

    /*!
    * \brief returns the orientation as a rotation matrix
    */
    SCH_API const Matrix3x3& getOrientation()const;

    /*!
    * \brief puts the transfomation matrix in a sclar array
    */
    SCH_API void getTransformationMatrix(Scalar *S) const;


    int getSlices() const;
    int getStacks() const;

    /*!
    * \brief type of a solid object. Don't use it to cast !
    */
    enum S_ObjectType
    {
      TS_Object,
      TPolyhedron,
      TSTP_BV,
      TSphere,
      TBox,
      TSuperellipsoid,
      TSTP_BV_WithPolyhedron,
      T_Point,
      T_Capsule
    };

    /*!
    * \brief must be overloaded to return the type
    */
    SCH_API virtual	S_ObjectType getType() const;

    /*!
    * \brief returns the current time stamp
    */
    const S_ObjectTimeStamp& checkStamp()const;


    template<class Archive>
    void serialize(Archive & ar, const unsigned int /*version*/)
    {
      ar & stamp_;
      ar & stacks_;
      ar & slices_;
      ar & mRot_;
      ar & trans_;
    }

  protected:
    S_ObjectTimeStamp stamp_;
    int stacks_,slices_;
    Matrix3x3 mRot_;
    Vector3 trans_;
  };


#include <sch/S_Object/S_Object.hxx>
}
#endif
