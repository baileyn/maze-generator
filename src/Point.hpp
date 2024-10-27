#pragma once

#include <cstdlib>

/**
 * Represents a point in a 2D space with x and y coordinates.
 */
struct Point
{
    size_t x; ///< The x-coordinate of the point.
    size_t y; ///< The y-coordinate of the point.

    /**
     * Constructs a Point with the specified x and y coordinates.
     *
     * @param x The x-coordinate of the point.
     * @param y The y-coordinate of the point.
     */
    Point(size_t x, size_t y) : x{x}, y{y}
    {
    }

    /**
     * Constructs a Point at the origin (0, 0).
     */
    Point() : Point(0, 0)
    {
    }
};
