#include "player.hpp"

namespace nanbou
{
Player::Player(SDL_Renderer *renderer)
    : Sprite(renderer, "res/redbull.bmp", {0, 0, 50, 50}), ix(0), iy(0)
{
}

Player::~Player()
{
}

void Player::SetInputVector(float x, float y, float speed)
{
    float length = SDL_sqrtf(x * x + y * y);
    if (length > 0)
    {
        ix = x / length * speed;
        iy = y / length * speed;
    }
    else
    {
        ix = iy = 0;
    }
}

void Player::Update(double delta)
{
    Rect().x += ix * delta;
    Rect().y += iy * delta;
}

void Player::Render() const
{
    Sprite::Render();
}
} // namespace nanbou
