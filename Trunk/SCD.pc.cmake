prefix=${CMAKE_INSTALL_PREFIX}
exec_prefix=${CMAKE_INSTALL_PREFIX}/bin
libdir=${CMAKE_INSTALL_PREFIX}/lib/${CMAKE_PROJECT_NAME}
includedir=${CMAKE_INSTALL_PREFIX}/include/${CMAKE_PROJECT_NAME}
datarootdir=${CMAKE_INSTALL_PREFIX}/share
docdir=${CMAKE_INSTALL_PREFIX}/share/doc/${CMAKE_PROJECT_NAME}

Name: ${PROJECT_NAME}
Description: Library for collision detection computation
Version: 1.0
Libs: ${${PROJECT_NAME}_LDFLAGS} -L${install_pkg_libdir} -lcd -lcd_penetration -lfile_parsing -ls_object -ls_polyhedron -lstp-bv
Cflags: -I${install_pkg_include_dir}  ${${PROJECT_NAME}_CFLAGS}
