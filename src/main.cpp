#include "Pz/Core/Game.hpp"
#include "Pz/Mesh/MeshBuilder.hpp"
#include "Pz/Shader/Program.hpp"

class ExampleGame : public Pz::Core::Game
{
  private:
    void init() override
    {
        Pz::Mesh::MeshBuilder builder{};
        builder.addVertex({{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}});
        builder.addVertex({{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}});
        builder.addVertex({{0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}});
        triangle = builder.build();

        program = std::make_shared<Pz::Shader::Program>();
        program->attachShader("shaders/simple.vert", GL_VERTEX_SHADER);
        program->attachShader("shaders/simple.frag", GL_FRAGMENT_SHADER);
        program->link();

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
};

PZ_GAME_ENTRY(ExampleGame)
