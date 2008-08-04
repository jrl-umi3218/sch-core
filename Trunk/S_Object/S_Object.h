#pragma once

#ifndef _S_OBJECT
#define _S_OBJECT


#include "../matrix/SCD_Types.h"

namespace SCD
{

	/*!
	* \struct the time stamp is used to check if objects moved or not between two proximity queries, if they didn't, computing the distance between them becomes useless.
	*/
	typedef struct _TimeStamp 
	{
		unsigned long int value1,value2,value3,value4;

		explicit _TimeStamp():value1(0),value2(0),value3(0),value4(0)
		{}

		bool operator==(const _TimeStamp t)const
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
			if (value1==unsigned long int(-1))
			{	
				value2--;
				if (value2==unsigned long int(-1))
				{	
					value3--;
					if (value3==unsigned long int(-1))
					{	
						value4--;

					}
				}
			}

		}




	} S_ObjectTimeStamp;

	class S_Object
	{

	protected:
		/*! 
		*  \brief gives the support point for a given normalized vector and a given last feature. Must be overloaded.
		*  \param v direction vector (normalized)
		*  \param lastFeature tells in which feature we were in last query, amd returns the new one. very important in spatio-temporal coherence
		*  \return returns the support point.
		*/ 

		virtual Point3 n_Support(const Vector3& v, int& lastFeature)const=0;


	public:

		S_Object(void);

		virtual ~S_Object(void);

		/*! 
		*  \brief normalizes the vector and put it in objects coordinates, then calls n_support.
		*  \param v direction vector
		*  \return returns the support point.
		*/ 
		virtual Point3 support(const Vector3& v) const;

		/*! 
		*  \brief version of support with last feature optimization
		*  \param v direction vector
		*  \param lastFeature tells in which feature we were in last query, amd returns the new one. very important in spatio-temporal coherence
		*  \return returns the support point.
		*/ 
		virtual Point3 support(const Vector3& v, int & LastFeature) const;

		
		/*
		*  \brief Constructs the Object from a file
		*/
		virtual void constructFromFile(const std::string& filename);

	   /*
		*  \brief Constructs the Object from a file and prepares the openGL display, default is to call construct from file
		*/
		virtual void constructFromFileWithGL(const std::string& filename);

		/*
		*  \brief Sets the Orientation
		*/
		void setOrientation(const Matrix3x3& Rotation);

		void setOrientation(const Scalar& r00,const Scalar& r01,const Scalar& r02,
			const Scalar& r10,const Scalar& r11,const Scalar& r12,
			const Scalar& r20,const Scalar& r21,const Scalar& r22);

		void setOrientation(const Quaternion quaternion);

		void setOrientation(const Scalar& q0,const Scalar& q1,const  Scalar& q2,const  Scalar& q3);

		void setOrientation(const Scalar& yaw,const Scalar& pitch,const Scalar& roll);

		void setOrientation(const Scalar* const p);

		void setOrientation(const Scalar& angle, const Vector3& axe);


		/*!
		* \brief Sets the position
		*/
		void setPosition(const Vector3& v);

		void setPosition(const Scalar& x,const Scalar& y, const Scalar& z);

		void setPosition(const Scalar* const v);

		/*!
		* \brief Sets the transformation matrix
		*/

		void setTransformation(const Matrix4x4& transformation);

		/*!
		* \brief composes the current orientation with a Rotation
		*/

		void addRotation(const Matrix3x3& Rotation);

		void addRotation(const Scalar& r00,const Scalar& r01,const Scalar& r02,
			const Scalar& r10,const Scalar& r11,const Scalar& r12,
			const Scalar& r20,const Scalar& r21,const Scalar& r22);

		void addRotation(const Quaternion quaternion);

		void addRotation(const Scalar& q0,const Scalar& q1,const  Scalar& q2,const  Scalar& q3);

		void addRotation(const Scalar& angle, const Vector3& axe);

		void addRotation(const Scalar& yaw,const Scalar& pitch,const Scalar& roll);

		void addRotation(const Scalar  * const p);


		/*!
		* \name Adds a translation
		* @{
		*/

		void addTranslation(const Vector3& v);

		void addTranslation(const Scalar* const v);

		void addTranslation(const Scalar& x,const Scalar& y, const Scalar& z);

		/*! @} */

		/*!
		* \brief composes the current transfornation with a scale
		*/

		void addScale(const Scalar& x,const Scalar& y, const Scalar& z);

		/*!
		* \brief composes the current transfornation with transformation matrix one
		*/

		void addTransformation(const Matrix4x4& transformation);


		/*!
		* \brief loads Identity
		*/
		void resetTransformation();

		/*!
		* \brief returns the position
		*/
		const Vector3& getPosition()const;

		/*!
		* \brief returns the orientation as a rotation matrix
		*/
		const Matrix3x3& getOrientation()const;	

		/*!
		* \brief puts the transfomation matrix in a sclar array
		*/
		void getTransformationMatrix(Scalar *S) const;

		/*!
		* \brief Displays the objects in openGl. default is to load unviverse cordinates and call drawGLInLocalCordinates()
		*/
		virtual void drawGL();

	   /*!
		* \brief displays the object in its cordinates using OpenGl. Default is support-mapping based display method.
		*/
		virtual void drawGLInLocalCordinates();




		/*!
		* \brief type of a solid object
		*/
		static enum S_ObjectType	
		{
			TS_Object,
			TPoint,
			TSegment,
			TPolyhedron,
			TSTP_BV,
			TCylinder,
			TSphere,
			TBox,
			TSuperellipsoid

		};

		/*!
		* \brief must be overloaded to return the type
		*/
		virtual	S_ObjectType getType() const;



		/*!
		* \brief returns the current time stamp
		*/
		const S_ObjectTimeStamp& checkStamp()const;







	protected:





		S_ObjectTimeStamp stamp_;

		int displist_;

		int stacks_,slices_;

		Matrix3x3 mRot_;

		Vector3 trans_;




	};


#include "S_Object.hxx"
}
#endif