#include "Pz/Core/Game.hpp"

class ExampleGame : public Pz::Core::Game
{
  private:
    void init() override
    {
        PZ_TRACE("This is a trace message");
        PZ_DEBUG("This is a debug message");
        PZ_INFO("This is an info message");
        PZ_WARN("This is a warning message");
        PZ_ERROR("This is an error message");
        PZ_CRITICAL("This is a critical message");

        glClearColor(0.2f, 0.4f, 0.8f, 1.0f);
    }

    void render() override
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
};

PZ_GAME_ENTRY(ExampleGame)
