#pragma once

#include <SDL3/SDL.h>

namespace nanbou
{
class Player
{
  public:
    Player(SDL_Renderer *renderer);

    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;

    ~Player();

    void SetInputVector(float x, float y, float speed);

    void Update(double delta);
    void Render() const;

  private:
    SDL_Texture *sprite;
    float x, y;
    float ix, iy;
};
} // namespace nanbou
