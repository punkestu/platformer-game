#ifndef GL_ENGINE_H___
#define GL_ENGINE_H___

#include "../include.h"

struct Vec2f
{
    float x;
    float y;
};
struct Vec4f
{
    float x;
    float y;
    float z;
    float w;
};

int generate_shader(GLuint *shaderID);
const struct Vec2f vec2f_px_to_gl(const struct Vec2f boundary, const struct Vec2f window);
const struct Vec2f vec2f_px_to_gl_translated(const struct Vec2f boundary, const struct Vec2f window);
float* vec2f_to_gl(const struct Vec2f boundary);
const struct Vec4f vec4f_px_to_gl(const struct Vec4f boundary, const struct Vec2f window);

#endif // GL_ENGINE_H___