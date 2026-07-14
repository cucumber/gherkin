# renovate: datasource=github-tags packageName=cpm-cmake/CPM.cmake versioning=semver
set(CPM_DOWNLOAD_TAG_DIGEST v0.43.1 456cb6754daaa010d57444d0c8ce6d95ecf006ab)
# renovate: datasource=github-tags packageName=cucumber/messages versioning=semver
set(CUCUMBER_MESSAGES_TAG_DIGEST v34.0.0 bc887957a1d2dca415200a9a11f196a343ddc614)

list(GET CPM_DOWNLOAD_TAG_DIGEST 0 CPM_DOWNLOAD_TAG)
list(GET CPM_DOWNLOAD_TAG_DIGEST 1 CPM_DOWNLOAD_DIGEST)
string(SUBSTRING "${CPM_DOWNLOAD_TAG}" 1 -1 CPM_DOWNLOAD_VERSION)

list(GET CUCUMBER_MESSAGES_TAG_DIGEST 0 CUCUMBER_MESSAGES_TAG)
list(GET CUCUMBER_MESSAGES_TAG_DIGEST 1 CUCUMBER_MESSAGES_DIGEST)
string(SUBSTRING "${CUCUMBER_MESSAGES_TAG}" 1 -1 CUCUMBER_MESSAGES_VERSION)

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
                "https://github.com/cpm-cmake/CPM.cmake/releases/download/${CPM_DOWNLOAD_TAG}/CPM.cmake"
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
        URI "gh:cucumber/messages@${CUCUMBER_MESSAGES_VERSION}#${CUCUMBER_MESSAGES_DIGEST}"
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
