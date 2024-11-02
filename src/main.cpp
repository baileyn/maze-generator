#include "Core/Game.hpp"

class ExampleGame : public Pz::Core::Game
{
  private:
    void init() override
    {
        glClearColor(0.2f, 0.4f, 0.8f, 1.0f);
    }

    void render() override
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
};

int main(int argc, char **argv)
{
    ExampleGame game{};
    game.run();

    return EXIT_SUCCESS;
}
