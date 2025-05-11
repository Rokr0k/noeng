#include "sprite.hpp"

namespace nanbou
{
Sprite::Sprite(SDL_Renderer *renderer, const char *filename,
               const SDL_FRect &rect)
    : texture(nullptr), rect(rect)
{
    SDL_Surface *surface = SDL_LoadBMP(filename);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(texture);
}

void Sprite::Render() const
{
    SDL_Renderer *renderer = SDL_GetRendererFromTexture(texture);
    SDL_RenderTexture(renderer, texture, nullptr, &rect);
}
} // namespace nanbou
