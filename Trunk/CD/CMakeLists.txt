set(SOURCES 
  CD_Pair.cpp
  CD_Scene.cpp
  CD_Simplex.cpp
  CD_SimplexEnhanced.cpp
)


add_definitions( 
)

ADD_LIBRARY( cd SHARED ${SOURCES} )
SET_TARGET_PROPERTIES( cd
    PROPERTIES
    COMPILE_FLAGS ${${PROJECT_NAME}_CXXFLAGS}
)
