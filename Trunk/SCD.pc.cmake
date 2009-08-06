prefix=${CMAKE_INSTALL_PREFIX}
exec_prefix=${CMAKE_INSTALL_PREFIX}/bin
libdir=${CMAKE_INSTALL_PREFIX}/lib
includedir=${CMAKE_INSTALL_PREFIX}/include
datarootdir=${CMAKE_INSTALL_PREFIX}/share
docdir=${CMAKE_INSTALL_PREFIX}/share/doc/${CMAKE_PROJECT_NAME}

Name: ${PROJECT_NAME}
Description: Library for collision detection computation
Version: 1.0
Libs: ${${PROJECT_NAME}_LDFLAGS} -lscd
Cflags: -I${install_pkg_include_dir}  ${${PROJECT_NAME}_CFLAGS}
