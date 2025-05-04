#pragma once

#include "sprite.hpp"
#include <SDL3/SDL.h>

namespace nanbou
{
class Player : public Sprite
{
  public:
    Player(SDL_Renderer *renderer);

    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;

    ~Player() override;

    void SetInputVector(float x, float y, float speed);

    void Update(double delta);
    void Render() const;

  private:
    float ix, iy;
};
} // namespace nanbou
