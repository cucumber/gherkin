add_library(gherkin-cpp-include INTERFACE)
add_library(gherkin::gherkin-cpp-include ALIAS gherkin-cpp-include)

set(INC_DIR "${CMAKE_CURRENT_LIST_DIR}")

# We prefer it that way...
file(GLOB_RECURSE GHERKIN_CPP_HEADERS ${INC_DIR}/*.[ch]pp)

target_sources(
    gherkin-cpp-include
    PRIVATE
        ${GHERKIN_CPP_HEADERS}
)

target_include_directories(
    gherkin-cpp-include
    INTERFACE
        $<BUILD_INTERFACE:${INC_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/gherkin>
)

target_link_libraries(
    gherkin-cpp-include
    INTERFACE
        cucumber::messages
        nlohmann_json::nlohmann_json
)
