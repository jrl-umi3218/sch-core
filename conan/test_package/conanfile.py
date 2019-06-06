from conans import ConanFile, CMake, tools
import os
import subprocess

class SCHCoreTestConan(ConanFile):
    requires = "sch-core/1.0.0@gergondet/stable"
    settings = "os", "arch", "compiler", "build_type"
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        if not tools.cross_building(self.settings):
            os.chdir("bin")
            self.run(".%sexample" % os.sep)
