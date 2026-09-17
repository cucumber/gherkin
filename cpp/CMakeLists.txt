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

# Options
if (POLICY CMP0077)
    # Allow CMake 3.13+ to override options when using FetchContent / add_subdirectory.
    cmake_policy(SET CMP0077 NEW)
endif ()

option(CUCUMBER_GHERKIN_ENABLE_CLANG_TIDY "Run clang-tidy as part of the build." Off)
option(CUCUMBER_GHERKIN_ENABLE_COVERAGE "Enable compiler flags for code coverage measurements." Off)
option(CUCUMBER_GHERKIN_ENABLE_SANITIZERS "Enable compiler flags for the address and undefined behaviour sanitizers." Off)

if(CUCUMBER_GHERKIN_ENABLE_SANITIZERS AND CUCUMBER_GHERKIN_ENABLE_COVERAGE)
    message(FATAL_ERROR "CUCUMBER_GHERKIN_ENABLE_SANITIZERS and CUCUMBER_GHERKIN_ENABLE_COVERAGE are mutually exclusive.")
endif()

if(CUCUMBER_GHERKIN_ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_PROGRAM clang-tidy REQUIRED)
endif()

if(CUCUMBER_GHERKIN_ENABLE_COVERAGE)
    find_program(GCOVR_PROGRAM gcovr REQUIRED)

    add_custom_target(
        generate-lcov-report
        COMMAND ${GCOVR_PROGRAM} --version
        COMMAND ${GCOVR_PROGRAM} --root ${CMAKE_CURRENT_SOURCE_DIR} --merge-lines --delete --exclude-unreachable-branches --exclude-throw-branches --exclude-noncode-lines --filter include/ --filter src/
            --txt-summary
            --lcov ${CMAKE_CURRENT_BINARY_DIR}/lcov.info
            --cobertura ${CMAKE_CURRENT_BINARY_DIR}/cobertura.xml --cobertura-pretty
            --markdown-summary ${CMAKE_CURRENT_BINARY_DIR}/coverage-summary.md
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating code coverage reports"
    )
endif()

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
find_package(nlohmann_json REQUIRED)
if (NOT TARGET cucumber::messages)
    find_package(cucumber_messages REQUIRED)
endif()

# Target options
if(CUCUMBER_GHERKIN_ENABLE_CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_PROGRAM}")
endif()

if(CUCUMBER_GHERKIN_ENABLE_COVERAGE)
    add_compile_options(
        -g -O0 --coverage -fprofile-arcs -ftest-coverage -fno-inline
        $<$<COMPILE_LANGUAGE:CXX>:-fno-elide-constructors>
    )

    if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
        link_libraries(gcov)
    else()
        add_link_options(--coverage)
    endif()
endif()

if(CUCUMBER_GHERKIN_ENABLE_SANITIZERS)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_compile_options(-fsanitize=address -fsanitize=undefined)
        add_link_options(-fsanitize=address -fsanitize=undefined)
    endif()
endif()

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
