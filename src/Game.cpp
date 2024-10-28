#include "Game.hpp"

#include <GLFW/glfw3.h>

Game::Game(std::string_view title, int width, int height)
    : m_window(std::make_unique<Window>(title, width, height)), m_width(width), m_height(height)
{
}

void Game::run()
{
    setup();

    while (!m_window->shouldClose())
    {
        glfwPollEvents();

        update();
        render();

        m_window->swapBuffers();
    }

    cleanup();
}