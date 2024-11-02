#include "Game.hpp"

#include <GLFW/glfw3.h>

namespace Pz::Core
{

Game::Game(std::string_view title, int width, int height)
    : m_window(title, width, height), m_width(width), m_height(height)
{
    m_keyboard = std::make_shared<Keyboard>(m_window);
}

void Game::run()
{
    init();

    while (!m_window.shouldClose())
    {
        m_keyboard->update();

        glfwPollEvents();

        update();
        render();

        m_window.swapBuffers();
    }

    cleanup();
}

} // namespace Pz::Core
