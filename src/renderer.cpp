#include "renderer.hpp"

Renderer::Renderer(){
    //Create VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //Create VBO and EBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(canvas_vertices), canvas_vertices, GL_STATIC_DRAW);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(canvas_indicies), canvas_indicies, GL_STATIC_DRAW);

    //Bind vertex array attributes
    glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT,GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);


    //Unbind VAO, VBO, and EBO
    glBindVertexArray(0); glBindBuffer(GL_ARRAY_BUFFER, 0); glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenTextures(1, &canvas_texture);

    glBindTexture(GL_TEXTURE_2D, canvas_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0); //unbind
}

Renderer::~Renderer(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Renderer::upload_data(std::vector<uint16_t> canvas_data, int canvas_width, int canvas_height){

    glBindTexture(GL_TEXTURE_2D, canvas_texture);

    if(texture_width == canvas_width && texture_height == canvas_height){
        glTexSubImage2D(
            GL_TEXTURE_2D,
            0,
            0,
            0,
            texture_width,
            texture_height,
            GL_RED_INTEGER,
            GL_UNSIGNED_SHORT,
            canvas_data.data()
        );
    }
    else{
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_R16UI,
            canvas_width,
            canvas_height,
            0,
            GL_RED_INTEGER,
            GL_UNSIGNED_SHORT,
            canvas_data.data()
        );

        texture_width = canvas_width; texture_height = canvas_height;
    }

    glBindTexture(GL_TEXTURE_2D, 0); //unbind

}

void Renderer::draw(){
    glClearColor(0.3, 0.3, 0.3, 1.0); //clear the colour buffer bit into a dark blue
    glClear(GL_COLOR_BUFFER_BIT); //clear back buffer with that colour bit i just wrote too

    default_shader.activate();
    GLint texture_uniform = glGetUniformLocation(default_shader.ID, "canvasTex");
    glUniform1i(texture_uniform, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, canvas_texture);

    glBindVertexArray(VAO); //bind the vao that the data was written too
    glDrawElements(GL_TRIANGLES, sizeof(canvas_indicies)/sizeof(GLuint), GL_UNSIGNED_INT, 0); //draw that data according to the triangle primative
    
}

void Renderer::fill_bg(float r, float g, float b, float a){
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

