# -*- coding: utf-8 -*-
#
# Copyright 2012-2019 CNRS-UM LIRMM, CNRS-AIST JRL
#

from conans import ConanFile, CMake, tools
import os
import shutil

class SCHCoreConan(ConanFile):
    name = "sch-core"
    version = "1.0.0"
    description = "Efficient implementation of GJK algorithm for proximity queries (collision detection, distance computations, penetration depths and witness points) between convex shapes."
    topics = ("robotics", "collision", "proximity", "convex")
    url = "https://github.com/jrl-umi3218/sch-core"
    homepage = "https://github.com/jrl-umi3218/sch-core"
    author = "Pierre Gergondet <pierre.gergondet@gmail.com>"
    license = "BSD-2-Clause"
    exports = ["LICENSE"]
    exports_sources = ["CMakeLists.txt", "conan/CMakeLists.txt", "cmake/*", "CMakeModules/*", "doc/*", "examples/*", "include/*", "src/*", "README.md"]
    generators = "cmake"
    settings = "os", "arch", "compiler", "build_type"

    requires = (
        # We don't really care for a specific version of Boost and conan has >= 1.64
        "boost/[>1.63]@conan/stable"
    )

    def source(self):
        # Wrap the original CMake file to call conan_basic_setup
        shutil.move("CMakeLists.txt", "CMakeListsOriginal.txt")
        shutil.move(os.path.join("conan", "CMakeLists.txt"), "CMakeLists.txt")

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.definitions['DISABLE_TESTS'] = True
        cmake.definitions['BUILD_BSD'] = True
        cmake.configure()
        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

    def deploy(self):
        self.copy("*")
        self.copy_deps("*")

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
        self.env_info.LD_LIBRARY_PATH.append(os.path.join(self.package_folder, 'lib'))
