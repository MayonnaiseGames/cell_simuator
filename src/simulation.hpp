#pragma once

//External
#include <vector>
#include <iostream>
#include <inttypes.h>
#include <random>
#include <glfw3.h>

//Internal
#include "settings.hpp"


class Simulation{
    public:
        Simulation(int Window_width, int Window_height);
        //~Simulation();
        void update(GLFWwindow* window, int Grid_width, int Grid_height);
        

        //Grid functions
        void fill_random(int width, int height, int type);
        void clear(int width, int height, int type);
        int get_state(int x, int y, int width, int height);
        void set_state(int x, int y, int width, int height, int value);

        std::vector<uint16_t> data;
        bool running = true;
        
    private:
        void gol();
        int count_live_neighbours(int x, int y);
        int window_width, window_height;
        int grid_width, grid_height;
        double mouse_x, mouse_y;
};
