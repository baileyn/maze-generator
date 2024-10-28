#define GLFW_INCLUDE_NONE

#include "Window.hpp"

int main(int argc, char **argv)
{
    Window window("Hello, World!", 800, 600);

    while (!window.shouldClose())
    {
        glfwPollEvents();
        window.swapBuffers();
    }

    return EXIT_SUCCESS;
}