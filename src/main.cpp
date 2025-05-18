#include "defer.hpp"
#include "game.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD);
    auto sdl_quit_deferrer = nanbou::MakeDefer([]() { SDL_Quit(); });

    nanbou::Game game;
    game.Run();

    return 0;
}
