#pragma once

#include "sprite.hpp"

namespace nanbou
{
class EBullet : public Sprite
{
  public:
    EBullet(SDL_Renderer *renderer, const SDL_FPoint &pos, const SDL_FPoint &dir);

    EBullet(const EBullet &) = delete;
    EBullet &operator=(const EBullet &) = delete;

    ~EBullet() override;

    void Update(double delta);
    void Render() const;

  private:
    SDL_FPoint dir;
};
} // namespace nanbou
