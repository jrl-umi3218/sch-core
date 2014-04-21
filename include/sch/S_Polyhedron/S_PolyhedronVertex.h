#ifndef _S_POLYHEDRONVERTEX
#define _S_POLYHEDRONVERTEX

#pragma once
#include <vector>

#include <boost/noncopyable.hpp>

#include <sch/sch_api.h>
#include <sch/Matrix/SCH_Types.h>

namespace sch
{
  class S_PolyhedronVertex : boost::noncopyable
  {
  public:
    sch_API S_PolyhedronVertex(void);
    sch_API virtual ~S_PolyhedronVertex(void);

    sch_API void addNeighbor(S_PolyhedronVertex*);

    sch_API Scalar supportH(const Vector3& direction)const;

    sch_API void setCordinates(const Vector3& v);

    sch_API void setCordinates(const Scalar& x,const Scalar& y,const Scalar& z);

    sch_API const Vector3& getCordinates()const;

    /*!
    *  \brief Gives a copy of the current vertex, without the neighbors array, keeping just the cordinates and the number
    */
    sch_API virtual S_PolyhedronVertex* clone();

    /*!
    * \brief clears the Neighbors
    */
    sch_API void clearNeighbors();


    /*!
    * \brief checks if this is the support point of the polyhedron in some given direction
    * \param direction the direction vector
    * \param cuurentsupportH, is the support height of this points, usually given by a neighbor
    * \return returns a boolean answer and stores the next vertex and its support height in case it is not the support
    */
    sch_API virtual bool isHere(const Vector3& direction, const Scalar& currentsupportH);


    /*!
    * \brief checks if this is the support point of the polyhedron in some given direction
    * \param direction the direction vector
    * \return returns a boolean answer and stores the next vertex and its support height in case it is not the support
    */
    sch_API virtual bool isHere(const Vector3& direction);

    /*!
    * \brief updates fast access neighbors array, must be called at each neighbors modification
    */
    sch_API void updateFastArrays();

    /*!
    * \brief sets the number of the vertex in the polyhedron
    */
    sch_API void setNumber(unsigned int);

    /*!
    * \brief gets the number of the vertex in the polyhedron
    */
    sch_API unsigned int getNumber()const;

    /*!
    * \brief gets the next vertex in a support point search
    */
    sch_API S_PolyhedronVertex* getNextVertex()const;

    /*!
    * \brief gets the next vertex support height
    */
    sch_API Scalar getNextVertexH()const;

    /*!
    * \brief gets the number of neighbors
    */
    sch_API unsigned getNumNeighbors()const;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int /*version*/)
    {
      ar & cordinates_;
      ar & neighbors_;
      //ar & fastNeighbors_;
      //ar & endNeighbors_;
      ar & number_;
      //ar & nextVertex_;
      ar & nextVertexH_;
    }

  private:

    Vector3 cordinates_;

    std::vector<S_PolyhedronVertex*> neighbors_;

    S_PolyhedronVertex** fastNeighbors_;
    S_PolyhedronVertex** endNeighbors_;
    unsigned int number_;

    S_PolyhedronVertex* nextVertex_;
    Scalar nextVertexH_;

  };


#include <sch/S_Polyhedron/S_PolyhedronVertex.hxx>
}
#endif
