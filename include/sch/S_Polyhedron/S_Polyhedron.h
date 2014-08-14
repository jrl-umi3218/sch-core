#ifndef _S_POLYHEDRON
#define _S_POLYHEDRON

#pragma once
#include <sch/sch_api.h>
#include <sch/S_Object/S_ObjectNonNormalized.h>
#include <sch/S_Polyhedron/S_PolyhedronVertex.h>
#include <sch/S_Polyhedron/Polyhedron_algorithms.h>

#include <string>
#include <vector>

#ifdef WITH_BOOST_1_36
#include <sch/boost/archive/detail/oserializer.hpp>
#endif
#include <boost/serialization/split_member.hpp>

namespace sch
{
  class S_Polyhedron :
    public S_ObjectNonNormalized
  {
  public:
    SCH_API S_Polyhedron(void);
    SCH_API S_Polyhedron(const S_Polyhedron&);
    SCH_API virtual ~S_Polyhedron(void);

    SCH_API const S_Polyhedron& operator =(const S_Polyhedron&);

    /*!
    * \brief loads the polyhedron from a file. the file must be in the format of Qhull qconvex output, called with these options :
    * \ "qconvex TI <input_filename> TO <output_filename> Qt o f"
    */
    SCH_API virtual void constructFromFile(const std::string& filename);

    /*!
    *  \brief Load the object from a binary archive
    *  \param filename path to the binary archive
    */
    SCH_API virtual void loadFromBinary(const std::string & filename);


    /*!
    *  \brief Save the object to a binary archive
    *  \param filename path to the binary archive
    */
    SCH_API virtual void saveToBinary(const std::string & filename);

    /*!
    *  \brief updates the fast access arrays, must be called after each polyhedron modification
    */
    SCH_API void updateFastArrays();

    SCH_API Point3 naiveSupport(const Vector3& v)const;

    /*!
    *  \brief updates the Neighborhood of the vertexes, must be called on polyhedron
    *  \which vertexes have no neighbors, or after calling clearNeighbors.
    */
    SCH_API void updateVertexNeighbors();

    /*!
    *  \brief clears the neighbors tables;
    */
    SCH_API void clearNeighbors();

    /*!
    *  \brief clears all the polyhedron;
    */
    SCH_API void clear();

    /*!
    * \brief deletes aal the vertexes that dont have neighbors;
    */
    SCH_API void deleteVertexesWithoutNeighbors();

    SCH_API int getTrianglesNumber() const;
    SCH_API Polyhedron_algorithms * getPolyhedronAlgorithm ()
    {
      return &poly;
    }

    template<class Archive>
    void save(Archive & ar, const unsigned int /*version*/) const
    {
      ar & boost::serialization::base_object<S_ObjectNonNormalized>(*this);
      ar & poly;
    }

    template<class Archive>
    void load(Archive & ar, const unsigned int /*version*/)
    {
      ar & boost::serialization::base_object<S_ObjectNonNormalized>(*this);
      ar & poly;
      updateFastArrays();
      updateVertexNeighbors();
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()

  protected:
    SCH_API virtual Point3 l_Support(const Vector3& v, int& lastFeature)const;
    SCH_API virtual	S_ObjectType getType() const;

  protected:

    Polyhedron_algorithms poly;
  };
}
#endif

/**
 * \example      example2.cpp
 * This example shows the normal use of the SCH library:
 * More Complex Objects
 */
