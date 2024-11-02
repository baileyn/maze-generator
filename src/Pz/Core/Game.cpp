#include "Game.hpp"
#include "Logging.hpp"

#include <GLFW/glfw3.h>

namespace Pz::Core
{

Game::Game(std::string_view title, int width, int height)
    : window(title, width, height), m_width(width), m_height(height)
{
}

void Game::run()
{
    PZ_CORE_TRACE("Initializing Game");
    init();

    while (!window.shouldClose())
    {
        PZ_CORE_TRACE("Polling events");
        glfwPollEvents();

        PZ_CORE_TRACE("Updating game");
        update();

        PZ_CORE_TRACE("Rendering game");
        render();

        PZ_CORE_TRACE("Swapping buffers");
        window.swapBuffers();
    }

    PZ_CORE_TRACE("Cleaning up resources");
    cleanup();
}

} // namespace Pz::Core
