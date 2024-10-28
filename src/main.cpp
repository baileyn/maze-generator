#include "Game.hpp"
#include "Logging.hpp"
#include "ShaderProgram.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include <filesystem>

struct Vertex
{
    glm::vec2 pos;
    glm::vec3 color;
};

class MazeGame : public Game
{
  public:
    void setup() override
    {
        m_shader = std::make_unique<ShaderProgram>();
        m_shader->addShader("../../../../simple.vert", GL_VERTEX_SHADER);
        m_shader->addShader("../../../../simple.frag", GL_FRAGMENT_SHADER);
        m_shader->link();

        std::vector<Vertex> vertices = {{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
                                        {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
                                        {{0.0f, 0.5f}, {0.0f, 0.0f, 1.0f}}};

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

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              reinterpret_cast<void *>(offsetof(Vertex, color)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void render() override
    {
        glClear(GL_COLOR_BUFFER_BIT);

        m_shader->use();
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }

  private:
    GLuint m_vao{};
    GLuint m_vbo{};

    std::unique_ptr<ShaderProgram> m_shader{};
};

int main(int argc, char **argv)
{
    std::filesystem::path path = std::filesystem::current_path();
    LOG_INFO("Current path: {}", path.string());

    MazeGame game{};
    game.run();

    return EXIT_SUCCESS;
}