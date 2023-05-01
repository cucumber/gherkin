cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(gherkin-cpp VERSION 1.0.0 LANGUAGES C CXX)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(src/lib/gherkin)

install(
    TARGETS
        gherkin-cpp_library
    EXPORT gherkin-cpp-config
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    EXPORT gherkin-cpp-config
    FILE gherkin-cpp-config.cmake
    NAMESPACE gherkin-cpp::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/gherkin-cpp
)
