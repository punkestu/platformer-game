#include "obj.h"
struct Object *create_object(struct Vec2f pos)
{
    struct Object *obj = malloc(sizeof(struct Object));
    obj->pos = pos;
    return obj;
}
void destroy_object(struct Object *obj)
{
    free(obj);
}

struct Renderable *create_renderable(struct Object *obj, const SDL_Rect representation)
{
    struct Renderable *rend = malloc(sizeof(struct Renderable));
    rend->body = obj;
    rend->representation = representation;
    return rend;
}
void destroy_renderable(struct Renderable *rend)
{
    free(rend);
}

struct RenderableGL *create_renderable_gl(struct Object *obj, const struct Vec4f boundary)
{
    struct RenderableGL *rend = malloc(sizeof(struct RenderableGL));
    rend->body = obj;
    generate_shader(&rend->shaderID);
    glGenVertexArrays(1, &rend->vao);
    glBindVertexArray(rend->vao);
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    float vertices[] = {
        boundary.x, boundary.y,
        boundary.x + boundary.z, boundary.y,
        boundary.x + boundary.z, boundary.y + boundary.w,
        boundary.x, boundary.y + boundary.w};
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0};
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);
    return rend;
}
void set_uniform_value(struct RenderableGL *rend, const char *name, GLuint ty, void* value)
{
    glUseProgram(rend->shaderID);
    if (ty == GL_FLOAT)
        glUniform1f(glGetUniformLocation(rend->shaderID, name), *(float*)value);
    else if (ty == GL_FLOAT_VEC2)
        glUniform2fv(glGetUniformLocation(rend->shaderID, name), 1, (float*)value);
    else if (ty == GL_FLOAT_VEC4)
        glUniform4fv(glGetUniformLocation(rend->shaderID, name), 1, (float*)value);
    glUseProgram(0);
}
void destroy_renderable_gl(struct RenderableGL *rend)
{
    free(rend);
}

struct Movable *create_movable(struct Object *obj)
{
    struct Movable *mov = malloc(sizeof(struct Movable));
    mov->body = obj;
    mov->vel = (struct Vec2f){0, 0};
    return mov;
}
void destroy_movable(struct Movable *mov)
{
    free(mov);
}
void move_movable(struct Movable *mov, int delta)
{
    mov->body->pos.x += mov->vel.x * (float)delta / 1000.f;
    mov->body->pos.y += mov->vel.y * (float)delta / 1000.f;
}
void move_with_gravity(struct Movable *mov, const float gravity, int delta)
{
    mov->vel.y += gravity;
}
int move_dir(SDL_bool isMoveLeft, SDL_bool isMoveRight)
{
    return (isMoveLeft ? -1 : (isMoveRight ? 1 : 0));
}

struct Solid *create_solid(struct Object *body, const SDL_Rect collBox, const char dir)
{
    struct Solid *solid = malloc(sizeof(struct Solid));
    solid->body = body;
    solid->collBox = collBox;
    solid->dir = dir;
    return solid;
}
void destroy_solid(struct Solid *solid)
{
    free(solid);
}

struct SolidMovable *create_solid_movable(struct Movable *mov, const SDL_Rect collBox)
{
    struct SolidMovable *solidMov = malloc(sizeof(struct SolidMovable));
    solidMov->mov = mov;
    solidMov->collBox = collBox;
    return solidMov;
}
void destroy_solid_movable(struct SolidMovable *solidMov)
{
    free(solidMov);
}