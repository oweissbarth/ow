import os

from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.files import copy


class ImGuiExample(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("tinygltf/2.5.0")
        self.requires("pcg-cpp/cci.20210406")
        self.requires("glad/0.1.35")
        self.requires("sdl/2.26.5")
        self.requires("imgui/1.89.4")
        self.requires("catch2/3.3.2")
        self.requires("glm/cci.20230113")
        self.requires("stb/cci.20220909")

    def configure(self):
        self.options["glad"].gl_profile = "core"
        self.options["glad"].gl_version = "4.6"
        self.options["glad"].spec = "gl"
        self.options["glad"].no_loader = False

        self.options["sdl"].pulse = False
        self.options["sdl"].alsa = False
        self.options["sdl"].opengles = False


    def generate(self):
        copy(self, "*SDL2*", os.path.join(self.dependencies["imgui"].package_folder,
            "res", "bindings"), os.path.join(self.source_folder, "examples/imgui/imgui/bindings"))
        copy(self, "*opengl3*", os.path.join(self.dependencies["imgui"].package_folder,
            "res", "bindings"), os.path.join(self.source_folder, "examples/imgui/imgui/bindings"))

