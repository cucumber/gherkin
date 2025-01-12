###
#
# Project
# name and version
#
###
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(cucumber_gherkin VERSION 30.0.4 LANGUAGES C CXX)

###
#
# Main project check
#
###
set(cucumber_gherkin_MAIN_PROJECT OFF)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(cucumber_gherkin_MAIN_PROJECT ON)
endif()

###
#
# Options
#
###
if(${CUCUMBER_GHERKIN_MAIN_PROJECT})
    set(CUCUMBER_GHERKIN_BUILD_TESTS_INIT ON)
    set(CUCUMBER_GHERKIN_EXPORT_COMPILE_INIT ON)
else()
    set(CUCUMBER_GHERKIN_BUILD_TESTS_INIT OFF)
    set(CUCUMBER_GHERKIN_EXPORT_COMPILE_INIT OFF)
endif()

option(
    CUCUMBER_GHERKIN_BUILD_TESTS
    "Build the unit tests."
    ${CUCUMBER_GHERKIN_BUILD_TESTS_INIT}
)

option(
    CUCUMBER_GHERKIN_EXPORT_COMPILE
    "Export compile commands."
    ${CUCUMBER_GHERKIN_EXPORT_COMPILE_INIT}
)

option(
    CUCUMBER_GHERKIN_FETCH_DEPS
    "Fetch dependencies via FetchContent."
    ${CUCUMBER_GHERKIN_FETCH_DEPS}
)

###
#
# Configuration
#
###
include(GNUInstallDirs)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS)
endif()

if(CUCUMBER_GHERKIN_EXPORT_COMPILE)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

###
#
# CMake dependencies
#
###
if(CUCUMBER_GHERKIN_FETCH_DEPS)
    include(FetchContent)

    FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
        OVERRIDE_FIND_PACKAGE
    )

    set(JSON_BuildTests "OFF")
    set(JSON_Install "ON")

    FetchContent_MakeAvailable(nlohmann_json)

    FetchContent_Declare(
        cucumber_messages
        GIT_REPOSITORY https://github.com/cucumber/messages.git
        GIT_TAG main
        OVERRIDE_FIND_PACKAGE
        SOURCE_SUBDIR "cpp"
    )
    FetchContent_MakeAvailable(cucumber_messages)
endif()

find_package(nlohmann_json CONFIG REQUIRED)
find_package(cucumber_messages CONFIG REQUIRED)

###
#
# Targets
#
###
add_subdirectory(src/lib/gherkin)
add_subdirectory(src/bin/gherkin)
add_subdirectory(src/bin/gherkin-generate-tokens)

###
#
# Installation support
#
###
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
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cucumber
)
