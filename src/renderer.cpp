#include "renderer.hpp"

void Renderer::init(){
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(canvas_verticies), canvas_verticies, GL_STATIC_DRAW);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(canvas_indicies), canvas_indicies, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Renderer::draw(){
    default_shader.activate();
    glBindVertexArray(VAO); //bind the vao that the data was written too
    glDrawElements(GL_TRIANGLES, sizeof(canvas_indicies)/sizeof(GLuint), GL_UNSIGNED_INT, 0); //draw that data according to the triangle primative
}

void Renderer::clean(){
    glDeleteVertexArrays(1, &VAO); 
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    default_shader.destroy();
}
