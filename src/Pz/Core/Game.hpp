#pragma once

#include "../UI/Window.hpp"

#include <glad/glad.h>
#include <spdlog/cfg/argv.h>
#include <spdlog/spdlog.h>
#include <string_view>

namespace Pz::Core
{

class Game
{
  public:
    Game(std::string_view title = "Game", int width = 800, int height = 600);

    void run();

  protected:
    float width() const
    {
        return m_width;
    }

    float height() const
    {
        return m_height;
    }

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

    float m_width{};
    float m_height{};
};

} // namespace Pz::Core

template <typename GameType> int run_game(int argc, char **argv)
{
    spdlog::cfg::load_argv_levels(argc, argv);

    GameType game{};
    game.run();

    return EXIT_SUCCESS;
}

#define PZ_GAME_ENTRY(GameType)                                                                                        \
    int main(int argc, char **argv)                                                                                    \
    {                                                                                                                  \
        Pz::Core::Logger::init(#GameType);                                                                             \
        return run_game<GameType>(argc, argv);                                                                         \
    }
