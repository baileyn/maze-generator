#include "Window.hpp"

#include <glad/glad.h>

namespace Pz::UI
{

Window::Window(std::string_view title, int width, int height) : m_window(nullptr, glfwDestroyWindow)
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    m_window.reset(glfwCreateWindow(width, height, title.data(), nullptr, nullptr));
    if (!m_window)
    {
        throw std::runtime_error("Failed to create window");
    }

    glfwMakeContextCurrent(m_window.get());
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

Window::~Window()
{
    glfwTerminate();
}

} // namespace Pz::UI
