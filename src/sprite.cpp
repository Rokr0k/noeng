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

    SDL_FRect dst{rect.x - rect.w * 0.5f, rect.y - rect.h * 0.5f, rect.w,
                  rect.h};
    SDL_RenderTexture(renderer, texture, nullptr, &dst);
}
} // namespace nanbou
