#include <SCD/S_Polyhedron/Polyhedron_algorithms.h>
#include <SCD/STP-BV/STP_BV.h>
#include "S_Object_gl.h"

//SCD_API virtual void drawGLInLocalCordinates(const S_Box *);

namespace SCD
{
	class STP_BV_GL: public S_Object_GL
	{
	public:
		STP_BV_GL(STP_BV *);
		/*
		*\brief Draws the Polyhedron in OpenGL
		*/
		virtual void drawGLInLocalCordinates();

	private:
		STP_BV * stpbv_;
		std::vector<int> displayList_;

		void computeDisplayList();
	};
}
