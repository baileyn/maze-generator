cmake_minimum_required(VERSION 3.29 FATAL_ERROR)
project(maze)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES src/main.cpp
    src/Cell.cpp src/Cell.hpp
    src/Grid.cpp src/Grid.hpp
    src/Errors.hpp
    src/ImageBuffer.hpp
    src/Pixel.hpp
    src/Point.hpp

    src/Window.cpp src/Window.hpp
    src/Game.cpp src/Game.hpp
    src/ShaderProgram.cpp src/ShaderProgram.hpp
)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)

find_package(SPNG CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE $<IF:$<TARGET_EXISTS:spng::spng>,spng::spng,spng::spng_static>)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
