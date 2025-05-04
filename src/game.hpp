#pragma once

#include "pbullet.hpp"
#include "player.hpp"
#include <SDL3/SDL.h>
#include <memory>
#include <vector>

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

    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<PBullet>> pbullets;
};
} // namespace nanbou
