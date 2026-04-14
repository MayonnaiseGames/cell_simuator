#include <raylib.h>
#include "grid.hpp"

void Grid::draw(){
    for(int row = 0; row < rows; row++){
        for(int column = 0; column < columns; column++){
            Color colour ;
            switch (cells[row][column]){
                case 0:
                    colour = {55, 55, 55, 255};
                    break;
                case 1:
                    colour = {100, 100, 100, 255};
                    break;
                case 2:
                    colour = {237, 221, 119, 255};
                    break;
                case 3:
                    colour = {0, 0, 200, 255};
                    break;
                case 4:
                    colour = {200, 50, 200, 255};
                    break;
                case 5:
                    colour = {255, 255, 255, 255};
                    break;
            }
            DrawRectangle(column * cell_size, row * cell_size, cell_size  , cell_size , colour);
        }
    }
}

void Grid::set_value(int row, int column, int value){
    if(cell_in_bound(row, column)){
        cells[row][column] = value;
    }
}

int Grid::get_state(int row, int column){
    if(cell_in_bound(row, column)){
        return cells[row][column];
    }
    return 0;
}

bool Grid::cell_in_bound(int row, int column){
    if(row >= 0 && row < rows && column >= 0 && column < columns){
        return true;
    }
    return false;
}

Vector2 Grid::get_cell(Vector2 position){
    Vector2 cell_position;
    cell_position.x = (int)position.x/cell_size;
    cell_position.y = (int)position.y/cell_size;
    return cell_position;
}

void Grid::fill_random()
{
    for(int row = 0; row < rows; row++){
        for(int column = 0; column < columns; column++){
            int random_value = GetRandomValue(0, 4);
            cells[row][column] = (random_value == 4) ? 1 : 0;
        }
    }
}

void Grid::clear(){
    for(int row = 0; row < rows; row++){
        for(int column = 0; column < columns; column++){
            cells[row][column] = 0;
        }
    }
}
