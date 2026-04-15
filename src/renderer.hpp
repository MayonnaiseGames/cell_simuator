#pragma once

#include "glad/glad.h"
#include "globals.hpp"
#include "shader_class.h"

const GLfloat canvas_verticies[] = {
    -1, 1, 0, //top left
    -1, -1, 0, //bottom left
    1, 1, 0, //top right
    1, -1, 0, //bottom right

};

const GLuint canvas_indicies[] = {
    0, 1, 2,
    2, 3, 1
};

class Renderer{
    public:
    void init();
    void draw();
    void clean();
    private:
    Shader default_shader{"shaders/default.vert", "shaders/default.frag"};
    GLuint VAO, VBO, EBO;
    
};
