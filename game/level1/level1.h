#ifndef LEVEL1_H__
#define LEVEL1_H__

#include "../../src/factory/factory.h"
#include "../../src/renderer/renderer.h"

struct Level1Utils
{
    struct Factory *factory;
    struct Mob *player;
    struct Mob *player2;
    struct Mob *player3;

    struct Vec2f camera;

    SDL_bool isMoveLeft;
    SDL_bool isMoveRight;
    SDL_bool isJumping;
};

struct Level1Utils *level1_init(struct Factory *factory);
void level1_update(struct Level1Utils *utils, int delta);
void level1_handle_input(struct Level1Utils *utils, SDL_Event *e);
void level1_render(struct Level1Utils *utils, SDL_Renderer *renderer);
void level1_destroy(struct Level1Utils *utils);

#endif // LEVEL1_H__