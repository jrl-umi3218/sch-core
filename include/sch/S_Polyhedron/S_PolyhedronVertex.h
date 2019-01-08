#ifndef _S_POLYHEDRONVERTEX
#define _S_POLYHEDRONVERTEX

#pragma once
#include <vector>

#include <boost/noncopyable.hpp>

#include <sch/sch_api.h>
#include <sch/core/deprecated.hh>
#include <sch/Matrix/SCH_Types.h>

namespace sch
{
  class S_PolyhedronVertex : boost::noncopyable
  {
  public:
    SCH_API S_PolyhedronVertex(void);
    SCH_API virtual ~S_PolyhedronVertex(void);

    SCH_API void addNeighbor(S_PolyhedronVertex*);

    SCH_API Scalar supportH(const Vector3& direction)const;

    SCH_API SCH_CORE_DEPRECATED void setCordinates(const Vector3& v);
    SCH_API void setCoordinates(const Vector3& v);

    SCH_API SCH_CORE_DEPRECATED void setCordinates(const Scalar& x,const Scalar& y,const Scalar& z);
    SCH_API void setCoordinates(const Scalar& x,const Scalar& y,const Scalar& z);

    SCH_API SCH_CORE_DEPRECATED const Vector3& getCordinates()const;
    SCH_API const Vector3& getCoordinates()const;

    /*!
    *  \brief Gives a copy of the current vertex, without the neighbors array, keeping just the cordinates and the number
    */
    SCH_API virtual S_PolyhedronVertex* clone();

    /*!
    * \brief clears the Neighbors
    */
    SCH_API void clearNeighbors();


    /*!
    * \brief checks if this is the support point of the polyhedron in some given direction
    * \param direction the direction vector
    * \param cuurentsupportH, is the support height of this points, usually given by a neighbor
    * \return returns a boolean answer and stores the next vertex and its support height in case it is not the support
    */
    SCH_API virtual bool isHere(const Vector3& direction, const Scalar& currentsupportH);


    /*!
    * \brief checks if this is the support point of the polyhedron in some given direction
    * \param direction the direction vector
    * \return returns a boolean answer and stores the next vertex and its support height in case it is not the support
    */
    SCH_API virtual bool isHere(const Vector3& direction);

    /*!
    * \brief updates fast access neighbors array, must be called at each neighbors modification
    */
    SCH_API void updateFastArrays();

    /*!
    * \brief sets the number of the vertex in the polyhedron
    */
    SCH_API void setNumber(unsigned int);

    /*!
    * \brief gets the number of the vertex in the polyhedron
    */
    SCH_API unsigned int getNumber()const;

    /*!
    * \brief gets the next vertex in a support point search
    */
    SCH_API S_PolyhedronVertex* getNextVertex()const;

    /*!
    * \brief gets the next vertex support height
    */
    SCH_API Scalar getNextVertexH()const;

    /*!
    * \brief gets the number of neighbors
    */
    SCH_API unsigned getNumNeighbors()const;

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
