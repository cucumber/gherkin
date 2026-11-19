find_package(GTest REQUIRED)

add_executable(cucumber_gherkin.test TestRegex.cpp TestParser.cpp)
target_link_libraries(cucumber_gherkin.test PRIVATE cucumber::gherkin GTest::gmock_main)
target_compile_definitions(cucumber_gherkin.test PRIVATE TESTDATA_SRC="${PROJECT_SOURCE_DIR}/../testdata")

if(CUCUMBER_GHERKIN_HAS_RE2)
    target_compile_definitions(cucumber_gherkin.test PRIVATE GHERKIN_TEST_RE2)
endif()

include(GoogleTest)
gtest_discover_tests(cucumber_gherkin.test)
