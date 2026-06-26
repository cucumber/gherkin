# ---------------------------------------------------------------------------
# CPM – download on first configure if not already cached (standalone only)
# ---------------------------------------------------------------------------
if(CUCUMBER_GHERKIN_FETCH_DEPS)
    set(CPM_DOWNLOAD_VERSION 0.40.2)
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

CPMAddPackage(
    NAME cucumber_messages
    GITHUB_REPOSITORY cucumber/messages
    GIT_TAG 572d419f3ba14bbeb7123714a9e4f74698bc3363 #cpp-remove-cmate-use-native-cmake-and-CPM
    SOURCE_SUBDIR cpp
    SYSTEM
)
