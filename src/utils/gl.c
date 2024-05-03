#include "gl.h"

int generate_shader(GLuint *shaderID)
{
    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec2 aPos;\n"
                                     "uniform vec2 gPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position = vec4(aPos.x + gPos.x, aPos.y + gPos.y, 0.0, 1.0);\n"
                                     "}\0";

    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\0";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    GLchar infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("Vertex shader compilation failed: %s\n", infoLog);
        return 1;
    }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("Fragment shader compilation failed: %s\n", infoLog);
        return 1;
    }

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("Shader program linking failed: %s\n", infoLog);
        return 1;
    }

    *shaderID = shaderProgram;

    return 0;
}
const struct Vec2f vec2f_px_to_gl(const struct Vec2f boundary, const struct Vec2f window)
{
    struct Vec2f glBoundary;
    glBoundary.x = (boundary.x / (window.x / 2));
    glBoundary.y = (boundary.y / (window.y / 2));
    return glBoundary;
}
const struct Vec2f vec2f_px_to_gl_translated(const struct Vec2f boundary, const struct Vec2f window)
{
    struct Vec2f glBoundary;
    glBoundary.x = (boundary.x / (window.x / 2)) - 1;
    glBoundary.y = (boundary.y / (window.y / 2)) - 1;
    return glBoundary;
}
float *vec2f_to_gl(const struct Vec2f boundary)
{
    float *glBoundary = malloc(sizeof(float) * 2);
    glBoundary[0] = boundary.x;
    glBoundary[1] = -boundary.y;
    return glBoundary;
}
const struct Vec4f vec4f_px_to_gl(const struct Vec4f boundary, const struct Vec2f window)
{
    struct Vec4f glBoundary;
    glBoundary.x = (boundary.x / (window.x / 2));
    glBoundary.y = (boundary.y / (window.y / 2));
    glBoundary.z = (boundary.z / (window.x / 2));
    glBoundary.w = (boundary.w / (window.y / 2));
    return glBoundary;
}