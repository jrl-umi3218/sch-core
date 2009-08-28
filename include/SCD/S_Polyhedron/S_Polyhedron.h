#ifndef _S_POLYHEDRON
#define _S_POLYHEDRON

#pragma once
#include <SCD/scd_api.h>
#include <SCD/S_Object/S_ObjectNonNormalized.h>
#include <SCD/S_Polyhedron/S_PolyhedronVertex.h>
#include <SCD/S_Polyhedron/Polyhedron_algorithms.h>

#include <string>
#include <vector>

#include <boost/serialization/split_member.hpp>

namespace SCD
{

	

	class S_Polyhedron :
		public S_ObjectNonNormalized
	{
	public:
		SCD_API S_Polyhedron(void);

		SCD_API S_Polyhedron(const S_Polyhedron&);


		SCD_API virtual ~S_Polyhedron(void);

		SCD_API const S_Polyhedron& operator =(const S_Polyhedron&);

    #ifdef WITH_OPENGL
		SCD_API virtual void drawGLInLocalCordinates();
    #endif

		/*
		* \brief loads the polyhedron from a file. the file must be in the format of Qhull conconvex.exe output, called with these options : 
		* \ "qconvex.exe TI <input_filename> TO <output_filename> Qt o f" 
		*/

		SCD_API virtual void constructFromFile(const std::string& filename);


    /*!
    *  \brief Load the object from a binary archive
    *  \param filename path to the binary archive
    */
    SCD_API virtual void loadFromBinary(const std::string & filename);


    /*!
    *  \brief Save the object to a binary archive
    *  \param filename path to the binary archive
    */
    SCD_API virtual void saveToBinary(const std::string & filename);


		/*! 
		*  \brief updates the fast access arrays, must be called after each polyhedron modification
		*/
		SCD_API void updateFastArrays();

		SCD_API Point3 naiveSupport(const Vector3& v)const;

		/*! 
		*  \brief updates the Neighborhood of the vertexes, must be called on polyhedron 
		*  \which vertexes have no neighbors, or after calling clearNeighbors.
		*/
		SCD_API void updateVertexNeighbors();

		/*! 
		*  \brief clears the neighbors tables;
		*/
		SCD_API void clearNeighbors();

		/*! 
		*  \brief clears all the polyhedron;
		*/
		SCD_API void clear();

		/*
		* \brief deletes aal the vertexes that dont have neighbors;
		*/
		SCD_API void deleteVertexesWithoutNeighbors();

    template<class Archive>
    void save(Archive & ar, const unsigned int version) const
    {
      ar & boost::serialization::base_object<S_ObjectNonNormalized>(*this);
      ar & poly;
    }

    template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<S_ObjectNonNormalized>(*this);
      ar & poly;
      updateFastArrays();
      updateVertexNeighbors();
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER();

	protected:
		SCD_API virtual Point3 l_Support(const Vector3& v, int& lastFeature)const;
		SCD_API virtual	S_ObjectType getType() const;




	protected:

		Polyhedron_algorithms poly;




	};
}
#endif
