add_library(cucumber_gherkin_lib)
add_library(cucumber::gherkin ALIAS cucumber_gherkin_lib)

set(CUCUMBER_GHERKIN_LIB_INC_DIR "${PROJECT_SOURCE_DIR}/include/gherkin")
file(GLOB_RECURSE CUCUMBER_GHERKIN_LIB_HEADERS "${CUCUMBER_GHERKIN_LIB_INC_DIR}/*.hpp")
list(APPEND CUCUMBER_GHERKIN_LIB_ALL_SOURCES ${CUCUMBER_GHERKIN_LIB_HEADERS})

set(CUCUMBER_GHERKIN_LIB_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB_RECURSE CUCUMBER_GHERKIN_LIB_SOURCES "${CUCUMBER_GHERKIN_LIB_SRC_DIR}/*.[ch]pp")
list(APPEND CUCUMBER_GHERKIN_LIB_ALL_SOURCES ${CUCUMBER_GHERKIN_LIB_SOURCES})

target_sources(
    cucumber_gherkin_lib
    PRIVATE
        ${CUCUMBER_GHERKIN_LIB_ALL_SOURCES}
)

target_include_directories(
    cucumber_gherkin_lib
    PUBLIC
        $<BUILD_INTERFACE:${CUCUMBER_GHERKIN_LIB_INC_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/cucumber>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    cucumber_gherkin_lib
    PUBLIC
        nlohmann_json::nlohmann_json
        cucumber::messages
)

set_target_properties(
    cucumber_gherkin_lib
    PROPERTIES
        CXX_STANDARD 20
        VERSION 30.0.4
        SOVERSION 30
        EXPORT_NAME gherkin
        OUTPUT_NAME cucumber_gherkin
)
