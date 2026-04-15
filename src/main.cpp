#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "iostream"
#include "globals.hpp"
#include "renderer.hpp"

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Cellular Sandbox", NULL, NULL);
    if(!window){
        std::cout<<"FAILED TO CREATE GLFW WINDOW\n";
        glfwTerminate();
        return 0;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGL()){
        std::cout<<"FAILED TO LOAD OPENGL\n";
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    Renderer renderer;

    renderer.init();

    while(!glfwWindowShouldClose(window)){
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        renderer.draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    renderer.clean();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}