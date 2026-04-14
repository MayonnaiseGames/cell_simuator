#include <vector>
#include <utility>
#include "game_of_life.hpp"
#include <raylib.h>
#include <iostream>

void Gol::start(){
    grid.fill_random();
}

void Gol::draw()
{
    grid.draw();
    if(is_running == false){
        DrawText("Paused\nPress SPACE to unpause\nPress C to clear screen\nPress P to populate random\nDraw to turn on cells\nENTER to turn off cells\nPress ESCAPE to return to main menu", 10, 10, 30, WHITE);
    }
}

void Gol::set_cell_value(int row, int column, int value){
    grid.set_value(row, column, value);
}

int Gol::count_live_neighbors(int row, int column){
    int live_neighbors = 0;

    std::vector<std::pair<int, int>> neighbor_offsets = {
        {-1, 0}, //above
        {1, 0}, //below
        {0, -1}, //left
        {0, 1}, //right
        {-1, -1}, //up left
        {-1, 1}, //up right
        {1, -1}, // down left
        {1, 1} //down right
    };

    for(const auto &offset : neighbor_offsets){
        int neighbor_row = (row + offset.first + grid.get_rows()) % grid.get_rows();
        int neighbor_column = (column + offset.second + grid.get_columns()) % grid.get_columns();
        live_neighbors += grid.get_state(neighbor_row, neighbor_column);
    }

    return live_neighbors;
}

void Gol::update(){
    if(is_running){
        for(int row = 0; row < grid.get_rows(); row++){
            for(int column = 0; column < grid.get_columns(); column++){
                int live_neighbors = count_live_neighbors(row, column);
                int cell_value = grid.get_state(row, column);

                if(cell_value){
                    if(live_neighbors > 3 || live_neighbors < 2){ //2
                        temp_grid.set_value(row, column, 0);
                    }
                    else{
                        temp_grid.set_value(row, column, 1);
                    }
                }
                else{
                    if(live_neighbors == 3){
                        temp_grid.set_value(row, column, 1);
                    }
                    else{
                        temp_grid.set_value(row, column, 0);
                    }
                }
            }
        }
        grid = temp_grid;
    }
    
}

void Gol::input(){
    if(IsKeyReleased(KEY_SPACE)){
        is_running = !is_running;
    }
    else if(IsKeyReleased(KEY_C)){
        grid.clear();
    }
    else if(IsKeyReleased(KEY_P)){
        grid.fill_random();
    }
    else if((IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !grid.get_state(grid.get_cell(GetMousePosition()).y, grid.get_cell(GetMousePosition()).x)) || IsKeyReleased(KEY_ENTER)){
        if(!grid.get_state(grid.get_cell(GetMousePosition()).y, grid.get_cell(GetMousePosition()).x)){
            grid.set_value(grid.get_cell(GetMousePosition()).y, grid.get_cell(GetMousePosition()).x, 1);
        }
        else{
            grid.set_value(grid.get_cell(GetMousePosition()).y, grid.get_cell(GetMousePosition()).x, 0);
        }
        
    }
}