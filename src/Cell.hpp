#pragma once

#include <cstdlib>

#include <vector>

class Grid;

class Cell
{
  public:
    /**
     * @brief Constructs a Cell object with the specified parent grid and coordinates.
     *
     * @param parent Pointer to the parent grid.
     * @param x The x-coordinate of the cell.
     * @param y The y-coordinate of the cell.
     */
    Cell(Grid *parent, size_t x, size_t y) : m_parent{parent}, m_x{x}, m_y{y}, m_walls{true, true, true, true}
    {
    }

    /**
     * @brief Default constructor for the Cell object.
     */
    Cell() = default;

    /**
     * @brief Marks the cell as visited and optionally sets the previous cell.
     *
     * @param previous Pointer to the previous cell visited.
     */
    void visit(Cell *previous = nullptr);

    /**
     * @brief Checks if the cell has been visited.
     *
     * @return True if the cell has been visited, false otherwise.
     */
    [[nodiscard]] bool visited() const
    {
        return m_visited;
    }

    /**
     * @brief Returns the x-coordinate of the cell.
     *
     * @return The x-coordinate of the cell.
     */
    [[nodiscard]] size_t x() const
    {
        return m_x;
    }

    /**
     * @brief Returns the y-coordinate of the cell.
     *
     * @return The y-coordinate of the cell.
     */
    [[nodiscard]] size_t y() const
    {
        return m_y;
    }

    /**
     * @brief Retrieves the neighboring cells of the current cell.
     *
     * @return A vector of pointers to the neighboring cells.
     */
    [[nodiscard]] std::vector<Cell *> neighbors();

    /**
     * @brief Retrieves the unvisited neighboring cells of the current cell.
     *
     * @return A vector of pointers to the unvisited neighboring cells.
     */
    [[nodiscard]] std::vector<Cell *> unvisitedNeighbors();

    /**
     * @brief Checks if the cell has a north wall.
     *
     * @return True if the cell has a north wall, false otherwise.
     */
    [[nodiscard]] bool hasNorthWall() const
    {
        return m_walls[0];
    }

    /**
     * @brief Checks if the cell has an east wall.
     *
     * @return True if the cell has an east wall, false otherwise.
     */
    [[nodiscard]] bool hasEastWall() const
    {
        return m_walls[1];
    }

    /**
     * @brief Checks if the cell has a south wall.
     *
     * @return True if the cell has a south wall, false otherwise.
     */
    [[nodiscard]] bool hasSouthWall() const
    {
        return m_walls[2];
    }

    /**
     * @brief Checks if the cell has a west wall.
     *
     * @return True if the cell has a west wall, false otherwise.
     */
    [[nodiscard]] bool hasWestWall() const
    {
        return m_walls[3];
    }

  private:
    Grid *m_parent;
    size_t m_x{};
    size_t m_y{};
    bool m_visited{};
    std::vector<Cell *> m_neighbors{};
    std::array<bool, 4> m_walls{};
};
