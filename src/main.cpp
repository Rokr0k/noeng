#include <SDL3/SDL.h>

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Nanbou", 1280, 720, 0);

    SDL_Delay(5000);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
