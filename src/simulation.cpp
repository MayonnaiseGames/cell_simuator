#include "simulation.hpp"

Simulation::Simulation(int Window_width, int Window_height){
    window_width = Window_width; window_height = Window_height;
}

void Simulation::update(GLFWwindow* window, int Grid_width, int Grid_height){
    grid_width = Grid_width; grid_height = Grid_height;
    //Input

    //Find mouse position
    {
        glfwGetCursorPos(window, &mouse_x, &mouse_y);
        mouse_y = window_height - mouse_y;
    }

    if(glfwGetKey(window, GLFW_KEY_SPACE)){
        running = false;
    }
    if(glfwGetKey(window, GLFW_KEY_P)){
        running = true;
    }
    

  
    switch (settings.game_mode){
        case 1:
            if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) ==  GLFW_PRESS){
                int cell_x = static_cast<int>(mouse_x * grid_width / window_width);
                int cell_y = static_cast<int>(mouse_y * grid_height / window_height);
                set_state(cell_x, cell_y, grid_width, grid_height, 1);
            }
            else if(glfwGetKey(window, GLFW_KEY_BACKSPACE) ==  GLFW_PRESS){
                int cell_x = static_cast<int>(mouse_x * grid_width / window_width);
                int cell_y = static_cast<int>(mouse_y * grid_height / window_height);
                set_state(cell_x, cell_y, grid_width, grid_height, 0);
            }
            if(running){
                gol();
            }
            
            break;
        case 2:
            if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) ==  GLFW_PRESS){
                int cell_x = static_cast<int>(mouse_x * grid_width / window_width);
                int cell_y = static_cast<int>(mouse_y * grid_height / window_height);
                set_state(cell_x, cell_y, grid_width, grid_height, 2);
            }
            else if(glfwGetKey(window, GLFW_KEY_BACKSPACE) ==  GLFW_PRESS){
                int cell_x = static_cast<int>(mouse_x * grid_width / window_width);
                int cell_y = static_cast<int>(mouse_y * grid_height / window_height);
                set_state(cell_x, cell_y, grid_width, grid_height, 0);
            }
            if(running){
                fill();
            }
            break;
        case 3:
            if(glfwGetKey(window, GLFW_KEY_1) ==  GLFW_PRESS){
                int cell_x = static_cast<int>(mouse_x * grid_width / window_width);
                int cell_y = static_cast<int>(mouse_y * grid_height / window_height);
                set_state(cell_x, cell_y, grid_width, grid_height, 1);
            }
            else if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){
                int cell_x = static_cast<int>(mouse_x * grid_width / window_width);
                int cell_y = static_cast<int>(mouse_y * grid_height / window_height);
                set_state(cell_x, cell_y, grid_width, grid_height, 2);
            }
            else if(glfwGetKey(window, GLFW_KEY_BACKSPACE) ==  GLFW_PRESS){
                int cell_x = static_cast<int>(mouse_x * grid_width / window_width);
                int cell_y = static_cast<int>(mouse_y * grid_height / window_height);
                set_state(cell_x, cell_y, grid_width, grid_height, 0);
            }
            if(running){
                gol_battle();
            }
        default:
            break;
    }

    
    
}

void Simulation::gol(){
    std::vector<uint16_t> new_data = data;

    for(int x = 0; x < grid_width; x++){
        for(int y = 0; y < grid_height; y++){
            int neighbours = count_live_neighbours(x, y);
            int current_pos = data[y * grid_width + x];

            if(current_pos == 1){
                if(neighbours < 2 || neighbours > 3){
                    new_data[y * grid_width + x] = 0;
                }
            } 
            else{
                if(neighbours == 3){ //change to 1 for fun
                    new_data[y * grid_width + x] = 1;
                }
            }
        }
    }

    data = new_data;
}

void Simulation::fill(){
    std::vector<uint16_t> new_data = data;

    for(int x = 0; x < grid_width; x++){
        for(int y = 0; y < grid_height; y++){
            int neighbours = count_live_neighbours(x, y);
            int current_pos = data[y * grid_width + x];

            if(current_pos == 1){
                if(neighbours < 2 || neighbours > 3){
                    new_data[y * grid_width + x] = 0;
                }
            } 
            else{
                if(neighbours == 1){ //change to 1 for fun
                    new_data[y * grid_width + x] = 2;
                }
            }
        }
    }

    data = new_data;
}

void Simulation::gol_battle(){
    std::vector<uint16_t> new_data = data;
    for(int x = 0; x < grid_width; x++){
        for(int y = 0; y < grid_height; y++){
            int neighbours = count_live_neighbours(x, y);
            int current_type = data[y * grid_width + x];
            int green_count = 0;
            int red_count = 0;

            for(int delta_y = -1; delta_y <= 1; delta_y++){
                for(int delta_x = -1; delta_x <= 1; delta_x++){
                    if(delta_x == 0 && delta_y == 0){
                        continue;
                    }

                    int neighbor_x = (x + delta_x + grid_width) % grid_width;
                    int neighbor_y = (y + delta_y + grid_height) % grid_height;

                    int neighbor_value = get_state(neighbor_x, neighbor_y, grid_width, grid_height);
                    if(neighbor_value == 1){
                        green_count++;
                    }
                    else if(neighbor_value == 2){
                        red_count++;
                    }
                }
            }

            int pos = y * grid_width + x;

            if(current_type){
                if(neighbours < 2 || neighbours > 3){
                    new_data[pos] = 0;
                }
            } 
            else{
                if(neighbours == 3 || (neighbours == 4 && rand() % 4 == 0)){
                    if(green_count > red_count){
                        new_data[pos] = 1;
                    }
                    else if(red_count > green_count){
                        new_data[pos] = 2;
                    }
                    else{
                        new_data[pos] = (rand() % 2) + 1;
                    }
                }
            }
        }
    }

    data = new_data;
}

int Simulation::count_live_neighbours(int x, int y){
    int neighbours = 0;
    for(int delta_y = -1; delta_y <= 1; delta_y++){
        for(int delta_x = -1; delta_x <= 1; delta_x++){
            if(delta_x == 0 && delta_y == 0) continue;

            int nx = (x + delta_x + grid_width) % grid_width;
            int ny = (y + delta_y + grid_height) % grid_height;

            if(data[ny * grid_width + nx]){
                neighbours ++;
            }
        }
    }
    return neighbours;
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
