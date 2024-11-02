#pragma once

#include "../UI/Window.hpp"

#include <glad/glad.h>
#include <string_view>

namespace Pz::Core
{

class Game
{
  public:
    Game(std::string_view title = "Game", int width = 800, int height = 600);

    void run();

  private:
    virtual void init()
    {
    }

    virtual void update()
    {
    }

    virtual void render() = 0;

    virtual void cleanup()
    {
    }

  private:
    Pz::UI::Window window;
};

} // namespace Pz::Core
