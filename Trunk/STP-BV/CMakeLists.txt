project( STP-BV )

set(SOURCES 
  STP_BigSphere.cpp
  STP_BV.cpp
  STP_BV_P.cpp
  STP_Feature.cpp
  STP_SmallSphere.cpp
  STP_Torus.cpp
)


add_definitions( 
)

add_library( STP-BV STATIC ${SOURCES} )

