#include "game.hpp"

namespace nanbou
{
Game::Game()
    : window(nullptr), renderer(nullptr), b_quit(false), player(nullptr)
{
    SDL_CreateWindowAndRenderer("Nanbou", 1280, 720, 0, &window, &renderer);
    SDL_SetRenderVSync(renderer, 1);
    SDL_SetRenderLogicalPresentation(renderer, 0, 0,
                                     SDL_LOGICAL_PRESENTATION_DISABLED);

    player = std::make_unique<Player>(renderer);
}

Game::~Game()
{
    player.reset();
    pbullets.clear();

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

    double pbullet_cooltime = 0;

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
                if (event.key.repeat)
                    break;

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

        pbullet_cooltime -= delta;
        if (pbullet_cooltime < 0)
        {
            constexpr int div = 32;
            const float pi = 4 * SDL_atanf(1);
            for (float theta = 0; theta < pi * 2; theta += pi * 2 / div)
            {
                float speed = 500;
                pbullets.push_back(std::make_unique<PBullet>(
                    renderer, SDL_FPoint{player->Rect().x, player->Rect().y},
                    SDL_FPoint{speed * SDL_sinf(theta),
                               speed * SDL_cosf(theta)}));
            }

            pbullet_cooltime += 0.1f;
        }

        {
            SDL_FRect screen;
            SDL_GetRenderLogicalPresentationRect(renderer, &screen);

            auto it = pbullets.begin();
            while (it != pbullets.end())
            {
                (*it)->Update(delta);

                if (SDL_HasRectIntersectionFloat(&screen, &(*it)->Rect()))
                {
                    ++it;
                }
                else
                {
                    it = pbullets.erase(it);
                }
            }
        }

        SDL_SetRenderDrawColorFloat(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        player->Render();
        for (const std::unique_ptr<PBullet> &bullet : pbullets)
        {
            bullet->Render();
        }

        SDL_RenderPresent(renderer);
    }
}
} // namespace nanbou
