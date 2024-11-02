#include "Pz/Core/Game.hpp"
#include "Pz/Mesh/MeshBuilder.hpp"
#include "Pz/Shader/Program.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ExampleGame : public Pz::Core::Game
{
  private:
    void init() override
    {
        Pz::Mesh::MeshBuilder builder{};
        builder.addVertex({{0.0f, 100.0f, 0.0f}, {1.0f, 0.0f, 0.0f}});
        builder.addVertex({{100.0f, 100.0f, 0.0f}, {0.0f, 1.0f, 0.0f}});
        builder.addVertex({{50.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}});
        triangle = builder.build();

        program = std::make_shared<Pz::Shader::Program>();
        program->attachShader("assets/shaders/simple.vert", GL_VERTEX_SHADER);
        program->attachShader("assets/shaders/simple.frag", GL_FRAGMENT_SHADER);
        program->link();

        // Setup projection matrix
        projection = glm::ortho(0.0f, width(), height(), 0.0f, 0.0f, 100.0f);

        program->use();
        program->setUniform("projection", projection);

        glClearColor(0.2f, 0.4f, 0.8f, 1.0f);
    }

    void render() override
    {
        glClear(GL_COLOR_BUFFER_BIT);

        program->use();
        triangle->draw();
    }

  private:
    std::shared_ptr<Pz::Mesh::Mesh> triangle{nullptr};
    std::shared_ptr<Pz::Shader::Program> program{nullptr};

    glm::mat4 projection{};
};

PZ_GAME_ENTRY(ExampleGame)
