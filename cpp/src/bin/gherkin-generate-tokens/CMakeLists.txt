add_executable(cucumber_gherkin_generate_tokens_bin)

set(CUCUMBER_GHERKIN_GENERATE_TOKENS_BIN_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB_RECURSE CUCUMBER_GHERKIN_GENERATE_TOKENS_BIN_SOURCES "${CUCUMBER_GHERKIN_GENERATE_TOKENS_BIN_SRC_DIR}/*.[ch]pp")
list(APPEND CUCUMBER_GHERKIN_GENERATE_TOKENS_BIN_ALL_SOURCES ${CUCUMBER_GHERKIN_GENERATE_TOKENS_BIN_SOURCES})

target_sources(
    cucumber_gherkin_generate_tokens_bin
    PRIVATE
        ${CUCUMBER_GHERKIN_GENERATE_TOKENS_BIN_ALL_SOURCES}
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
        CXX_STANDARD 20
        OUTPUT_NAME gherkin-generate-tokens
)
