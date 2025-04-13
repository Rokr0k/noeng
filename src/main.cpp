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

    bool upDown = false, downDown = false;
    bool leftDown = false, rightDown = false;
    float x = 0, y = 0;
    float speed = 300;

    Uint64 lastLoopTick = SDL_GetTicksNS();

    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_EVENT_QUIT:
                quit = true;
                break;
            case SDL_EVENT_KEY_DOWN:
            case SDL_EVENT_KEY_UP:
                switch (event.key.key)
                {
                case SDLK_UP:
                    upDown = event.key.down;
                    break;
                case SDLK_DOWN:
                    downDown = event.key.down;
                    break;
                case SDLK_LEFT:
                    leftDown = event.key.down;
                    break;
                case SDLK_RIGHT:
                    rightDown = event.key.down;
                    break;
                }
                break;
            }
        }

        Uint64 loopTick = SDL_GetTicksNS();
        Uint64 deltaTick = loopTick - lastLoopTick;
        double delta = deltaTick * 1e-9;
        lastLoopTick = loopTick;

        float moveX = 0, moveY = 0;

        if (upDown)
            moveY -= 1;
        if (downDown)
            moveY += 1;
        if (leftDown)
            moveX -= 1;
        if (rightDown)
            moveX += 1;

        // normalize
        float length = SDL_sqrtf(moveX * moveX + moveY * moveY);
        if (length > 0)
        {
            moveX /= length;
            moveY /= length;
        }

        x += moveX * speed * delta;
        y += moveY * speed * delta;

        SDL_SetRenderDrawColorFloat(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        SDL_FRect dst = {x, y, 50, 50};
        SDL_RenderTexture(renderer, texture, nullptr, &dst);

        SDL_SetRenderScale(renderer, 2, 2);
        SDL_SetRenderDrawColorFloat(renderer, 1, 1, 1, 1);
        SDL_RenderDebugTextFormat(renderer, 0, 0, "FPS: %.0lf (%.2lfms)",
                                  1 / delta, delta * 1e3);
        SDL_SetRenderScale(renderer, 1, 1);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
