#include "Game.hpp"
#include "Logging.hpp"
#include "ShaderProgram.hpp"

#include "Cell.hpp"
#include "Grid.hpp"
#include "ImageBuffer.hpp"
#include "Pixel.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include <filesystem>

constexpr size_t SQUARE_SIZE = 50;
constexpr size_t GRID_WIDTH = 10;
constexpr size_t GRID_HEIGHT = 10;

struct Vertex
{
    glm::vec2 pos;
    glm::vec2 uv;
};

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

    // if (cell->hasEastWall())
    // {
    //     buffer.line({0, 0, 0}, {x + SQUARE_SIZE, y}, {x + SQUARE_SIZE, y + SQUARE_SIZE});
    // }

    // if (cell->hasSouthWall())
    // {
    //     buffer.line({0, 0, 0}, {x, y + SQUARE_SIZE}, {x + SQUARE_SIZE, y + SQUARE_SIZE});
    // }

    if (cell->hasWestWall())
    {
        buffer.line({0, 0, 0}, {x, y}, {x, y + SQUARE_SIZE});
    }
}

GLuint createTextureFromRGB(const unsigned char *pixels, int width, int height)
{
    GLuint textureID;

    // Generate a texture ID
    glGenTextures(1, &textureID);

    // Bind the texture as a 2D texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     // Wrap texture horizontally
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     // Wrap texture vertically
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear filtering for minification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear filtering for magnification

    // Upload the texture data to the GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    // Generate mipmaps (optional)
    glGenerateMipmap(GL_TEXTURE_2D);

    // Unbind the texture (optional)
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}

class MazeGame : public Game
{
  public:
    MazeGame(int width, int height) : Game("Game", width, height)
    {
        m_width = width;
        m_height = height;
    }

    void setup() override
    {
        Grid grid{GRID_WIDTH, GRID_HEIGHT};
        grid.generate();

        ImageBuffer<Pixel<uint8_t>> buffer{SQUARE_SIZE * GRID_WIDTH, SQUARE_SIZE * GRID_HEIGHT};
        buffer.fill({0xFF});

        for (size_t y = 0; y < GRID_HEIGHT; y++)
        {
            for (size_t x = 0; x < GRID_WIDTH; x++)
            {
                auto current = grid.get(x, y);
                drawCell(buffer, current);
            }
        }

        m_texture = createTextureFromRGB(reinterpret_cast<const unsigned char *>(buffer.data()), buffer.width(),
                                         buffer.height());
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture);

        m_shader = std::make_unique<ShaderProgram>();
        m_shader->addShader("../../../../simple.vert", GL_VERTEX_SHADER);
        m_shader->addShader("../../../../simple.frag", GL_FRAGMENT_SHADER);
        m_shader->link();

        m_texShader = std::make_unique<ShaderProgram>();
        m_texShader->addShader("../../../../tex.vert", GL_VERTEX_SHADER);
        m_texShader->addShader("../../../../tex.frag", GL_FRAGMENT_SHADER);
        m_texShader->link();

        m_projection = glm::ortho(0.0f, m_width, 0.0f, m_height, -100.0f, 100.0f);
        glViewport(0, 0, m_width, m_height);

        m_shader->use();
        m_shader->setUniform("projection", m_projection);

        m_texShader->use();
        m_texShader->setUniform("projection", m_projection);
        m_texShader->setUniform("textureSampler", 0);

        std::vector<Vertex> vertices = {
            // Positions               // Texture Coordinates
            {{0.0f, m_height}, {0.0f, 0.0f}},    // Top left
            {{0.0f, 0.0f}, {0.0f, 1.0f}},        // Bottom left
            {{m_width, m_height}, {1.0f, 0.0f}}, // Top right

            {{m_width, m_height}, {1.0f, 0.0f}}, // Top right
            {{0.0f, 0.0f}, {0.0f, 1.0f}},        // Bottom left
            {{m_width, 0.0f}, {1.0f, 1.0f}},     // Bottom right
        };

        glClearColor(0.2f, 0.4f, 0.8f, 1.0f);

        // Create VAO for rendering a triangle
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              reinterpret_cast<void *>(offsetof(Vertex, pos)));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, uv)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void render() override
    {
        glClear(GL_COLOR_BUFFER_BIT);

        m_texShader->use();
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

  private:
    GLuint m_vao{};
    GLuint m_vbo{};
    GLuint m_texture{};
    glm::mat4 m_projection{};

    std::unique_ptr<ShaderProgram> m_shader{};
    std::unique_ptr<ShaderProgram> m_texShader{};

    float m_width;
    float m_height;
};

int main(int argc, char **argv)
{
    std::filesystem::path path = std::filesystem::current_path();
    LOG_INFO("Current path: {}", path.string());

    MazeGame game{800, 600};
    game.run();

    return EXIT_SUCCESS;
}