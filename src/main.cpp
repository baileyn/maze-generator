#include "UI/Window.hpp"

#include <cstdlib>

// Developmet ONLY should _NOT_ be in the final product.
#include <GLFW/glfw3.h>

int main(int argc, char **argv)
{
    Pz::UI::Window window("Game", 800, 600);

    while (!window.shouldClose())
    {
        glfwPollEvents();
        window.swapBuffers();
    }

    return EXIT_SUCCESS;
}
