#pragma once

#include "Window.hpp"

#include <memory>
#include <string_view>

class Game
{
  public:
    Game(std::string_view title = "Game", int width = 800, int height = 600);
    virtual ~Game()
    {
    }

    [[nodiscard]] int width() const
    {
        return m_width;
    }

    [[nodiscard]] int height() const
    {
        return m_height;
    }

    virtual void setup()
    {
    }

    virtual void update()
    {
    }

    virtual void cleanup()
    {
    }

    virtual void render()
    {
    }

    void run();

  private:
    std::unique_ptr<Window> m_window{};
    int m_width{};
    int m_height{};
};