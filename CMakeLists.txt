cmake_minimum_required(VERSION 3.29 FATAL_ERROR)
project(maze)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES src/main.cpp
    src/Pz/UI/Window.hpp src/Pz/UI/Window.cpp

    src/Pz/Core/Game.hpp src/Pz/Core/Game.cpp
    src/Pz/Core/Logging.hpp src/Pz/Core/Logging.cpp
    src/Pz/Core/Keyboard.hpp src/Pz/Core/Keyboard.cpp

    src/Pz/Mesh/Mesh.hpp src/Pz/Mesh/Mesh.cpp
    src/Pz/Mesh/MeshBuilder.hpp src/Pz/Mesh/MeshBuilder.cpp

    src/Pz/Shader/Program.hpp src/Pz/Shader/Program.cpp
)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
