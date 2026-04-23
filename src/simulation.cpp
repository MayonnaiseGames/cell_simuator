#include "simulation.hpp"

Simulation::Simulation(int Window_width, int Window_height){
    window_width = Window_width; window_height = Window_height;
}

void Simulation::update(GLFWwindow* window, int grid_width, int grid_height){
    //Input

    //Find mouse position
    {
        glfwGetCursorPos(window, &mouse_x, &mouse_y);
    mouse_y = window_height - mouse_y;
    }
    
    switch (settings.game_mode)
    {
    case 1:
        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) ==  GLFW_PRESS){
            int cell_x = static_cast<int>(mouse_x * grid_width / window_width);
            int cell_y = static_cast<int>(mouse_y * grid_height / window_height);
            set_state(cell_x, cell_y, grid_width, grid_height, 1);
        }
        gol();
        break;
    
    default:
        break;
    }
    
}

void Simulation::gol(){
    
}

void Simulation::fill_random(int width, int height, int type){
    data.clear();
    for (int i = 0; i < width * height; i++){
        data.push_back(((rand() % 11) <= 5) ? type : 0);
    }
}

void Simulation::clear(int width, int height, int type){
    data.assign(width * height, type);
}

int Simulation::get_state(int x, int y, int width, int height){
    int value;
    value = data[y * width + x];
    return value;
}

void Simulation::set_state(int x, int y, int width, int height, int value){
    if(x >= 0 && x < width && y >= 0 && y < height){
        data[y * width + x] = value;
    }
    
}
