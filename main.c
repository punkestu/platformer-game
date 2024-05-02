#include <SDL2/SDL.h>
#include "src/obj/obj.h"
#include "src/renderer/renderer.h"
#include "src/factory/factory.h"
#include "game/level1/level1.h"

struct TheObject
{
    struct Object *obj;
    size_t index;
};

int main()
{
    const float gravity = 0.98f;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow(
        "Hello World",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    struct Factory *factory = create_list_mob();
    struct Level1Utils *level1Utils = level1_init(factory);

    int frame = 0;
    int ticker = 0;
    int currentTicks = SDL_GetTicks();

    SDL_Event e;
    while (1)
    {
        int delta = SDL_GetTicks() - currentTicks;
        currentTicks = SDL_GetTicks();

        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                break;
            }
#ifdef DEBUG
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    break;
                }
            }
#endif
            level1_handle_input(level1Utils, &e);
        }
        level1_update(level1Utils, delta);
        level1_render(level1Utils, renderer);

        frame++;
        ticker += delta;
        if (ticker >= 1000)
        {
            printf("FPS: %d | Ticker: %d\n", frame, ticker);
            frame = 0;
            ticker = 0;
        }
    }

    level1_destroy(level1Utils);
    destroy_list_mob(factory);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}