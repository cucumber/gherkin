# The VERSION here is a placeholder; the real version is in the VERSION file.
set(VERSION 28.0.0)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION")
    file(STRINGS "VERSION" LINES)
    list(GET LINES 0 VERSION)
endif()

# Crude Semver parsing
if("${VERSION}" MATCHES "^([^\\.]+)\\.([^\\.]+)\\.([^\\.]+)$")
    set(VER_MAJOR ${CMAKE_MATCH_1})
    set(VER_MINOR ${CMAKE_MATCH_2})
    set(VER_PATCH ${CMAKE_MATCH_3})
else()
    message(FATAL_ERROR "unable to parse version: ${VERSION}")
endif()

cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(cucumber_gherkin VERSION ${VERSION} LANGUAGES CXX)

# Required so CMake can find the custom package/config helper modules in ./cmake.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Standalone check
if(PROJECT_IS_TOP_LEVEL)
    set(cucumber_gherkin_MAIN_PROJECT ON)
else()
    set(cucumber_gherkin_MAIN_PROJECT OFF)
endif()

# Options
if (POLICY CMP0077)
    # Allow CMake 3.13+ to override options when using FetchContent / add_subdirectory.
    cmake_policy(SET CMP0077 NEW)
endif ()

option(CUCUMBER_GHERKIN_FETCH_DEPS "Fetch dependencies via FetchContent." ${cucumber_gherkin_MAIN_PROJECT})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler cache
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    message(STATUS "Using ccache: ${CCACHE_PROGRAM}")
else()
    find_program(SCCACHE_PROGRAM sccache)
    if(SCCACHE_PROGRAM)
        set(CMAKE_CXX_COMPILER_LAUNCHER "${SCCACHE_PROGRAM}")
        message(STATUS "Using sccache: ${SCCACHE_PROGRAM}")
    endif()
endif()

# Configuration
include(GNUInstallDirs)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS)
endif()

# CMake dependencies
include(dependencies.cpm)

# Targets
add_subdirectory(src/lib/gherkin)
add_subdirectory(src/bin/gherkin)
add_subdirectory(src/bin/gherkin-generate-tokens)

# Installation support
include(CMakePackageConfigHelpers)

configure_package_config_file(
  "cmake/cucumber_gherkin-config.cmake.in"
  "${PROJECT_BINARY_DIR}/cucumber_gherkin-config.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/cucumber_gherkin"
  PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR
)

write_basic_package_version_file(
  "${PROJECT_BINARY_DIR}/cucumber_gherkin-config-version.cmake"
  COMPATIBILITY AnyNewerVersion
)

install(
    TARGETS
        cucumber_gherkin_lib
        cucumber_gherkin_bin
        cucumber_gherkin_generate_tokens_bin
    EXPORT cucumber_gherkin-targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    EXPORT cucumber_gherkin-targets
    FILE cucumber_gherkin-targets.cmake
    NAMESPACE cucumber::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/cucumber_gherkin"
)

install(
    FILES
        "${PROJECT_BINARY_DIR}/cucumber_gherkin-config.cmake"
        "${PROJECT_BINARY_DIR}/cucumber_gherkin-config-version.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/cucumber_gherkin"
)

install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/include/gherkin/"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
