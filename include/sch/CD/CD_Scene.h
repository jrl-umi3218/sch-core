#ifndef _CD_SCENE
#define _CD_SCENE

#pragma once



#include <vector>
#include <sch/sch_api.h>
#include <sch/S_Object/S_Object.h>
#include <sch/CD/CD_Pair.h>


namespace sch
{
  class CD_Scene
  {
  public:
    SCH_API CD_Scene(void);
    SCH_API virtual ~CD_Scene(void);

    /*!
    * \brief Add Object to scene, returns an index that must be kept for collision detection
    */
    SCH_API int addObject(S_Object* O);

    /*!
    * \brief Withdraw an object
    */
    SCH_API void withdrawObject( int a);

    SCH_API void ignorePair( int a, int b);

    SCH_API void considerPair( int a, int b);

    SCH_API CD_Pair* operator()( int a, int b) const
    {
      if (a!=b)
      {
        return (b<a)? pairs_[a][b]:pairs_[b][a];
      }
      else
        return NULL;
    }


    SCH_API int  sceneProximityQuery();

    SCH_API S_Object * operator[](size_t i)const
    {
      return objects_[i];
    }

    SCH_API size_t size()
    {
      return objects_.size();
    }


    /*!
    *\brief Doesn't Compute the closest points, just gives the result of last computations.
    */
    SCH_API Scalar getWitnessPoints(int a, int b,Point3 &p1,Point3 &p2)
    {
      if (a!=b)
      {
        p1=witness_[a][b];
        p2=witness_[b][a];
        return distances_[a][b];
      }
      else
      {
        return 0;
      }
    }


  protected:
    std::vector <S_Object*> objects_;

    std::vector <std::vector <CD_Pair*> > pairs_;

    std::vector <std::vector <Point3 > > witness_;

    std::vector <std::vector <Scalar > > distances_;
  };
}
#endif

/**
* \example      example1.cpp
* This example shows the normal use of the SCH library:
* Scene managements
*/
