cmake_minimum_required(VERSION 3.24.1)

project(Smart-Rockets)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
add_executable(${PROJECT_NAME} main.cpp geneticalgorithm.cpp rocket.cpp application.cpp)
target_link_libraries(${PROJECT_NAME} sfml-graphics)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)