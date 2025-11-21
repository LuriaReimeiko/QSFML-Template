cmake_minimum_required(VERSION 3.16) # 3.16 required for Qt

# Enable Hot Reload for MSVC compilers if supported.
    if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
    endif()

# Set CXX Standard
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use the root directory's NAME as PROJECT_NAME
    get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    
# Create the project using CXX at PROJECT_NAME
    project(${PROJECT_NAME} LANGUAGES CXX)
    
# Add Qt and let it set itself up
    find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)
    qt_standard_project_setup()

# Automate everything
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTORCC ON)

# Find CXX files
    # Find all .cpp files in src/ and add them to executables
        file(GLOB_RECURSE SOURCES "src/*.cpp" "include/*.hpp")
        qt_add_executable(${PROJECT_NAME} ${SOURCES})
    # Include all headers in include/
        target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)


# Install CPM 0.42.0
    set(CPM_USE_LOCAL_PACKAGES ON)

    set(CPM_DOWNLOAD_VERSION 0.42.0)
    set(CPM_HASH_SUM "2020b4fc42dba44817983e06342e682ecfc3d2f484a581f11cc5731fbe4dce8a")

    if(CPM_SOURCE_CACHE)
        set(CPM_DOWNLOAD_LOCATION "${CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
    elseif(DEFINED ENV{CPM_SOURCE_CACHE})
        set(CPM_DOWNLOAD_LOCATION "$ENV{CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
    else()
        set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
    endif()

    # Expand relative path. This is important if the provided path contains a tilde (~)
    get_filename_component(CPM_DOWNLOAD_LOCATION ${CPM_DOWNLOAD_LOCATION} ABSOLUTE)

    file(DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
        ${CPM_DOWNLOAD_LOCATION} EXPECTED_HASH SHA256=${CPM_HASH_SUM}
    )

    include(${CPM_DOWNLOAD_LOCATION})

# CPMAddPackage
    # Add SFML 3.0.2
    CPMAddPackage(
        NAME SFML
        GITHUB_REPOSITORY SFML/SFML
        GIT_TAG 3.0.2
        OPTIONS
            "SFML_BUILD_EXAMPLES OFF"
            "SFML_BUILD_TEST_SUITE OFF"
            "SFML_BUILD_DOC OFF"
            "SFML_SHARED_LIBS ON"
            "CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
            $<$<PLATFORM_ID:Windows>:
                "SFML_GENERATE_PDB ON"
            >
            $<$<AND:$<PLATFORM_ID:Darwin>,$<CONFIG:Release>>:
                "CMAKE_INSTALL_PREFIX=/Library/Frameworks" "SFML_BUILD_FRAMEWORKS ON"
            >
            $<$<AND:$<PLATFORM_ID:Darwin>,$<CONFIG:Debug>>:
                "SFML_BUILD_FRAMEWORKS OFF"
            >
    )


# Link libraries to the executable
    target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Window SFML::Audio SFML::System)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)
