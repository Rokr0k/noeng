#pragma once

#include "sprite.hpp"

namespace nanbou
{
class PBullet : public Sprite
{
  public:
    PBullet(SDL_Renderer *renderer, const SDL_FPoint &pos, const SDL_FPoint &dir);

    PBullet(const PBullet &) = delete;
    PBullet &operator=(const PBullet &) = delete;

    ~PBullet() override;

    void Update(double delta);
    void Render() const;

  private:
    SDL_FPoint dir;
};
} // namespace nanbou
