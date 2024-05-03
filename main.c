#include "src/engine.h"
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

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context)
    {
        printf("Failed to create OpenGL context: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK)
    {
        printf("GLEW initialization failed: %s\n", glewGetErrorString(glewError));
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    glViewport(0, 0, 800, 600);

    struct Factory *factory = create_factory();
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
        // level1_render(level1Utils, renderer);
        level1_render_gl(level1Utils, window);

        frame++;
        ticker += delta;
        if (ticker >= 1000)
        {
            printf("FPS: %d | Ticker: %d\n", frame, ticker);
            frame = 0;
            ticker = 0;
        }
    }

    SDL_Log("Exiting...");

    level1_destroy(level1Utils);
    SDL_Log("Exited successfully!");
    destroy_factory(factory);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}