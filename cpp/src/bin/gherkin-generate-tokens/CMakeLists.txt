add_executable(gherkin-generate-tokens-bin)

target_sources(
    gherkin-generate-tokens-bin
    PRIVATE
        gherkin-generate-tokens.cpp
)

target_include_directories(
    gherkin-generate-tokens-bin
    PRIVATE
        ./
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
