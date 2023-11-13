add_library(gherkin-cpp)
add_library(gherkin::gherkin-cpp ALIAS gherkin-cpp)

set(INC_DIR "${CMAKE_SOURCE_DIR}/include")

# We prefer it that way...
file(GLOB_RECURSE GHERKIN_CPP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.[ch]pp)

target_sources(
    gherkin-cpp
    PRIVATE
        ${GHERKIN_CPP_SOURCES}
)

target_link_libraries(
    gherkin-cpp
    PUBLIC
        cucumber::messages
        nlohmann_json::nlohmann_json
        gherkin::gherkin-cpp-include
)

set_target_properties(
    gherkin-cpp
    PROPERTIES
    OUTPUT_NAME gherkin-cpp
)
