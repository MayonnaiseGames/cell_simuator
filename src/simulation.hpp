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
        Simulation(int window_width, int window_height);
        //~Simulation();
        void update(GLFWwindow* window, int grid_width, int grid_height);
        

        //Grid functions
        void fill_random(int width, int height, int type);
        void clear(int width, int height, int type);
        int get_state(int x, int y, int width, int height);
        void set_state(int x, int y, int width, int height, int value);

        std::vector<uint16_t> data;
        
    private:
        void gol();
        int window_width, window_height;
        double mouse_x, mouse_y;
};
