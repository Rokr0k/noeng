#include "game.hpp"

namespace nanbou
{
Game::Game() : window(nullptr), renderer(nullptr), b_quit(false), player(nullptr)
{
    SDL_CreateWindowAndRenderer("Nanbou", 1280, 720, 0, &window, &renderer);
    SDL_SetRenderVSync(renderer, 1);

    player = new Player(renderer);
}

Game::~Game()
{
    delete player;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Game::Run()
{
    Uint64 last_loop_tick = SDL_GetTicksNS();

    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;

    while (!b_quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_EVENT_QUIT:
                b_quit = true;
                break;
            case SDL_EVENT_KEY_DOWN:
            case SDL_EVENT_KEY_UP:
                switch (event.key.key)
                {
                case SDLK_UP:
                    up = event.key.down;
                    break;
                case SDLK_DOWN:
                    down = event.key.down;
                    break;
                case SDLK_LEFT:
                    left = event.key.down;
                    break;
                case SDLK_RIGHT:
                    right = event.key.down;
                    break;
                }
                break;
            }
        }

        Uint64 loop_tick = SDL_GetTicksNS();
        Uint64 delta_tick = loop_tick - last_loop_tick;
        double delta = delta_tick * 1e-9;
        last_loop_tick = loop_tick;

        player->SetInputVector((left ? -1 : 0) + (right ? 1 : 0),
                               (up ? -1 : 0) + (down ? 1 : 0), 300);
        player->Update(delta);

        SDL_SetRenderDrawColorFloat(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        player->Render();

        SDL_RenderPresent(renderer);
    }
}
} // namespace nanbou
