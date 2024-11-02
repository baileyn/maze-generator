#pragma once

#include <GLFW/glfw3.h>
#include <memory>
#include <string_view>

namespace Pz::UI
{

namespace GLFW
{
using WindowDeleter = decltype(&glfwDestroyWindow);
}

class Window
{
  public:
    Window(std::string_view title = "Game", int width = 800, int height = 600);
    ~Window();

    bool shouldClose() const
    {
        return glfwWindowShouldClose(m_window.get());
    }

    void swapBuffers()
    {
        glfwSwapBuffers(m_window.get());
    }

  private:
    Window(Window const &) = delete;
    Window &operator=(Window const &) = delete;
    Window(Window &&) = delete;
    Window &operator=(Window &&) = delete;

  private:
    std::unique_ptr<GLFWwindow, GLFW::WindowDeleter> m_window;
};

} // namespace Pz::UI
