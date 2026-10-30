add_executable(cucumber_gherkin_benchmark Benchmark.cpp)

target_link_libraries(cucumber_gherkin_benchmark PRIVATE cucumber::gherkin)
configure_file(benchmark.feature benchmark.feature COPYONLY)

target_compile_definitions(cucumber_gherkin_benchmark PRIVATE
    GHERKIN_BENCHMARK_FEATURE="${CMAKE_CURRENT_BINARY_DIR}/benchmark.feature"
)

if(CUCUMBER_GHERKIN_HAS_RE2)
    target_compile_definitions(cucumber_gherkin_benchmark PRIVATE GHERKIN_REGEX_BACKEND="RE2")
else()
    target_compile_definitions(cucumber_gherkin_benchmark PRIVATE GHERKIN_REGEX_BACKEND="std::regex")
endif()

add_custom_target(
    run_cucumber_gherkin_benchmark
    COMMAND $<TARGET_FILE:cucumber_gherkin_benchmark> 100
    DEPENDS cucumber_gherkin_benchmark
    COMMENT "Running cucumber gherkin benchmark"
    USES_TERMINAL
    VERBATIM
)

if(CUCUMBER_GHERKIN_BUILD_TESTS)
    add_test(NAME Benchmark.Smoke COMMAND cucumber_gherkin_benchmark 1)
    set_tests_properties(Benchmark.Smoke PROPERTIES
        PASS_REGULAR_EXPRESSION "backend,iterations,files,bytes_per_iteration,seconds,documents_per_second,MiB_per_second,checksum"
    )
    add_test(NAME Benchmark.RejectsInvalidIterations COMMAND cucumber_gherkin_benchmark 0)
    set_tests_properties(Benchmark.RejectsInvalidIterations PROPERTIES WILL_FAIL TRUE)
endif()
