#pragma once

#include "ebullet.hpp"
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
    SDL_AudioDeviceID audio_device;
    SDL_AudioStream *audio_stream;

    bool b_quit;

    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<PBullet>> pbullets;
    std::vector<std::unique_ptr<EBullet>> ebullets;

    Uint8 *tung_buf;
    Uint32 tung_len;
};
} // namespace nanbou
