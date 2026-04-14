#pragma once

#include "grid.hpp"

class Particle_simulation{
    public:
        Particle_simulation(int width, int height, int cell_size)
        : grid(width, height, cell_size), temp_grid(width, height, cell_size) {};
        void start();
        void update();
        void draw();
        Vector2 return_first_neighbor_powder(int row, int column);
        Vector2 return_first_neighbor_liquid(int row, int column);
        Vector2 return_first_neighbor_acid(int row, int column);
    
    private:
        Grid grid;
        Grid temp_grid;
        int selected_item = 2;
        bool is_running = false;
        int brush_size = 1;
};