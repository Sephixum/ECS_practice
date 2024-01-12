cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(RESOUCES_DIR "${CMAKE_SOURCE_DIR}/resources/")

project(ECS_DEMO
    VERSION 0.0.1
    DESCRIPTION "ECS design pattern example"
    LANGUAGES CXX)

find_package(SFML COMPONENTS system graphics window CONFIG REQUIRED)

add_executable(output)

if(MSVC)
target_compile_options(output PRIVATE /W4 /WX)
else()
target_compile_options(output PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

target_sources(output PRIVATE
    src/main.cpp
    src/Components.cpp
    src/EntityManager.cpp
    src/Entity.cpp
    src/Game.cpp
)

target_include_directories(output PRIVATE "${CMAKE_SOURCE_DIR}/include/")
target_link_libraries(output PRIVATE sfml-graphics sfml-window sfml-system)

add_custom_command(TARGET output
    POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    -E copy_directory ${RESOUCES_DIR}
    $<TARGET_FILE_DIR:output>/resources)
