#pragma once

#include <cstdlib>

#include <vector>

class Cell;

class Grid
{
  public:
    /**
     * @brief Constructs a Grid object with the specified width and height.
     *
     * @param width The width of the grid.
     * @param height The height of the grid.
     */
    Grid(size_t width, size_t height);

    /**
     * @brief Destroys the Grid object.
     */
    virtual ~Grid();

    /**
     * @brief Deleted copy constructor to prevent copying of Grid objects.
     */
    Grid(Grid &) = delete;

    /**
     * @brief Deleted move constructor to prevent moving of Grid objects.
     */
    Grid(Grid &&) = delete;

    /**
     * @brief Deleted copy assignment operator to prevent copying of Grid objects.
     */
    Grid &operator=(Grid &) = delete;

    /**
     * @brief Deleted move assignment operator to prevent moving of Grid objects.
     */
    Grid &operator=(Grid &&) = delete;

    /**
     * @brief Retrieves a pointer to the cell at the specified coordinates.
     *
     * @param x The x-coordinate of the cell.
     * @param y The y-coordinate of the cell.
     * @return Pointer to the cell at the specified coordinates.
     */
    Cell *get(size_t x, size_t y);

    /**
     * @brief Returns the width of the grid.
     *
     * @return The width of the grid.
     */
    [[nodiscard]] size_t width() const
    {
        return m_width;
    }

    /**
     * @brief Returns the height of the grid.
     *
     * @return The height of the grid.
     */
    [[nodiscard]] size_t height() const
    {
        return m_height;
    }

    /**
     * @brief Generates the grid.
     *
     * This function generates the grid, initializing its cells and setting up any necessary
     * structures for the grid to function properly.
     */
    void generate();

  private:
    size_t m_width{};
    size_t m_height{};
    std::vector<Cell *> m_cells{};
};
