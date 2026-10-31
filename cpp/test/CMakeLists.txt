find_package(GTest REQUIRED)

add_executable(cucumber_gherkin.test TestRegex.cpp TestParser.cpp)
target_link_libraries(cucumber_gherkin.test PRIVATE cucumber::gherkin GTest::gmock_main)
target_compile_definitions(cucumber_gherkin.test PRIVATE TESTDATA_SRC="${PROJECT_SOURCE_DIR}/../testdata")

include(GoogleTest)
gtest_discover_tests(cucumber_gherkin.test)
