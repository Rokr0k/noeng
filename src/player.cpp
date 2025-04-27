#include "player.hpp"

namespace nanbou
{
Player::Player(SDL_Renderer *renderer)
    : sprite(nullptr), x(0), y(0), ix(0), iy(0)
{
    SDL_Surface *surface = SDL_LoadBMP("res/redbull.bmp");
    sprite = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
}

Player::~Player()
{
    SDL_DestroyTexture(sprite);
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
    x += ix * delta;
    y += iy * delta;
}

void Player::Render() const
{
    SDL_Renderer *renderer = SDL_GetRendererFromTexture(sprite);

    SDL_FRect dst{x - 25, y - 25, 50, 50};
    SDL_RenderTexture(renderer, sprite, nullptr, &dst);
}
} // namespace nanbou
