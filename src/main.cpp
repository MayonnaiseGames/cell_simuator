//External
#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <vector>

//Internal
#include "renderer.hpp"
#include "settings.hpp"
#include "simulation.hpp"

//Constants
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

//Variables
int grid_size = 100;

int main(){
    //Create window 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //telling GLFW what opengl version thats being used
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,  GLFW_OPENGL_CORE_PROFILE); //telling GLFW using modern opengl
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Cell and Particle Simulation Engine", NULL, NULL);
    if(!window){
        std::cout<<"Window failed to create!\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); //make the window the current one for the opengl context

    //Load OpenGL
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout<<"OpenGL failed to load!\n";
        return -1;
    }
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    //Initialise the renderer to display the texture
    Renderer renderer = Renderer();

    //Initialise the simulation
    Simulation simulation = Simulation(WINDOW_WIDTH, WINDOW_HEIGHT);

    //Initialise ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    simulation.clear(grid_size, grid_size, 0);
    srand(time(0));
    while(!glfwWindowShouldClose(window)){
        //Update game
        simulation.update(window, grid_size, grid_size);
        
        //simulation.set_state(200, 200, grid_size, grid_size, 1);
        simulation.fill_random(grid_size, grid_size, 1);


        //Render game
        renderer.upload_data(simulation.data, grid_size, grid_size);
        renderer.draw();

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //Menu UI
        {   
            ImGui::Begin("Menu", nullptr,  ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
            if(ImGui::CollapsingHeader("Simulation options")){
                ImGui::Text("Size: %dx%d", grid_size, grid_size);
                if(ImGui::Button("+ Grid size") && grid_size < 500){
                    grid_size += 20;
                    simulation.clear(grid_size, grid_size, 0);
                }
                if(ImGui::Button("- Grid size") && grid_size > 20){
                    grid_size -= 20;
                    simulation.clear(grid_size, grid_size, 0);
                }
                if(ImGui::Button("Clear grid")){
                    simulation.clear(grid_size, grid_size, 0);
                }
                if(ImGui::Button("Fill random")){
                    simulation.fill_random(grid_size, grid_size, 1);
                }
            }
            if(ImGui::CollapsingHeader("Game modes")){
                if(ImGui::Button("Game of life mode")){
                    settings.game_mode = 1;
                }
            }
            if(ImGui::CollapsingHeader("Settings")){
                ImGui::Checkbox("Wireframe rendering", &settings.wireframe);
                ImGui::Checkbox("Show debug menu", &settings.show_debug);
                ImGui::Checkbox("Show console", &settings.show_console);
            }

            ImGui::End();
        }

        //Handle settings
        {
            if(settings.show_debug){
                ImGui::Begin("Debug menu", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
                ImGuiIO& io = ImGui::GetIO();
                ImGui::Text("FPS: %.0f", io.Framerate);
                ImGui::Text("Frame time: %.3f ms", 1000.0f / io.Framerate);
                ImGui::End();
            }

            if(settings.show_console){
                ImGui::Begin("Console");
                ImGui::End();
            }

            if(settings.wireframe){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            else{
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); 

        //Update frame
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Free memory
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}