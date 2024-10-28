#include "Game.hpp"

#include <glad/glad.h>

class MazeGame : public Game
{
  public:
    void setup() override
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
    MazeGame game{};
    game.run();

    return EXIT_SUCCESS;
}