add_library(cucumber_gherkin_lib)
add_library(cucumber::gherkin ALIAS cucumber_gherkin_lib)

set(CUCUMBER_GHERKIN_LIB_INC_DIR "${PROJECT_SOURCE_DIR}/include/gherkin")
set(CUCUMBER_GHERKIN_LIB_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cucumber/gherkin")

target_sources(
    cucumber_gherkin_lib
    PRIVATE
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/App.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/AstBuilder.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/AstNode.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/CbTypes.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/Demangle.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/Dialect.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/Exceptions.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/File.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/IdGenerator.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/Items.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/JoinUtils.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/Keywords.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/Line.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/Log.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/MsgTypes.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/ParseError.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/Parser.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/ParserBase.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/ParserContext.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/ParserInfo.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/PickleCompiler.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/PickleCompilerContext.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/Regex.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/RuleType.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/Token.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/TokenFormatterBuilder.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/TokenMatcher.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/TokenScanner.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/TypeTraits.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/Types.hpp
        ${CUCUMBER_GHERKIN_LIB_INC_DIR}/cucumber/gherkin/Utils.hpp
        ${CUCUMBER_GHERKIN_LIB_SRC_DIR}/App.cpp
        ${CUCUMBER_GHERKIN_LIB_SRC_DIR}/AstBuilder.cpp
        ${CUCUMBER_GHERKIN_LIB_SRC_DIR}/AstNode.cpp
        ${CUCUMBER_GHERKIN_LIB_SRC_DIR}/Demangle.cpp
        ${CUCUMBER_GHERKIN_LIB_SRC_DIR}/Dialect.cpp
        ${CUCUMBER_GHERKIN_LIB_SRC_DIR}/Exceptions.cpp
        ${CUCUMBER_GHERKIN_LIB_SRC_DIR}/IdGenerator.cpp
        ${CUCUMBER_GHERKIN_LIB_SRC_DIR}/Keywords.cpp
        ${CUCUMBER_GHERKIN_LIB_SRC_DIR}/Line.cpp
        ${CUCUMBER_GHERKIN_LIB_SRC_DIR}/ParseError.cpp
        ${CUCUMBER_GHERKIN_LIB_SRC_DIR}/PickleCompiler.cpp
        ${CUCUMBER_GHERKIN_LIB_SRC_DIR}/PickleCompilerContext.cpp
        ${CUCUMBER_GHERKIN_LIB_SRC_DIR}/Regex.cpp
        ${CUCUMBER_GHERKIN_LIB_SRC_DIR}/RuleType.cpp
        ${CUCUMBER_GHERKIN_LIB_SRC_DIR}/Token.cpp
        ${CUCUMBER_GHERKIN_LIB_SRC_DIR}/TokenFormatterBuilder.cpp
        ${CUCUMBER_GHERKIN_LIB_SRC_DIR}/TokenMatcher.cpp
        ${CUCUMBER_GHERKIN_LIB_SRC_DIR}/TokenScanner.cpp
        ${CUCUMBER_GHERKIN_LIB_SRC_DIR}/Utils.cpp
)

target_include_directories(
    cucumber_gherkin_lib
    PUBLIC
        $<BUILD_INTERFACE:${CUCUMBER_GHERKIN_LIB_INC_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    cucumber_gherkin_lib
    PUBLIC
        nlohmann_json::nlohmann_json
        cucumber::messages
)

set_target_properties(
    cucumber_gherkin_lib
    PROPERTIES
        VERSION ${VERSION}
        SOVERSION ${VER_MAJOR}
        EXPORT_NAME gherkin
        OUTPUT_NAME cucumber_gherkin
)
