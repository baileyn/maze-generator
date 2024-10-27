#pragma once

/**
 * Represents a pixel with red, green, and blue color components.
 *
 * @tparam T The type of the color components (e.g., uint8_t for 8-bit color).
 */
template <typename T> struct Pixel
{
    T r; ///< The red component of the pixel.
    T g; ///< The green component of the pixel.
    T b; ///< The blue component of the pixel.

    /**
     * Constructs a Pixel with the specified red, green, and blue components.
     *
     * @param r The red component.
     * @param g The green component.
     * @param b The blue component.
     */
    Pixel(T r, T g, T b) : r{r}, g{g}, b{b}
    {
    }

    /**
     * Constructs a grayscale Pixel where all color components are the same.
     *
     * @param grayscale The value for the red, green, and blue components.
     */
    Pixel(T grayscale) : Pixel(grayscale, grayscale, grayscale)
    {
    }

    /**
     * Constructs a Pixel with all color components set to zero.
     */
    Pixel() : Pixel(0)
    {
    }
};
