cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(cucumber_gherkin VERSION 42.0.1 LANGUAGES CXX)

# Options
if(POLICY CMP0077)
    # Allow CMake 3.13+ to override options when using FetchContent / add_subdirectory.
    cmake_policy(SET CMP0077 NEW)
endif()

option(CUCUMBER_GHERKIN_ENABLE_CLANG_TIDY "Run clang-tidy as part of the build." Off)
option(CUCUMBER_GHERKIN_ENABLE_COVERAGE "Enable compiler flags for code coverage measurements." Off)
option(CUCUMBER_GHERKIN_ENABLE_SANITIZERS "Enable compiler flags for the address and undefined behaviour sanitizers." Off)
option(CUCUMBER_GHERKIN_BUILD_TESTS "Build Gherkin regression tests." Off)
option(CUCUMBER_GHERKIN_BUILD_BENCHMARKS "Build the Gherkin parser benchmark." Off)

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

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS)
endif()

# CMake dependencies
find_package(nlohmann_json REQUIRED)
if(NOT TARGET cucumber::messages)
    find_package(cucumber_messages REQUIRED)
endif()

# Debian/Ubuntu's libre2-dev may only provide pkg-config metadata.
set(CUCUMBER_GHERKIN_HAS_RE2 OFF)
set(CUCUMBER_GHERKIN_RE2_USES_PKG_CONFIG OFF)
find_package(re2 QUIET)
if(NOT TARGET re2::re2)
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(RE2 QUIET IMPORTED_TARGET re2)
        if(TARGET PkgConfig::RE2)
            add_library(re2::re2 ALIAS PkgConfig::RE2)
            set(CUCUMBER_GHERKIN_RE2_USES_PKG_CONFIG ON)
        endif()
    endif()
endif()

if(TARGET re2::re2)
    set(CUCUMBER_GHERKIN_HAS_RE2 ON)
else()
    message(STATUS "re2 not found, falling back to std::regex")
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

    if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
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
if(CUCUMBER_GHERKIN_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
if(CUCUMBER_GHERKIN_BUILD_BENCHMARKS)
    add_subdirectory(benchmark)
endif()

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
