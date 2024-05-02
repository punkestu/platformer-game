#include "level1.h"

const float gravity = 0.98f;

struct Level1Utils *level1_init(struct Factory *factory)
{
    struct Level1Utils *utils = malloc(sizeof(struct Level1Utils));
    utils->factory = factory;

    utils->player = create_mob(factory, (SDL_Rect){0, 0, 50, 50});
    utils->player2 = create_mob(factory, (SDL_Rect){0, 100, 50, 50});
    utils->player3 = create_mob(factory, (SDL_Rect){200, 100, 50, 50});
    struct Mob *ground = create_mob(factory, (SDL_Rect){0, 550, 800, 50});
    struct Mob *obstacle = create_mob(factory, (SDL_Rect){400, 500, 50, 50});
    struct Mob *ceiling = create_mob(factory, (SDL_Rect){400, 300, 400, 50});

    be_movable(factory, utils->player);
    be_movable(factory, utils->player2);
    be_movable(factory, utils->player3);

    be_solid_movable(factory, utils->player);
    be_solid_movable(factory, utils->player2);
    be_solid_movable(factory, utils->player3);

    be_solid(factory, ground, UP);
    be_solid(factory, obstacle, UP | DOWN | LEFT | RIGHT);
    be_solid(factory, ceiling, DOWN);

    utils->isJumping = SDL_FALSE;
    utils->isMoveLeft = SDL_FALSE;
    utils->isMoveRight = SDL_FALSE;
}
void level1_update(struct Level1Utils *utils, int delta)
{
    utils->player->mov->vel.x = move_dir(utils->isMoveLeft, utils->isMoveRight) * 200;
    if (utils->player2->mov->isGrounded)
        utils->player2->mov->vel.x = 100;
    if (utils->player3->mov->isGrounded)
        utils->player3->mov->vel.x = -100;

    move_with_gravity(utils->player->mov, gravity, delta);
    move_with_gravity(utils->player2->mov, gravity, delta);
    move_with_gravity(utils->player3->mov, gravity, delta);

    if (utils->isJumping && utils->player->mov->isGrounded)
    {
        utils->player->mov->vel.y = -400;
    }

    utils->player->mov->isGrounded = SDL_FALSE;

    block_with_solid_movables(utils->factory->solidMovable, delta);
    block_with_solids(utils->factory->movable, utils->factory->solid, delta);
    move_movable(utils->player->mov, delta);
    move_movable(utils->player2->mov, delta);
    move_movable(utils->player3->mov, delta);
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
    render_objs(renderer, utils->factory->obj);

    SDL_RenderPresent(renderer);
}
void level1_destroy(struct Level1Utils *utils)
{
    delete_mob(utils->factory, utils->player);
    delete_mob(utils->factory, utils->player2);
    delete_mob(utils->factory, utils->player3);
    free(utils);
}