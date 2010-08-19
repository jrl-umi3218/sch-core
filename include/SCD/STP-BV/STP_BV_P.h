#pragma once
#include <SCD/STP-BV/STP_BV.h>
#include <SCD/S_Polyhedron/Polyhedron_algorithms.h>

namespace SCD
{
	class STP_BV_P :
		public STP_BV
	{
	public:		

		STP_BV_P(void);
		
		virtual Point3  l_Support(const Vector3& v, int& lastFeature)const;

		/*!
		*  \brief Constructs the object from a file describing its STP_BV decomposition
		*  \param filename path to the file describing the STP_BV decomposition of the object 
		*  \another file in the same folder with the same name but with ".otp" at the end must exist must be 
		*  \ in the format of Qhull conconvex.exe output, called with these options : 
		*  \ "qconvex.exe TI <input_filename> TO <output_filename> Qt o f" it will describe the convex hull of the polyhedric shape of the stpbv
		*  \ (example: in the folder : "home\" there are two files ; the STP_BV file : "home\STPBV.txt", and the Qhull output : "home\STPBV.txt.otp")
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
