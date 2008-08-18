#pragma once
#include "stp_bv.h"
#include "..\s_Polyhedron\polyhedron_algorithms.h"

namespace SCD
{
	class STP_BV_P :
		public STP_BV
	{
	public:		

		STP_BV_P(void);
		
		virtual Point3  n_Support(const Vector3& v, int& lastFeature)const;

		/*!
		*  \brief Constructs the object from a file describing its STP_BV decomposition
		*  \param filename path to the file describing the STP_BV decomposition of the object
		*
		*/
		virtual void constructFromFile(const std::string& filename);


		/*!
		*  \brief Constructs the object from a file describing its STP_BV decomposition
		*  \param filename path to the file describing the STP_BV decomposition of the object
		*
		* This method computes all the needed data for display and every distance calculation method.
		*/
		virtual void constructFromFileWithGL(const std::string& filename);

		virtual void drawGLInLocalCordinates();

		virtual ~STP_BV_P(void);

		virtual S_ObjectType getType() const;




	private:
		Polyhedron_algorithms poly;


	};
}