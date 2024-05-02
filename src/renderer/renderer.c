#include "renderer.h"

void render(SDL_Renderer *renderer, struct Object *obj)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &obj->representation);
}
void render_objs(SDL_Renderer *renderer, struct List *listObj)
{
    for (int i = 0; i < listObj->size; i++)
    {
        struct Object *obj = (struct Object *)get(listObj, i);
        render(renderer, obj);
    }
}