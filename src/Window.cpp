#include "Window.hpp"
#include "Logging.hpp"

#include <glad/glad.h>
#include <iostream>

Window::Window(std::string_view title, int width, int height)
{
    if (!glfwInit())
    {
        LOG_ERROR("Failed to initialize GLFW");
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_window = std::unique_ptr<GLFWwindow, GlfwWindowDestroyer>(
        glfwCreateWindow(width, height, title.data(), nullptr, nullptr));

    if (!m_window)
    {
        LOG_ERROR("Failed to create window");
        glfwTerminate();
        throw std::runtime_error("Failed to create window");
    }

    glfwMakeContextCurrent(m_window.get());

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        LOG_ERROR("Failed to initialize GLAD");
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

Window::~Window()
{
    glfwDestroyWindow(m_window.get());
    m_window = nullptr;

    glfwTerminate();
}