#include "ebullet.hpp"

namespace nanbou
{
EBullet::EBullet(SDL_Renderer *renderer, const SDL_FPoint &pos,
                 const SDL_FPoint &dir)
    : Sprite(renderer, "res/poo.bmp",
             {pos.x - 25 * 0.5f, pos.y - 25 * 0.5f, 25, 25}),
      dir(dir)
{
}

EBullet::~EBullet()
{
}

void EBullet::Update(double delta)
{
    Rect().x += dir.x * delta;
    Rect().y += dir.y * delta;
}

void EBullet::Render() const
{
    Sprite::Render();
}
} // namespace nanbou
