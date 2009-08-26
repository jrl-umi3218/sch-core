#ifndef _S_POLYHEDRON
#define _S_POLYHEDRON

#pragma once
#include <SCD/S_Object/S_ObjectNonNormalized.h>
#include <SCD/S_Polyhedron/S_PolyhedronVertex.h>
#include <SCD/S_Polyhedron/Polyhedron_algorithms.h>

#include <boost/serialization/base_object.hpp>

#include <string>
#include <vector>

namespace SCD
{

	

	class S_Polyhedron :
		public S_ObjectNonNormalized
	{
	public:
		S_Polyhedron(void);

		S_Polyhedron(const S_Polyhedron&);


		virtual ~S_Polyhedron(void);

		const S_Polyhedron& operator =(const S_Polyhedron&);

    #ifdef WITH_OPENGL
		virtual void drawGLInLocalCordinates();
    #endif

		/*
		* \brief loads the polyhedron from a file. the file must be in the format of Qhull conconvex.exe output, called with these options : 
		* \ "qconvex.exe TI <input_filename> TO <output_filename> Qt o f" 
		*/

		virtual void constructFromFile(const std::string& filename);

		/*! 
		*  \brief updates the fast access arrays, must be called after each polyhedron modification
		*/
		void updateFastArrays();

		Point3 naiveSupport(const Vector3& v)const;

		/*! 
		*  \brief updates the Neighborhood of the vertexes, must be called on polyhedron 
		*  \which vertexes have no neighbors, or after calling clearNeighbors.
		*/
		void updateVertexNeighbors();

		/*! 
		*  \brief clears the neighbors tables;
		*/
		void clearNeighbors();

		/*! 
		*  \brief clears all the polyhedron;
		*/
		void clear();

		/*
		* \brief deletes aal the vertexes that dont have neighbors;
		*/
		void deleteVertexesWithoutNeighbors();

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
      boost::serialization::base_object<S_ObjectNonNormalized>(*this);
      ar & poly;
    }
	protected:
		virtual Point3 l_Support(const Vector3& v, int& lastFeature)const;
		virtual	S_ObjectType getType() const;




	protected:

		Polyhedron_algorithms poly;




	};
}
#endif
