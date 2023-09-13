add_executable(gherkin-generate-tokens-bin)

target_sources(
    gherkin-generate-tokens-bin
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src/bin/gherkin-generate-tokens/gherkin-generate-tokens.cpp
)

target_include_directories(
    gherkin-generate-tokens-bin
    PRIVATE
        ${CMAKE_SOURCE_DIR}/
        ${CMAKE_SOURCE_DIR}/src/bin/gherkin-generate-tokens
)

target_link_libraries(
    gherkin-generate-tokens-bin
    PUBLIC
        gherkin-cpp
)

set_target_properties(
    gherkin-generate-tokens-bin
    PROPERTIES
    OUTPUT_NAME gherkin-generate-tokens
)
