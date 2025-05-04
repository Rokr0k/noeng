#pragma once

#include <SDL3/SDL.h>

namespace nanbou
{
class Sprite
{
  public:
    Sprite(SDL_Renderer *renderer, const char *filename, const SDL_FRect &rect);

    Sprite(const Sprite &) = delete;
    Sprite &operator=(const Sprite &) = delete;

    virtual ~Sprite();

    SDL_FRect &Rect()
    {
        return rect;
    }

    const SDL_FRect &Rect() const
    {
        return rect;
    }

    void Render() const;

  private:
    SDL_Texture *texture;
    SDL_FRect rect;
};
} // namespace nanbou
