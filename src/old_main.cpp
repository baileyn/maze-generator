#define GLFW_INCLUDE_NONE

#include "Cell.hpp"
#include "Grid.hpp"
#include "ImageBuffer.hpp"
#include "Pixel.hpp"

#include "Shader.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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

// Turn ImageBuffer into an OpenGL texture
GLuint convertImageBufferToTexture(ImageBuffer<Pixel<uint8_t>> &buffer)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, buffer.width(), buffer.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}

struct Vertex
{
    glm::vec2 position;
    glm::vec3 color;
};

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

    Shader shader("../simple.vert", "../simple.frag");

    glm::mat4 view = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    shader.setMat4("view", view);

    // Define vertices for a 2D triangle
    Vertex vertices[] = {
        // positions        // colors
        {{400.0f, 100.0f}, {1.0f, 0.0f, 0.0f}}, // top
        {{300.0f, 500.0f}, {0.0f, 1.0f, 0.0f}}, // bottom left
        {{500.0f, 500.0f}, {0.0f, 0.0f, 1.0f}}  // bottom right
    };

    // Create VAO and VBO
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind VBO and upload vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Define vertex attributes
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    glClearColor(0.2f, 0.4, 0.8f, 1.0f);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

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
