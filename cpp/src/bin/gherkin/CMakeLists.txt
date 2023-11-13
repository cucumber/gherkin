add_executable(gherkin-bin)

target_sources(
    gherkin-bin
    PRIVATE
        gherkin.cpp
)

target_include_directories(
    gherkin-bin
    PRIVATE
        ./
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
