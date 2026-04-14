#pragma once

#include "grid.hpp"
#include <vector>
#include <utility>

class Gol{
    public:
        Gol(int width, int height, int cell_size)
        : grid(width, height, cell_size), temp_grid(width, height, cell_size) {};

        void start();
        void draw();
        void set_cell_value(int row, int column, int value);
        int count_live_neighbors(int row, int column);
        void update();
        void input();

    private:
        Grid grid;
        Grid temp_grid;
        bool is_running = false;  
};