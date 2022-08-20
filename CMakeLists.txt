cmake_minimum_required(VERSION 3.14)
include(FetchContent)
include(ExternalProject)
project(notes CXX)

ExternalProject_Add(PortAudio
    GIT_REPOSITORY https://github.com/PortAudio/portaudio.git
    INSTALL_COMMAND cmake -E echo "Skipping install step."
)

FetchContent_Declare(boost_lockfree
    GIT_REPOSITORY https://github.com/boostorg/lockfree.git
    GIT_TAG boost-1.79.0
    # INSTALL_COMMAND cmake -E echo "Skipping install step."
)

FetchContent_MakeAvailable(boost_lockfree)

if(CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -g")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Add directory containing FindSFML.cmake to module path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/;${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}")

file(GLOB SOURCES
    "${PROJECT_SOURCE_DIR}/*.cpp"
)
# Find SFML
if (SFML_OS_WINDOWS AND SFML_COMPILER_MSVC)
    find_package( SFML 2 COMPONENTS main audio graphics window system REQUIRED)
else()
    find_package( SFML 2 COMPONENTS audio graphics window system REQUIRED)
endif()

include_directories(${SFML_INCLUDE_DIR} ${boost_lockfree_SOURCE_DIR}/boost_lockfree/include)
add_executable(notes ${SOURCES})
target_link_libraries(notes ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${PortAudio_LIBRARIES})

set_property(TARGET notes PROPERTY CXX_STANDARD 11)
set_property(TARGET notes PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS notes RUNTIME DESTINATION bin)
