add_executable(gherkin-bin)

target_sources(
    gherkin-bin
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/bin/gherkin/gherkin.cpp
)

target_include_directories(
    gherkin-bin
    PRIVATE
        ${CMAKE_SOURCE_DIR}/
        ${CMAKE_SOURCE_DIR}/src/bin/gherkin
)

target_link_libraries(
    gherkin-bin
    PUBLIC
        gherkin-cpp
)

set_target_properties(
    gherkin-bin
    PROPERTIES
    OUTPUT_NAME gherkin
)
