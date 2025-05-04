#include "pbullet.hpp"

namespace nanbou
{
PBullet::PBullet(SDL_Renderer *renderer, const SDL_FPoint &pos,
                 const SDL_FPoint &dir)
    : Sprite(renderer, "res/poo.bmp", {pos.x, pos.y, 25, 25}), dir(dir)
{
}

PBullet::~PBullet()
{
}

void PBullet::Update(double delta)
{
    Rect().x += dir.x * delta;
    Rect().y += dir.y * delta;
}

void PBullet::Render() const
{
    Sprite::Render();
}
} // namespace nanbou
