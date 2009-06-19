set(SOURCES 
  SimplestParsing.cpp
)


add_definitions( 
)

add_library( file_parsing SHARED ${SOURCES} )
SET_TARGET_PROPERTIES( file_parsing
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ../lib
)

