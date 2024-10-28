#pragma once

#include <GLFW/glfw3.h>
#include <memory>
#include <string_view>

struct GlfwWindowDestroyer
{
    void operator()(GLFWwindow *window) const
    {
        glfwDestroyWindow(window);
    }
};

class Window
{
  public:
    Window(std::string_view title, int width, int height);
    ~Window();

    [[nodiscard]] bool shouldClose() const
    {
        return glfwWindowShouldClose(m_window.get());
    }

    void swapBuffers()
    {
        glfwSwapBuffers(m_window.get());
    }

  private:
    Window(const Window &) = delete;
    Window(Window &&) = delete;
    Window &operator=(const Window &) = delete;
    Window &operator=(Window &&) = delete;

  private:
    std::unique_ptr<GLFWwindow, GlfwWindowDestroyer> m_window;
};