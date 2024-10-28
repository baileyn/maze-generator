#include "Grid.hpp"
#include "Cell.hpp"

#include <random>

Grid::Grid(size_t width, size_t height) : m_width{width}, m_height{height}, m_cells(width * height)
{
    for (size_t y = 0; y < m_height; y++)
    {
        for (size_t x = 0; x < m_width; x++)
        {
            m_cells[y * m_width + x] = new Cell{this, x, y};
        }
    }
}

Grid::~Grid()
{
    for (Cell *cell : m_cells)
    {
        delete cell;
    }
}

Cell *Grid::get(size_t x, size_t y)
{
    return m_cells[y * m_width + x];
}

void Grid::generate()
{
    std::random_device dev;
    std::mt19937 random(dev());

    std::vector<Cell *> stack;
    Cell *current = m_cells[0];

    current->visit();
    stack.push_back(current);

    while (!stack.empty())
    {
        auto unvisited_neighbors = current->unvisitedNeighbors();

        if (!unvisited_neighbors.empty())
        {
            size_t location = random() % unvisited_neighbors.size();
            Cell *next = unvisited_neighbors[location];

            next->visit(current);
            stack.push_back(next);

            current = next;
        }
        else
        {
            stack.pop_back();

            if (!stack.empty())
            {
                current = stack.back();
            }
        }
    }
}
