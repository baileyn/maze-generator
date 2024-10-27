#pragma once

#include "Errors.hpp"
#include "Point.hpp"

#include <algorithm>
#include <cstdlib>
#include <string_view>

#include <spng.h>

template <typename T> class ImageBuffer
{
  public:
    /**
     * Constructs an ImageBuffer with the specified width and height.
     *
     * @param width The width of the image buffer.
     * @param height The height of the image buffer.
     *
     * This constructor initializes the image buffer with the given dimensions and allocates
     * memory for the pixel data. The pixel data is stored in a vector with a size equal to
     * the product of the width and height.
     */
    ImageBuffer(size_t width, size_t height) : m_width{width}, m_height{height}, m_pixels(width * height)
    {
    }

    /**
     * @brief Returns a pointer to the underlying data array.
     *
     * @return Pointer to the first element of the data array.
     */
    auto data()
    {
        return m_pixels.data();
    }

    /**
     * @brief Returns an iterator to the beginning of the data array.
     *
     * @return Iterator to the first element of the data array.
     */
    auto begin()
    {
        return std::begin(m_pixels);
    }

    /**
     * @brief Returns an iterator to the end of the data array.
     *
     * @return Iterator to the element following the last element of the data array.
     */
    auto end()
    {
        return std::end(m_pixels);
    }

    /**
     * Fills the entire pixel grid with the specified color.
     *
     * @param color The color to fill the pixel grid with.
     *
     * This function sets every pixel in the grid to the specified color using the std::fill algorithm.
     */
    void fill(T color)
    {
        std::fill(std::begin(m_pixels), std::end(m_pixels), color);
    }

    /**
     * Draws a filled square on the pixel grid.
     *
     * @param color The color to use for the square.
     * @param p The top-left corner point of the square.
     * @param size The length of the sides of the square.
     *
     * This function will fill a square of the given size starting from the specified top-left corner point.
     * It iterates over the rows and columns within the bounds of the square and sets each pixel to the specified color.
     */
    void drawSquare(T color, Point p, size_t size)
    {
        for (size_t y = p.y; y < p.y + size; y++)
        {
            for (size_t x = p.x; x < p.x + size; x++)
            {
                m_pixels[y * m_width + x] = color;
            }
        }
    }

    /**
     * Draws a line on the pixel grid.
     *
     * @param color The color to use for the line.
     * @param p1 The starting point of the line.
     * @param p2 The ending point of the line.
     *
     * This function supports only horizontal and vertical lines.
     * If the line is vertical (p1.x == p2.x), it will draw from the minimum y to the maximum y.
     * If the line is horizontal (p1.y == p2.y), it will draw from the minimum x to the maximum x.
     * If the line is neither horizontal nor vertical, it will throw a NotImplemented exception.
     */
    void line(T color, Point p1, Point p2)
    {
        if (p1.x == p2.x)
        {
            size_t x = p1.x;
            size_t y1 = std::min(p1.y, p2.y);
            size_t y2 = std::max(p1.y, p2.y);

            for (auto y = y1; y < y2; y++)
            {
                m_pixels[y * m_width + x] = color;
            }
        }
        else if (p1.y == p2.y)
        {
            size_t y = p1.y;
            size_t x1 = std::min(p1.x, p2.x);
            size_t x2 = std::max(p1.x, p2.x);

            for (auto x = x1; x < x2; x++)
            {
                m_pixels[y * m_width + x] = color;
            }
        }
        else
        {
            throw NotImplemented();
        }
    }

    /**
     * @brief Saves the image data to a PNG file.
     *
     * This function encodes the image data stored in `m_pixels` and writes it to a file
     * specified by the `filename` parameter. The image is encoded using the SPNG library.
     *
     * @param filename The name of the file to save the image to.
     */
    void save_to_file(std::string_view filename)
    {
        spng_ihdr ihdr{
            .width = static_cast<uint32_t>(m_width),
            .height = static_cast<uint32_t>(m_height),
            .bit_depth = 8,
            .color_type = SPNG_COLOR_TYPE_TRUECOLOR,
        };

        auto *out = std::fopen(filename.data(), "wb");
        auto *ctx = spng_ctx_new(SPNG_CTX_ENCODER);
        {
            spng_set_png_file(ctx, out);
            spng_set_option(ctx, SPNG_ENCODE_TO_BUFFER, 1);
            spng_set_ihdr(ctx, &ihdr);

            auto ret = spng_encode_image(ctx, m_pixels.data(), m_pixels.size() * sizeof(T), SPNG_FMT_PNG,
                                         SPNG_ENCODE_FINALIZE);

            if (ret != 0)
            {
                printf("Error encoding image: %s\n", spng_strerror(ret));
            }
        }
        spng_ctx_free(ctx);

        fclose(out);
    }

  private:
    size_t m_width;
    size_t m_height;
    std::vector<T> m_pixels{};
};
