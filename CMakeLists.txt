cmake_minimum_required(VERSION 3.1)
project(notes)

find_package( SFML 2 COMPONENTS graphics audio window system )

if(CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -g")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
endif()

file(GLOB SOURCES
    "${PROJECT_SOURCE_DIR}/*.cpp"
)

add_executable(notes ${SOURCES})

set_property(TARGET notes PROPERTY CXX_STANDARD 11)
set_property(TARGET notes PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS notes RUNTIME DESTINATION bin)
target_link_libraries(notes ${SFML_LIBRARIES})