#include "Core/Game.hpp"

class ExampleGame : public Pz::Core::Game
{
  private:
    void render() override
    {
    }
};

int main(int argc, char **argv)
{
    ExampleGame game{};
    game.run();

    return EXIT_SUCCESS;
}
