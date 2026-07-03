# ---------------------------------------------------------------------------
# CPM – download on first configure if not already cached (standalone only)
# ---------------------------------------------------------------------------
if(NOT COMMAND CPMAddPackage)
    set(CPM_DOWNLOAD_VERSION 0.40.2)
    set(CPM_USE_LOCAL_PACKAGES ON)
    set(CPM_DOWNLOAD_LOCATION
        "${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

    if(NOT EXISTS "${CPM_DOWNLOAD_LOCATION}")
        message(STATUS "Downloading CPM.cmake ${CPM_DOWNLOAD_VERSION}…")
        file(DOWNLOAD
            "https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake"
            "${CPM_DOWNLOAD_LOCATION}"
            TLS_VERIFY ON
        )
    endif()

    include("${CPM_DOWNLOAD_LOCATION}")
endif()

# ---------------------------------------------------------------------------
# Dependencies
# ---------------------------------------------------------------------------
CPMAddPackage(
    NAME nlohmann_json
    GITHUB_REPOSITORY nlohmann/json
    GIT_TAG v3.12.0
    OPTIONS "JSON_BuildTests OFF" "JSON_Install ON"
    SYSTEM
)

if(TARGET nlohmann_json)
    set_target_properties(nlohmann_json PROPERTIES SYSTEM ON)
endif()

if(nlohmann_json_ADDED)
    # Make the generated config file discoverable by cucumber_messages' find_package()
    list(APPEND CMAKE_PREFIX_PATH "${nlohmann_json_BINARY_DIR}")
    if(NOT cucumber_messages_MAIN_PROJECT)
        set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}" PARENT_SCOPE)
    endif()
endif()


CPMAddPackage(
    NAME cucumber_messages
    GITHUB_REPOSITORY cucumber/messages
    GIT_TAG c34b8cf6412f274ac6943075326440b7e6062c81 #refactor-cpp-codegen
    SOURCE_SUBDIR cpp
    SYSTEM
)
