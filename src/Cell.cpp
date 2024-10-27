#include "Cell.hpp"

#include "Grid.hpp"

void Cell::visit(Cell *previous)
{
    m_visited = true;

    if (previous != nullptr)
    {
        if (previous->x() < this->x())
        {
            m_walls[3] = false;
            previous->m_walls[1] = false;
        }
        else if (previous->x() > this->x())
        {
            m_walls[1] = false;
            previous->m_walls[3] = false;
        }
        else if (previous->y() < this->y())
        {
            m_walls[0] = false;
            previous->m_walls[2] = false;
        }
        else if (previous->y() > this->y())
        {
            m_walls[2] = false;
            previous->m_walls[0] = false;
        }
    }
}

std::vector<Cell *> Cell::neighbors()
{
    std::vector<Cell *> result;

    if (this->x() > 0)
    {
        result.push_back(m_parent->get(this->x() - 1, this->y()));
    }

    if (this->x() < m_parent->width() - 1)
    {
        result.push_back(m_parent->get(this->x() + 1, this->y()));
    }

    if (this->y() > 0)
    {
        result.push_back(m_parent->get(this->x(), this->y() - 1));
    }

    if (this->y() < m_parent->height() - 1)
    {
        result.push_back(m_parent->get(this->x(), this->y() + 1));
    }

    return result;
}

std::vector<Cell *> Cell::unvisitedNeighbors()
{
    std::vector<Cell *> result;

    for (Cell *neighbor : this->neighbors())
    {
        if (!neighbor->visited())
        {
            result.push_back(neighbor);
        }
    }

    return result;
}
