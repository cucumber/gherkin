set(NLOHMANN_JSON_VERSION 3.12.0 CACHE STRING "Version of nlohmann_json to use")
set(CUCUMBER_MESSAGES_VERSION 34.0.2 CACHE STRING "Version of cucumber_messages to use")

if(CUCUMBER_GHERKIN_FETCH_DEPS)
    if(NOT COMMAND CPMAddPackage)
        # ---------------------------------------------------------------------------
        # CPM – download on first configure if not already cached (standalone only)
        # ---------------------------------------------------------------------------
        set(CPM_DOWNLOAD_VERSION 0.40.2)
        set(CPM_USE_LOCAL_PACKAGES ON)
        set(CPM_DOWNLOAD_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

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
        GIT_TAG v${NLOHMANN_JSON_VERSION}
        OPTIONS "JSON_BuildTests Off" "JSON_Install ON"
    )

    if(TARGET nlohmann_json)
        set_target_properties(nlohmann_json PROPERTIES SYSTEM ON)
    endif()

    if(nlohmann_json_ADDED)
        # Make the generated config file discoverable by cucumber_messages' find_package()
        list(APPEND CMAKE_PREFIX_PATH "${nlohmann_json_BINARY_DIR}")
        if(NOT PROJECT_IS_TOP_LEVEL)
            set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}" PARENT_SCOPE)
        endif()
    endif()

    CPMAddPackage(
        NAME cucumber_messages
        GITHUB_REPOSITORY cucumber/messages
        GIT_TAG v${CUCUMBER_MESSAGES_VERSION}
        SOURCE_SUBDIR cpp
        SYSTEM
        OPTIONS "CUCUMBER_MESSAGES_FETCH_DEPS ON"
    )

else()
    find_package(nlohmann_json ${NLOHMANN_JSON_VERSION} REQUIRED)
    find_package(cucumber_messages ${CUCUMBER_MESSAGES_VERSION} REQUIRED)
endif()
