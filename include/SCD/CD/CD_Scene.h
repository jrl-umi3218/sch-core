#ifndef _CD_SCENE
#define _CD_SCENE

#pragma once



#include <vector>
#include <SCD/scd_api.h>
#include <SCD/S_Object/S_Object.h>
#include <SCD/CD/CD_Pair.h>


namespace SCD
{
	class CD_Scene
	{
	public:
		SCD_API CD_Scene(void);
		SCD_API virtual ~CD_Scene(void);

		/*! 
		* \brief Add Object to scene, returns an index that must be kept for collision detection 
		*/
		SCD_API int addObject(S_Object* O);

		/*!
		* \brief Withdraw an object 
		*/
		SCD_API void withdrawObject( int a);

		SCD_API void ignorePair( int a, int b);

		SCD_API void considerPair( int a, int b);

		SCD_API CD_Pair* operator()( int a, int b) const
		{
			if (a!=b)
			{
				return (b<a)? pairs_[a][b]:pairs_[b][a];
			}
			else
				return NULL;
		}


		SCD_API int  sceneProximityQuery();

		SCD_API S_Object * operator[](unsigned char i)const
		{
			return objects_[i];
		}	

		SCD_API size_t size()
		{
			return objects_.size();
		}


		/*!
		*\brief Doesn't Compute the closest points, just gives the result of last computations.
		*/
		SCD_API Scalar getWitnessPoints(int a, int b,Point3 &p1,Point3 &p2)
		{
			if (a!=b)
			{
				if (b<a)
				{
					p1=witness_[a][b];
					p2=witness_[b][a];
					return distances_[a][b];
				}
				else
				{
					p1=witness_[b][a];
					p2=witness_[a][b];
					return distances_[b][a];
				}
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
