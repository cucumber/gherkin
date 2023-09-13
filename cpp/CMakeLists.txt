cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(gherkin-cpp VERSION 1.0.0 LANGUAGES C CXX)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(cucumber-messages CONFIG REQUIRED)

add_subdirectory(src/lib/gherkin)
add_subdirectory(src/bin/gherkin)
add_subdirectory(src/bin/gherkin-generate-tokens)

install(
    TARGETS
        gherkin-cpp
        gherkin-bin
        gherkin-generate-tokens-bin
    EXPORT gherkin-cpp-config
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    DIRECTORY "${CMAKE_SOURCE_DIR}/include/"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/gherkin
)

install(
    EXPORT gherkin-cpp-config
    FILE gherkin-cpp-config.cmake
    NAMESPACE gherkin-cpp::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/gherkin-cpp
)
