add_library(gherkin-cpp)
add_library(gherkin::gherkin-cpp ALIAS gherkin-cpp)

set(INC_DIR "${CMAKE_SOURCE_DIR}/include")

target_sources(
    gherkin-cpp
    PUBLIC
    FILE_SET
        "gherkin_cpp_headers"
        TYPE HEADERS
        BASE_DIRS ${INC_DIR}
        FILES
        ${INC_DIR}/gherkin/ast_builder.hpp
        ${INC_DIR}/gherkin/file.hpp
        ${INC_DIR}/gherkin/dialect.hpp
        ${INC_DIR}/gherkin/items.hpp
        ${INC_DIR}/gherkin/line.hpp
        ${INC_DIR}/gherkin/location.hpp
        ${INC_DIR}/gherkin/parser.hpp
        ${INC_DIR}/gherkin/rule_type.hpp
        ${INC_DIR}/gherkin/token.hpp
        ${INC_DIR}/gherkin/token_matcher.hpp
        ${INC_DIR}/gherkin/token_scanner.hpp
        ${INC_DIR}/gherkin/utils.hpp
        ${INC_DIR}/gherkin/types.hpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/ast_builder.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/dialect.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/parser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/token.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/token_matcher.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/token_scanner.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/utils.cpp
)

target_include_directories(
    gherkin-cpp
    PUBLIC
        $<BUILD_INTERFACE:${INC_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/gherkin>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    gherkin-cpp
    PRIVATE
        cucumber::cucumber-messages
)

set_target_properties(
    gherkin-cpp
    PROPERTIES
    OUTPUT_NAME gherkin-cpp
)

