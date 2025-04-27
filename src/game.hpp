#pragma once

#include <SDL3/SDL.h>
#include "player.hpp"

namespace nanbou
{
class Game
{
  public:
    Game();

    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;

    ~Game();

    void Run();

  private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool b_quit;

    Player *player;
};
} // namespace nanbou
