cmake_minimum_required(VERSION 3.14) # 3.14 required for CPM

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

# Find CXX files
    # Find all .cpp files in src/ and add them to executables
        file(GLOB_RECURSE SOURCES "src/*.cpp")
        add_executable(${PROJECT_NAME} ${SOURCES})
    # Include all headers in include/
        target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Use FetchContent
    include(FetchContent)

    FetchContent_Declare(
        sfml
        GIT_REPOSITORY "https://github.com/SFML/SFML.git"
        GIT_TAG        "3.0.2"
    )

# Make used libraries available
    FetchContent_MakeAvailable(sfml)

# Add Qt
    find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTORCC ON)

# Link libraries to the executable
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-audio sfml-graphics sfml-system sfml-window)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)
