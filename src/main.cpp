#include "Pz/Core/Game.hpp"
#include "Pz/Mesh/MeshBuilder.hpp"

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

        glClearColor(0.2f, 0.4f, 0.8f, 1.0f);
    }

    void render() override
    {
        glClear(GL_COLOR_BUFFER_BIT);

        triangle->draw();
    }

  private:
    std::shared_ptr<Pz::Mesh::Mesh> triangle{nullptr};
};

PZ_GAME_ENTRY(ExampleGame)
