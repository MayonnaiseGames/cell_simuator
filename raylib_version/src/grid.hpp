#pragma once
#include <vector>
#include <raylib.h>

class Grid{
    public:
        Grid(int width, int height, int cell_size)
        : rows(height/cell_size), columns(width/cell_size), cell_size(cell_size), cells(rows, std::vector<int>(columns, 0)) {};

        void draw();
        void set_value(int row, int column, int value);
        int get_state(int row, int column);
        bool cell_in_bound(int row, int column);
        int get_rows(){return rows;}
        int get_columns(){return columns;}
        Vector2 get_cell(Vector2 position);
        void fill_random();
        void clear();


    private:
        int rows;
        int columns;
        int cell_size;
        std::vector<std::vector<int>> cells;
};