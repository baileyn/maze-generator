#include "Pz/Core/Game.hpp"
#include "Pz/Mesh/MeshBuilder.hpp"
#include "Pz/Shader/Program.hpp"

#include <algorithm>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <random>

constexpr int GRID_SIZE = 20;
constexpr int WIDTH = 20;
constexpr int HEIGHT = 20;

enum class Direction : int
{
    UP = 0,
    RIGHT,
    DOWN,
    LEFT
};

Direction getOppositeDirection(Direction d)
{
    switch (d)
    {
    case Direction::UP:
        return Direction::DOWN;
    case Direction::RIGHT:
        return Direction::LEFT;
    case Direction::DOWN:
        return Direction::UP;
    case Direction::LEFT:
        return Direction::RIGHT;
    default:
        throw std::runtime_error("Invalid direction");
    }
}

class Cell
{
  public:
    Cell(int x, int y)
    {
        m_x = x;
        m_y = y;
    }

    void visit()
    {
        m_visited = true;
    }

    bool visited() const
    {
        return m_visited;
    }

    bool hasWall(Direction direction) const
    {
        return m_walls[static_cast<int>(direction)];
    }

    void setWall(Direction direction, bool value)
    {
        m_walls[static_cast<int>(direction)] = value;
    }

    void setNeighbor(Direction direction, std::shared_ptr<Cell> cell)
    {
        m_neighbors[static_cast<int>(direction)] = cell;
    }

    std::shared_ptr<Cell> getNeighbor(Direction direction) const
    {
        return m_neighbors[static_cast<int>(direction)];
    }

    int x() const
    {
        return m_x;
    }

    int y() const
    {
        return m_y;
    }

  private:
    std::array<bool, 4> m_walls{true, true, true, true};
    std::shared_ptr<Cell> m_neighbors[4]{};
    bool m_visited{false};

    int m_x;
    int m_y;
};

struct CellNeighbor
{
    std::shared_ptr<Cell> cell;
    Direction direction;
};

class Grid
{
  public:
    Grid(int width, int height) : m_width{width}, m_height{height}
    {
        m_cells.resize(m_width * m_height);

        for (int y = 0; y < m_height; ++y)
        {
            for (int x = 0; x < m_width; ++x)
            {
                m_cells[y * m_width + x] = std::make_shared<Cell>(x, y);
            }
        }

        for (int y = 0; y < m_height; ++y)
        {
            for (int x = 0; x < m_width; ++x)
            {
                auto cell = getCell(x, y);

                if (x > 0)
                {
                    cell->setNeighbor(Direction::LEFT, getCell(x - 1, y));
                }

                if (x < m_width - 1)
                {
                    cell->setNeighbor(Direction::RIGHT, getCell(x + 1, y));
                }

                if (y > 0)
                {
                    cell->setNeighbor(Direction::UP, getCell(x, y - 1));
                }

                if (y < m_height - 1)
                {
                    cell->setNeighbor(Direction::DOWN, getCell(x, y + 1));
                }
            }
        }
    }

    void generate()
    {
        std::stack<std::shared_ptr<Cell>> stack{};
        auto current = getCell(0, 0);
        current->visit();

        while (true)
        {
            auto neighbors = getUnvisitedNeighbors(current);

            if (!neighbors.empty())
            {
                auto [next, direction] = neighbors.front();

                current->setWall(direction, false);
                next->setWall(getOppositeDirection(direction), false);

                next->visit();
                stack.push(current);
                current = next;
            }
            else if (!stack.empty())
            {
                current = stack.top();
                stack.pop();
            }
            else
            {
                break;
            }
        }

        generateMesh();
    }

    void generateMesh()
    {
        Pz::Mesh::MeshBuilder builder{};
        for (int y = 0; y < m_height; ++y)
        {
            for (int x = 0; x < m_width; ++x)
            {
                auto cell = getCell(x, y);

                if (cell->hasWall(Direction::UP))
                {
                    builder.addLine({x, y}, {x + 1, y}, {});
                }

                if (cell->hasWall(Direction::RIGHT))
                {
                    builder.addLine({x + 1, y}, {x + 1, y + 1}, {});
                }

                if (cell->hasWall(Direction::DOWN))
                {
                    builder.addLine({x, y + 1}, {x + 1, y + 1}, {});
                }

                if (cell->hasWall(Direction::LEFT))
                {
                    builder.addLine({x, y}, {x, y + 1}, {});
                }
            }
        }

        m_mesh = builder.build();
    }

    void render(Pz::Shader::ProgramPtr &program)
    {
        program->use();
        program->setUniform("model", glm::mat4(1.0f));

        m_mesh->draw(GL_LINES);
    }

    std::shared_ptr<Cell> getCell(int x, int y)
    {
        return m_cells[y * m_width + x];
    }

    std::vector<CellNeighbor> getUnvisitedNeighbors(std::shared_ptr<Cell> cell)
    {
        std::vector<CellNeighbor> neighbors{};

        for (int i = 0; i < 4; ++i)
        {
            auto neighbor = cell->getNeighbor(static_cast<Direction>(i));

            if (neighbor && !neighbor->visited())
            {
                neighbors.push_back({neighbor, static_cast<Direction>(i)});
            }
        }

        std::shuffle(std::begin(neighbors), std::end(neighbors), rng);

        return neighbors;
    }

  private:
    int m_width;
    int m_height;

    std::vector<std::shared_ptr<Cell>> m_cells;
    std::mt19937 rng{std::random_device{}()};

    Pz::Mesh::MeshPtr m_mesh{};
};

class Player
{
  public:
    Player()
    {
        generateMesh();
    }

    void update()
    {
    }

    void render(Pz::Shader::ProgramPtr &program)
    {
        program->use();
        program->setUniform("model", glm::translate(glm::mat4(1.0f), m_position + glm::vec3{0.25f, 0.25f, 0.0f}));

        m_mesh->draw();
    }

  private:
    void generateMesh()
    {
        Pz::Mesh::MeshBuilder builder{};
        builder.addVertex({{0.0f, 0.0f, 0.0f}, {}});
        builder.addVertex({{0.0f, 0.5f, 0.0f}, {}});
        builder.addVertex({{0.5f, 0.0f, 0.0f}, {}});
        builder.addVertex({{0.5f, 0.0f, 0.0f}, {}});
        builder.addVertex({{0.0f, 0.5f, 0.0f}, {}});
        builder.addVertex({{0.5f, 0.5f, 0.0f}, {}});
        m_mesh = builder.build();
    }

  private:
    Pz::Mesh::MeshPtr m_mesh{};
    glm::vec3 m_position{};
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
        m_grid.generate();
        m_player = std::make_shared<Player>();

        program = std::make_shared<Pz::Shader::Program>();
        program->attachShader("assets/shaders/simple.vert", GL_VERTEX_SHADER);
        program->attachShader("assets/shaders/simple.frag", GL_FRAGMENT_SHADER);
        program->link();

        // Setup projection matrix
        projection = glm::ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, 0.0f, 100.0f);

        program->use();
        program->setUniform("projection", projection);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    }

    void render() override
    {
        glClear(GL_COLOR_BUFFER_BIT);

        m_grid.render(program);
        m_player->render(program);
    }

  private:
    std::shared_ptr<Player> m_player{};

    Pz::Mesh::MeshPtr triangle{nullptr};
    Pz::Shader::ProgramPtr program{nullptr};

    glm::mat4 projection{};
    Grid m_grid{WIDTH, HEIGHT};
};

PZ_GAME_ENTRY(ExampleGame)
