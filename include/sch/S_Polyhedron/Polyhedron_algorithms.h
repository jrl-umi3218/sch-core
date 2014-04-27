#pragma once

#ifndef _POLYHEDRON_ALGORITHMS
#define _POLYHEDRON_ALGORITHMS

#include <sch/Matrix/SCH_Types.h>
#include <sch/S_Polyhedron/S_PolyhedronVertex.h>

#include <string>
#include <vector>

namespace sch
{
  struct PolyhedronTriangle
  {
    unsigned int a,b,c;
    Vector3 normal;
  public:
    template<class Archive>
    void serialize(Archive & ar, const unsigned int /*version*/)
    {
      ar & a;
      ar & b;
      ar & c;
      ar & normal;
    }
  };

  struct Polyhedron_algorithms
  {
  public:
    SCH_API Polyhedron_algorithms(void);
    SCH_API Polyhedron_algorithms(const Polyhedron_algorithms&);

    SCH_API ~Polyhedron_algorithms(void);

    SCH_API const Polyhedron_algorithms & operator=(const Polyhedron_algorithms&);

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

    /*!
    *\brief Computes the support point of the polyhedron
    */

    SCH_API Point3 support(const Vector3& v, int& lastFeature)const;

    /*!
    * \brief loads the polyhedron from a file. the file must be in the format of Qhull conconvex.exe output, called with these options :
    * \ "qconvex.exe TI <input_filename> TO <output_filename> Qt o f"
    */

    SCH_API void openFromFile(const std::string& filename);

    template<class Archive>
    void serialize(Archive & ar, const unsigned int /*version*/)
    {
      ar & vertexes_;
      ar & triangles_;
      //ar & fastVertexes_;
      //ar & lastVertexes_;
    }

    std::vector<S_PolyhedronVertex*> vertexes_;

    std::vector<PolyhedronTriangle> triangles_;
    S_PolyhedronVertex ** fastVertexes_;
    S_PolyhedronVertex ** lastVertexes_;
  };
}

#endif
