#include "Pz/Core/Game.hpp"
#include "Pz/Mesh/MeshBuilder.hpp"
#include "Pz/Shader/Program.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

constexpr int GRID_SIZE = 20;
constexpr int WIDTH = 20;
constexpr int HEIGHT = 20;

class Player
{
  public:
    Player(Pz::Mesh::MeshPtr mesh, glm::vec3 position) : m_mesh{mesh}, m_position{position}
    {
    }

    void update()
    {
    }

    void render(Pz::Shader::ProgramPtr &program)
    {
        program->use();
        program->setUniform("model", glm::translate(glm::mat4(1.0f), m_position * (float)GRID_SIZE));

        m_mesh->draw();
    }

  private:
    Pz::Mesh::MeshPtr m_mesh{};
    glm::vec3 m_position;
};

class ExampleGame : public Pz::Core::Game
{
  public:
    ExampleGame() : Pz::Core::Game("Example Game", WIDTH * GRID_SIZE, HEIGHT * GRID_SIZE)
    {
    }

  private:
    void init() override
    {
        Pz::Mesh::MeshBuilder builder{};
        builder.addVertex({{0.0f, 100.0f, 0.0f}, {1.0f, 0.0f, 0.0f}});
        builder.addVertex({{100.0f, 100.0f, 0.0f}, {0.0f, 1.0f, 0.0f}});
        builder.addVertex({{50.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}});
        triangle = builder.build();
        builder.reset();

        builder.addVertex({{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}});
        builder.addVertex({{0.0f, 10.0f, 0.0f}, {0.0f, 0.0f, 0.0f}});
        builder.addVertex({{10.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}});
        builder.addVertex({{10.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}});
        builder.addVertex({{0.0f, 10.0f, 0.0f}, {0.0f, 0.0f, 0.0f}});
        builder.addVertex({{10.0f, 10.0f, 0.0f}, {0.0f, 0.0f, 0.0f}});
        m_player = std::make_shared<Player>(builder.build(), glm::vec3{5.0, 5.0, 0.0});

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

        program->setUniform("model", glm::mat4(1.0f));
        triangle->draw();

        m_player->render(program);
    }

  private:
    std::shared_ptr<Player> m_player{};

    Pz::Mesh::MeshPtr triangle{nullptr};
    Pz::Shader::ProgramPtr program{nullptr};

    glm::mat4 projection{};
};

PZ_GAME_ENTRY(ExampleGame)
