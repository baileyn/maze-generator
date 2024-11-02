#include "Game.hpp"

#include <GLFW/glfw3.h>

namespace Pz::Core
{

Game::Game(std::string_view title, int width, int height) : window(title, width, height)
{
}

void Game::run()
{
    init();

    while (!window.shouldClose())
    {
        glfwPollEvents();

        update();
        render();

        window.swapBuffers();
    }

    cleanup();
}

} // namespace Pz::Core
