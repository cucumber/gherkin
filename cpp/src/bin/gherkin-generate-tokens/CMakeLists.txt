add_executable(cucumber_gherkin_generate_tokens_bin)

target_sources(
    cucumber_gherkin_generate_tokens_bin
    PRIVATE
        GherkinGenerateTokens.cpp
)

target_include_directories(
    cucumber_gherkin_generate_tokens_bin
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    cucumber_gherkin_generate_tokens_bin
    PUBLIC
        cucumber::gherkin
)

set_target_properties(
    cucumber_gherkin_generate_tokens_bin
    PROPERTIES
        OUTPUT_NAME gherkin-generate-tokens
)
