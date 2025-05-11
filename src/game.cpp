#include "game.hpp"
#include <random>

namespace nanbou
{
Game::Game()
    : window(nullptr), renderer(nullptr), audio_device(0),
      audio_stream(nullptr), b_quit(false), player(nullptr), tung_buf(nullptr),
      tung_len(0)
{
    SDL_CreateWindowAndRenderer("Nanbou", 1280, 720, 0, &window, &renderer);
    SDL_SetRenderVSync(renderer, 1);
    SDL_SetRenderLogicalPresentation(renderer, 0, 0,
                                     SDL_LOGICAL_PRESENTATION_DISABLED);

    audio_device =
        SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    audio_stream = SDL_CreateAudioStream(nullptr, nullptr);
    SDL_BindAudioStream(audio_device, audio_stream);

    player = std::make_unique<Player>(renderer);

    SDL_AudioSpec audio_spec;
    SDL_LoadWAV("res/tung.wav", &audio_spec, &tung_buf, &tung_len);

    SDL_SetAudioStreamFormat(audio_stream, &audio_spec, nullptr);
}

Game::~Game()
{
    player.reset();
    pbullets.clear();
    ebullets.clear();

    SDL_free(tung_buf);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_DestroyAudioStream(audio_stream);
    SDL_CloseAudioDevice(audio_device);
}

void Game::Run()
{
    Uint64 last_loop_tick = SDL_GetTicksNS();

    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;

    double pbullet_cooltime = 0;
    double ebullet_cooltime = 0;
    float ebullet_offset = 0;

    std::random_device rd;

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
        if (pbullet_cooltime < 0 && 0)
        {
            constexpr int div = 32;
            const float pi = 4 * SDL_atanf(1);
            for (float theta = 0; theta < pi * 2; theta += pi * 2 / div)
            {
                float speed = 500;
                pbullets.push_back(std::make_unique<PBullet>(
                    renderer, SDL_FPoint{player->Rect().x, player->Rect().y},
                    SDL_FPoint{speed * SDL_cosf(theta),
                               speed * SDL_sinf(theta)}));
            }

            pbullet_cooltime += 0.1f;
        }

        ebullet_cooltime -= delta;
        if (ebullet_cooltime < 0)
        {
            constexpr int div = 16;
            const float pi = 4 * SDL_atanf(1);
            for (float theta = 0; theta < pi * 2; theta += pi * 2 / div)
            {
                float speed = 300;
                ebullets.push_back(std::make_unique<EBullet>(
                    renderer, SDL_FPoint{640, 0},
                    SDL_FPoint{
                        speed * SDL_cosf(theta + ebullet_offset),
                        speed * SDL_sinf(theta + ebullet_offset),
                    }));
            }

            ebullet_cooltime += 0.2f;
            ebullet_offset += pi * 2 / 6 / div;
        }

        {
            SDL_FRect screen;
            SDL_GetRenderLogicalPresentationRect(renderer, &screen);

            auto pit = pbullets.begin();
            while (pit != pbullets.end())
            {
                (*pit)->Update(delta);

                if (SDL_HasRectIntersectionFloat(&screen, &(*pit)->Rect()))
                {
                    ++pit;
                }
                else
                {
                    pit = pbullets.erase(pit);
                }
            }

            SDL_FRect playerCenter = {
                player->Rect().x + player->Rect().w / 2,
                player->Rect().y + player->Rect().h / 2,
                0,
                0,
            };

            auto eit = ebullets.begin();
            while (eit != ebullets.end())
            {
                (*eit)->Update(delta);

                if (!SDL_HasRectIntersectionFloat(&screen, &(*eit)->Rect()))
                {
                    eit = ebullets.erase(eit);
                    continue;
                }

                if (SDL_HasRectIntersectionFloat(&playerCenter,
                                                 &(*eit)->Rect()))
                {
                    SDL_ClearAudioStream(audio_stream);
                    SDL_PutAudioStreamData(audio_stream, tung_buf, tung_len);
                    SDL_FlushAudioStream(audio_stream);

                    eit = ebullets.erase(eit);
                    continue;
                }

                ++eit;
            }
        }

        SDL_SetRenderDrawColorFloat(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        player->Render();
        for (const std::unique_ptr<PBullet> &bullet : pbullets)
        {
            bullet->Render();
        }
        for (const std::unique_ptr<EBullet> &bullet : ebullets)
        {
            bullet->Render();
        }

        SDL_RenderPresent(renderer);
    }
}
} // namespace nanbou
