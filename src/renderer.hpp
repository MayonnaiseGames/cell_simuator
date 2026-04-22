#pragma once

//External
#include <glad.h>
#include <glfw3.h>
#include <vector>
#include <iostream>

//Internal
#include "shader_class.hpp"

class Renderer{
    public:
        Renderer();
        ~Renderer();
        void upload_data(std::vector<uint16_t> canvas_data, int canvas_width, int canvas_height);
        void draw();
        
        void fill_bg(float r, float g, float b, float a);

    private:
        GLuint VAO, VBO, EBO;
        Shader default_shader{"shaders/default.vert", "shaders/default.frag"};
        GLuint canvas_texture;
        int texture_width, texture_height;
        static constexpr GLfloat canvas_vertices[] = {
            //Pos            //Texture uv
            -1.0f, -1.0f, 0,  0.0f, 0.0f,
            1.0f, -1.0f, 0,  1.0f, 0.0f,
            1.0f,  1.0f, 0,  1.0f, 1.0f,
            -1.0f,  1.0f, 0,  0.0f, 1.0f
        };

        static constexpr GLint canvas_indicies[] = {
            0, 1, 2,
            2, 3, 0
        };
};