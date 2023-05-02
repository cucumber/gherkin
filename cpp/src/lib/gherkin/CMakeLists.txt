add_library(gherkin-cpp_library)
add_library(weezu::gherkin-cpp ALIAS gherkin-cpp_library)

set(INC_DIR "${CMAKE_SOURCE_DIR}/include")

target_sources(
    gherkin-cpp_library
    PRIVATE
        ${INC_DIR}/gherkin/ast_builder.hpp
        ${INC_DIR}/gherkin/file.hpp
        ${INC_DIR}/gherkin/i18n.hpp
        ${INC_DIR}/gherkin/line.hpp
        ${INC_DIR}/gherkin/location.hpp
        ${INC_DIR}/gherkin/parser.hpp
        ${INC_DIR}/gherkin/rule_type.hpp
        ${INC_DIR}/gherkin/token.hpp
        ${INC_DIR}/gherkin/token_matcher.hpp
        ${INC_DIR}/gherkin/token_scanner.hpp
        ${INC_DIR}/gherkin/types.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ast_builder.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/i18n.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/parser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/token.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/token_matcher.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/token_scanner.cpp
)

target_include_directories(
    gherkin-cpp_library
    PUBLIC
        $<BUILD_INTERFACE:${INC_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/gherkin>
    PRIVATE
        ${INC_DIR}
)

set_target_properties(
    gherkin-cpp_library
    PROPERTIES
    OUTPUT_NAME gherkin-cpp
)

