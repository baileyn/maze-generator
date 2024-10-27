#pragma once

#include <stdexcept>

/**
 * @brief Exception class for unimplemented functions.
 *
 * This exception is thrown when a function that has not been implemented is called.
 */
class NotImplemented : public std::logic_error
{
  public:
    /**
     * @brief Constructs a NotImplemented exception with a default error message.
     */
    NotImplemented() : std::logic_error("Function not yet implemented"){};
};
