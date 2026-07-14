# renovate
set(CPM_DOWNLOAD_VERSION 0.43.1)
# renovate: datasource=github-tags packageName=cucumber/messages versioning=semver
set(CUCUMBER_MESSAGES_HASH_VERSION 79002c8940c9dcaa09d96db4d5a320d0f6806b7a 34.0.2)

list(GET CUCUMBER_MESSAGES_HASH_VERSION 0 CUCUMBER_MESSAGES_HASH)
list(GET CUCUMBER_MESSAGES_HASH_VERSION 1 CUCUMBER_MESSAGES_VERSION)

if(CUCUMBER_GHERKIN_FETCH_DEPS)
    if(NOT COMMAND CPMAddPackage)
        # ---------------------------------------------------------------------------
        # CPM – download on first configure if not already cached (standalone only)
        # ---------------------------------------------------------------------------
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
        URI "gh:cucumber/messages@${CUCUMBER_MESSAGES_VERSION}#${CUCUMBER_MESSAGES_HASH}"
        NAME cucumber_messages
        SOURCE_SUBDIR cpp
        OPTIONS
            "CUCUMBER_MESSAGES_FETCH_DEPS ON"
    )

    if(cucumber_messages_ADDED)
        # Propagate cucumber_messages install rules so 'cmake --install' also installs it
        install(SCRIPT "${cucumber_messages_BINARY_DIR}/cmake_install.cmake")
    endif()

else()
    find_package(cucumber_messages ${CUCUMBER_MESSAGES_VERSION} REQUIRED)
endif()
