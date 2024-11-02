#include "Keyboard.hpp"

namespace Pz::Core
{

Keyboard::Keyboard(UI::Window &window)
{
    glfwSetWindowUserPointer(window.get(), this);
    glfwSetKeyCallback(window.get(), key_callback);
}

void Keyboard::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    auto *keyboard = static_cast<Keyboard *>(glfwGetWindowUserPointer(window));
    keyboard->m_currentKeys[key] = action != GLFW_RELEASE;
}

} // namespace Pz::Core
