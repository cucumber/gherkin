from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.build import can_run, check_min_cppstd
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
import os

class CucumberGherkin(ConanFile):
    name = "cucumber_gherkin"
    version = "0.1.0"
    package_type = "library"

    license = "MIT"
    url = "https://github.com/cucumber/gherkin"
    homepage = "https://github.com/cucumber/gherkin"
    description = "Cucumber Gherkin for C++"
    topics = ("cucumber", "gherkin", "bdd", "json")

    settings = "os", "arch", "compiler", "build_type"
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
    }
    default_options = {
        "shared": False,
        "fPIC": True,
    }

    def set_version(self):
        version_file = os.path.join(self.recipe_folder, "VERSION")
        if os.path.exists(version_file):
            with open(version_file, "r", encoding="utf-8") as f:
                self.version = f.readline().strip()

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def requirements(self):
        self.requires("nlohmann_json/3.12.0")
        self.requires("cucumber_messages/34.2.1")

    def validate(self):
        check_min_cppstd(self, 17)

    def layout(self):
        cmake_layout(self)

    def generate(self):
        cmake_deps = CMakeDeps(self)
        cmake_deps.generate()

        cmake_toolchain = CMakeToolchain(self)
        cmake_toolchain.user_presets_path = False
        cmake_toolchain.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "cucumber_gherkin")
        self.cpp_info.set_property("cmake_target_name", "cucumber::gherkin")
        self.cpp_info.libs = ["cucumber_gherkin"]


    exports_sources = (
        "cmake/*",
        "include/*",
        "src/*",
        "CMakeLists.txt",
        "README.md",
        "VERSION",
    )
