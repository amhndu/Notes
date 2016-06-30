cmake_minimum_required(VERSION 3.1)
project(notes)

find_package( SFML 2 COMPONENTS graphics audio window system )

file(GLOB SOURCES
    "${PROJECT_SOURCE_DIR}/*.cpp"
)

add_executable(notes ${SOURCES})

set_property(TARGET notes PROPERTY CXX_STANDARD 11)
set_property(TARGET notes PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS notes RUNTIME DESTINATION bin)
target_link_libraries(notes ${SFML_LIBRARIES})