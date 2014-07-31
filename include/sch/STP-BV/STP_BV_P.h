#ifndef STP_VB_P_HEADER
#define STP_VB_P_HEADER

#pragma once


#include <sch/sch_api.h>
#include <sch/STP-BV/STP_BV.h>
#include <sch/S_Polyhedron/Polyhedron_algorithms.h>

namespace sch
{
  class STP_BV_P :
    public STP_BV
  {
  public:
    SCH_API STP_BV_P(void);

    SCH_API virtual Point3  l_Support(const Vector3& v, int& lastFeature)const;

    /*!
    *  \brief Constructs the object from a file describing its STP_BV decomposition
    *  \param filename path to the file describing the STP_BV decomposition of the object
    *  \another file in the same folder with the same name but with ".otp" at the end must exist must be
    *  \ in the format of Qhull conconvex.exe output, called with these options :
    *  \ "qconvex.exe TI <input_filename> TO <output_filename> Qt o f" it will describe the convex hull of the polyhedric shape of the stpbv
    *  \ (example: in the folder : "home\" there are two files ; the STP_BV file : "home\STPBV.txt", and the Qhull output : "home\STPBV.txt.otp")
    *
    */
    SCH_API virtual void constructFromFile(const std::string& filename);

    SCH_API virtual ~STP_BV_P(void);

    SCH_API virtual S_ObjectType getType() const;

  private:
    Polyhedron_algorithms poly;
  };
}

#endif

/**
 * \example      example2.cpp
 * This example shows the normal use of the SCH library:
 * More Complex Objects
 */
