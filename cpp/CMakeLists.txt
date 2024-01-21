cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(cucumber_gherkin VERSION 0.1.0 LANGUAGES C CXX)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS)
endif()

find_package(nlohmann_json CONFIG REQUIRED)
find_package(cucumber_messages CONFIG REQUIRED)

add_subdirectory(src/lib/gherkin)
add_subdirectory(src/bin/gherkin)
add_subdirectory(src/bin/gherkin-generate-tokens)

install(
    TARGETS
        cucumber_gherkin_bin
        cucumber_gherkin_generate_tokens_bin
        cucumber_gherkin_lib
    EXPORT cucumber_gherkin-config
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    EXPORT cucumber_gherkin-config
    FILE cucumber_gherkin-config.cmake
    NAMESPACE cucumber::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cucumber_gherkin
)

install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/include/gherkin/"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cucumber
)
