#define GLFW_INCLUDE_NONE

#include "Cell.hpp"
#include "Grid.hpp"
#include "ImageBuffer.hpp"
#include "Pixel.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

constexpr size_t SQUARE_SIZE = 20;
constexpr size_t GRID_WIDTH = 100;
constexpr size_t GRID_HEIGHT = 100;

/**
 * @brief Draws a cell on the image buffer.
 *
 * This function draws a cell on the provided image buffer. It draws the cell's walls
 * and colors the start and end cells differently. The start cell (top-left) is colored green,
 * and the end cell (bottom-right) is colored red.
 *
 * @param buffer The image buffer to draw the cell on.
 * @param cell The cell to be drawn.
 */
void drawCell(ImageBuffer<Pixel<uint8_t>> &buffer, Cell *cell)
{
    size_t x = cell->x() * SQUARE_SIZE;
    size_t y = cell->y() * SQUARE_SIZE;

    if (cell->x() == 0 && cell->y() == 0)
    {
        buffer.drawSquare({0x00, 0xFF, 0x00}, {x, y}, SQUARE_SIZE);
    }
    else if (cell->x() == GRID_WIDTH - 1 && cell->y() == GRID_HEIGHT - 1)
    {
        buffer.drawSquare({0xFF, 0x00, 0x00}, {x, y}, SQUARE_SIZE);
    }

    if (cell->hasNorthWall())
    {
        buffer.line({0, 0, 0}, {x, y}, {x + SQUARE_SIZE, y});
    }

    if (cell->hasEastWall())
    {
        buffer.line({0, 0, 0}, {x + SQUARE_SIZE, y}, {x + SQUARE_SIZE, y + SQUARE_SIZE});
    }

    if (cell->hasSouthWall())
    {
        buffer.line({0, 0, 0}, {x, y + SQUARE_SIZE}, {x + SQUARE_SIZE, y + SQUARE_SIZE});
    }

    if (cell->hasWestWall())
    {
        buffer.line({0, 0, 0}, {x, y}, {x, y + SQUARE_SIZE});
    }
}

int main(int argc, char **argv)
{
    if (!glfwInit())
    {
        spdlog::error("Failed to initialize GLFW");
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); // This setting is required for Mac compatibility
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Maze Generator", nullptr, nullptr);
    if (!window)
    {
        spdlog::error("Failed to create window");
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        spdlog::error("Failed to initialize GLAD");
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    // Grid grid{GRID_WIDTH, GRID_HEIGHT};
    // grid.generate();

    // ImageBuffer<Pixel<uint8_t>> buffer{SQUARE_SIZE * GRID_WIDTH, SQUARE_SIZE * GRID_HEIGHT};
    // buffer.fill(0xFF);

    // for (size_t y = 0; y < GRID_HEIGHT; y++)
    // {
    //     for (size_t x = 0; x < GRID_WIDTH; x++)
    //     {
    //         drawCell(buffer, grid.get(x, y));
    //     }
    // }

    // buffer.save_to_file("test.png");

    return EXIT_SUCCESS;
}
