#include "level1.h"

const float gravity = 0.98f;

struct Level1Utils *level1_init(struct Factory *factory)
{
    struct Level1Utils *utils = malloc(sizeof(struct Level1Utils));
    utils->factory = factory;

    utils->player = create_mob(factory, (struct Vec2f){0, 0});
    utils->player2 = create_mob(factory, (struct Vec2f){0, 100});
    utils->player3 = create_mob(factory, (struct Vec2f){200, 100});
    struct Mob *ground = create_mob(factory, (struct Vec2f){0, 550});
    struct Mob *obstacle = create_mob(factory, (struct Vec2f){400, 500});
    struct Mob *ceiling = create_mob(factory, (struct Vec2f){400, 300});

    SDL_Log("Level 1 initialize...");

    be_renderable_gl(factory, utils->player, vec4f_px_to_gl((const struct Vec4f){0, 0, 50, 50}, (struct Vec2f){800, 600}));
    be_renderable_gl(factory, utils->player2, vec4f_px_to_gl((const struct Vec4f){0, 0, 50, 50}, (struct Vec2f){800, 600}));
    be_renderable_gl(factory, utils->player3, vec4f_px_to_gl((const struct Vec4f){0, 0, 50, 50}, (struct Vec2f){800, 600}));
    be_renderable_gl(factory, ground, vec4f_px_to_gl((const struct Vec4f){0, 0, 800, 50}, (struct Vec2f){800, 600}));
    be_renderable_gl(factory, obstacle, vec4f_px_to_gl((const struct Vec4f){0, 0, 50, 50}, (struct Vec2f){800, 600}));
    be_renderable_gl(factory, ceiling, vec4f_px_to_gl((const struct Vec4f){0, 0, 400, 50}, (struct Vec2f){800, 600}));

    for (size_t i = 0; i < factory->renderableGL->size; i++)
    {
        struct RenderableGL *rend = (struct RenderableGL *)get(factory->renderableGL, i);
        glUseProgram(rend->shaderID);
        set_uniform_value(rend, "gPos", GL_FLOAT_VEC2, (float *)vec2f_to_gl(vec2f_px_to_gl_translated((struct Vec2f){rend->body->pos.x, rend->body->pos.y}, (struct Vec2f){800, 600})));
    }

    // be_renderable(factory, utils->player, (SDL_Rect){0, 0, 50, 50});
    // be_renderable(factory, utils->player2, (SDL_Rect){0, 0, 50, 50});
    // be_renderable(factory, utils->player3, (SDL_Rect){0, 0, 50, 50});
    // be_renderable(factory, ground, (SDL_Rect){0, 0, 800, 50});
    // be_renderable(factory, obstacle, (SDL_Rect){0, 0, 50, 50});
    // be_renderable(factory, ceiling, (SDL_Rect){0, 0, 400, 50});

    be_movable(factory, utils->player);
    be_movable(factory, utils->player2);
    be_movable(factory, utils->player3);

    be_solid_movable(factory, utils->player, (SDL_Rect){0, 0, 50, 50});
    be_solid_movable(factory, utils->player2, (SDL_Rect){0, 0, 50, 50});
    be_solid_movable(factory, utils->player3, (SDL_Rect){0, 0, 50, 50});

    be_solid(factory, ground, (SDL_Rect){0, 0, 800, 50}, UP);
    be_solid(factory, obstacle, (SDL_Rect){0, 0, 50, 50}, UP | DOWN | LEFT | RIGHT);
    be_solid(factory, ceiling, (SDL_Rect){0, 0, 400, 50}, DOWN);

    utils->isJumping = SDL_FALSE;
    utils->isMoveLeft = SDL_FALSE;
    utils->isMoveRight = SDL_FALSE;

    SDL_Log("Level 1 initialized!");

    return utils;
}
void level1_update(struct Level1Utils *utils, int delta)
{
    utils->player->mov->vel.x = move_dir(utils->isMoveLeft, utils->isMoveRight) * 200;
    if (utils->player2->solidMov->isColliding & DOWN)
        utils->player2->mov->vel.x = 100;
    if (utils->player3->solidMov->isColliding & DOWN)
        utils->player3->mov->vel.x = -100;

    move_with_gravity(utils->player->mov, gravity, delta);
    move_with_gravity(utils->player2->mov, gravity, delta);
    move_with_gravity(utils->player3->mov, gravity, delta);

    if (utils->isJumping && utils->player->solidMov->isColliding & DOWN)
    {
        utils->player->mov->vel.y = -400;
    }

    block_with_solid_movables(utils->factory->solidMovable, delta);
    block_with_solids(utils->factory->solidMovable, utils->factory->solid, delta);
    move_movable(utils->player->mov, delta);
    move_movable(utils->player2->mov, delta);
    move_movable(utils->player3->mov, delta);

    set_uniform_value(utils->player->rendGL, "gPos", GL_FLOAT_VEC2, (float *)vec2f_to_gl(vec2f_px_to_gl_translated((struct Vec2f){utils->player->obj->pos.x, utils->player->obj->pos.y}, (struct Vec2f){800, 600})));
    set_uniform_value(utils->player2->rendGL, "gPos", GL_FLOAT_VEC2, (float *)vec2f_to_gl(vec2f_px_to_gl_translated((struct Vec2f){utils->player2->obj->pos.x, utils->player2->obj->pos.y}, (struct Vec2f){800, 600})));
    set_uniform_value(utils->player3->rendGL, "gPos", GL_FLOAT_VEC2, (float *)vec2f_to_gl(vec2f_px_to_gl_translated((struct Vec2f){utils->player3->obj->pos.x, utils->player3->obj->pos.y}, (struct Vec2f){800, 600})));
}
void level1_handle_input(struct Level1Utils *utils, SDL_Event *e)
{
    if (e->type == SDL_KEYDOWN)
    {
        if (e->key.keysym.sym == SDLK_a)
        {
            utils->isMoveLeft = SDL_TRUE;
        }
        if (e->key.keysym.sym == SDLK_d)
        {
            utils->isMoveRight = SDL_TRUE;
        }
        if (e->key.keysym.sym == SDLK_SPACE)
        {
            utils->isJumping = SDL_TRUE;
        }
    }
    if (e->type == SDL_KEYUP)
    {
        if (e->key.keysym.sym == SDLK_a)
        {
            utils->isMoveLeft = SDL_FALSE;
        }
        if (e->key.keysym.sym == SDLK_d)
        {
            utils->isMoveRight = SDL_FALSE;
        }
        if (e->key.keysym.sym == SDLK_SPACE)
        {
            utils->isJumping = SDL_FALSE;
        }
    }
}
void level1_render(struct Level1Utils *utils, SDL_Renderer *renderer)
{
    follow_camera(&utils->camera, utils->player->mov);
    move_camera(utils->factory->obj, &utils->camera);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    render_objs(renderer, utils->factory->renderable);

    SDL_RenderPresent(renderer);
}

void level1_render_gl(struct Level1Utils *utils, SDL_Window *window)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    render_objs_gl(utils->factory->renderableGL);
    SDL_GL_SwapWindow(window);
}

void level1_destroy(struct Level1Utils *utils)
{
    delete_mob(utils->factory, utils->player);
    delete_mob(utils->factory, utils->player2);
    delete_mob(utils->factory, utils->player3);
    free(utils);
}