#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_CreateWindowAndRenderer("Nanbou", 1280, 720, 0, &window, &renderer);
    SDL_SetRenderVSync(renderer, 1);

    SDL_Surface *surface = SDL_LoadBMP("res/redbull.bmp");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                quit = true;
            }
        }

        SDL_SetRenderDrawColorFloat(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        SDL_RenderTexture(renderer, texture, nullptr, nullptr);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
