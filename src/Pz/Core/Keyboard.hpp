#pragma once

#include "../UI/Window.hpp"
#include "Logging.hpp"

#include <GLFW/glfw3.h>
#include <array>

namespace Pz::Core
{

class Keyboard
{
  public:
    Keyboard(UI::Window &window);

    bool isPressed(int key) const
    {
        return m_currentKeys[key];
    }

    bool isJustPressed(int key) const
    {
        return m_currentKeys[key] && !m_lastKeys[key];
    }

    void update()
    {
        std::copy(m_currentKeys.begin(), m_currentKeys.end(), m_lastKeys.begin());
    }

  private:
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

  private:
    std::array<bool, GLFW_KEY_LAST> m_currentKeys{};
    std::array<bool, GLFW_KEY_LAST> m_lastKeys{};
};

} // namespace Pz::Core
