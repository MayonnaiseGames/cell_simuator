#include "particle_simulation.hpp"
#include "vector"
#include <iostream>

void Particle_simulation::start(){
    grid.clear();
}

void Particle_simulation::update(){
    float mouseWheel = GetMouseWheelMove();

    if (mouseWheel != 0) {
        brush_size += (int)mouseWheel;

        if (brush_size < 1) brush_size = 1;
        if (brush_size > 50) brush_size = 50;
    }
    
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        Vector2 mouse_pos = GetMousePosition();
        if(selected_item > 1){
            for(int i =0; i < brush_size; i++){
                grid.set_value(grid.get_cell(mouse_pos).y + GetRandomValue(-brush_size, brush_size), grid.get_cell(mouse_pos).x + GetRandomValue(-brush_size, brush_size), selected_item);
            }
        }
        else{
            grid.set_value(grid.get_cell(mouse_pos).y, grid.get_cell(mouse_pos).x, selected_item);
            grid.set_value(grid.get_cell(mouse_pos).y + 1, grid.get_cell(mouse_pos).x + 1 , selected_item);
            grid.set_value(grid.get_cell(mouse_pos).y, grid.get_cell(mouse_pos).x + 1, selected_item);
            grid.set_value(grid.get_cell(mouse_pos).y + 1, grid.get_cell(mouse_pos).x + 1 , selected_item);
            grid.set_value(grid.get_cell(mouse_pos).y + 1, grid.get_cell(mouse_pos).x, selected_item);
            grid.set_value(grid.get_cell(mouse_pos).y + 1, grid.get_cell(mouse_pos).x + 1 , selected_item);
            
        }
        
    }
    if(IsKeyPressed(KEY_S)){
        selected_item = 2;
    }
    else if(IsKeyPressed(KEY_W)){
        selected_item = 3;
    }
    else if(IsKeyPressed(KEY_B)){
        selected_item = 1;
    }
    else if(IsKeyPressed(KEY_D)){
        selected_item = 0;
    }
    else if(IsKeyPressed(KEY_A)){
        selected_item = 4;
    }
    else if (IsKeyPressed(KEY_Z)){
        selected_item = 5;
    }
    if(IsKeyReleased(KEY_SPACE)){
        is_running = !is_running;
    }
    if(IsKeyPressed(KEY_C)){
        grid.clear();
    }
    
    if(is_running){
        for(int row = grid.get_rows() - 1; row >= 0; row--){
            for(int column = grid.get_columns() - 1; column >= 0; column--){
                if(grid.get_state(row, column) == 1){
                    grid.set_value(row, column, 1);
                }
                if(grid.get_state(row, column) == 2){
                    Vector2 direction = return_first_neighbor_powder(row, column);
                    grid.set_value(row, column, 0);
                    grid.set_value(row + direction.x, column + direction.y, 2);
                }
                if(grid.get_state(row, column) == 3){
                    Vector2 direction = return_first_neighbor_liquid(row, column);
                    grid.set_value(row, column, 0);
                    grid.set_value(row + direction.x, column + direction.y, 3);
                }
                if(grid.get_state(row, column) == 4){
                    Vector2 direction = return_first_neighbor_acid(row, column);
                    grid.set_value(row, column, 0);
                    grid.set_value(row + direction.x, column + direction.y, 4);
                }
                if(grid.get_state(row, column) == 5){
                    Vector2 direction = return_first_neighbor_powder(row, column);
                    grid.set_value(row, column, 0);
                    grid.set_value(row + direction.x, column + direction.y, 5);
                }
                
                
            }
        }
    }
}

void Particle_simulation::draw(){
    grid.draw();
    if(!is_running){
        DrawText("Paused\nPress SPACE to unpause\nPress C to clear screen\nPress W for water\nPress S for sand\nPress B for brick\nPress D to destroy\nPress A for acid\nPress Z for sugar\nSCROLL to change brush size\nPress ESCAPE to return to main menu", 10, 10, 30, WHITE);
    }
}

Vector2 Particle_simulation::return_first_neighbor_powder(int row, int column){
    if(row < grid.get_rows() - 1 && (grid.get_state(row + 1, column) == 0) || (grid.get_state(row + 1, column) == 3)){
        return {1, 0};
    }

    bool checkRightFirst = GetRandomValue(0,1);

    if(checkRightFirst){
        if(row < grid.get_rows()-1 && column < grid.get_columns()-1 && grid.get_state(row + 1, column + 1) == 0){
            return {1, 1};
        }
        if(row < grid.get_rows()-1 && column > 0 && grid.get_state(row + 1, column - 1) == 0){
            return {1, -1};
        }
        
    }
    else{
        if(row < grid.get_rows()-1 && column > 0 && grid.get_state(row + 1, column - 1) == 0){
            return {1, -1};
        }
        if(row < grid.get_rows()-1 && column < grid.get_columns()-1 && grid.get_state(row + 1, column + 1) == 0){
            return {1, 1};
        }
        
        
    }

    return {0, 0};
}

Vector2 Particle_simulation::return_first_neighbor_liquid(int row, int column){

    if(row < grid.get_rows() - 1 && grid.get_state(row + 1, column) == 0){
        return {1, 0};
    }

    bool checkRightFirst = GetRandomValue(0, 1);

    if(checkRightFirst){
        if(row < grid.get_rows()-1 && column < grid.get_columns()-1 && grid.get_state(row + 1, column + 1) == 0){
            return {1, 1};
        }
        if(row < grid.get_rows()-1 && column > 0 && grid.get_state(row + 1, column - 1) == 0){
            return {1, -1};
        }
        if(column < grid.get_columns()-1 && grid.get_state(row, column + 1) == 0){
            return {0, 1};
        }
        if(column > 0 && grid.get_state(row, column - 1) == 0){
            return {0, -1};
        }
    }
    else{
        if(row < grid.get_rows()-1 && column > 0 && grid.get_state(row + 1, column - 1) == 0){
            return {1, -1};
        }
        if(row < grid.get_rows()-1 && column < grid.get_columns()-1 && grid.get_state(row + 1, column + 1) == 0){
            return {1, 1};
        }
        if(column > 0 && grid.get_state(row, column - 1) == 0){
            return {0, -1};
        }
        if(column < grid.get_columns()-1 && grid.get_state(row, column + 1) == 0){
            return {0, 1};
        }
    }

    return {0, 0};
}

Vector2 Particle_simulation::return_first_neighbor_acid(int row, int column){

    if(row < grid.get_rows() - 1 && grid.get_state(row + 1, column) != 4){
        return {1, 0};
    }

    bool checkRightFirst = GetRandomValue(0,1);

    if(checkRightFirst){
        if(row < grid.get_rows()-1 && column < grid.get_columns()-1 && grid.get_state(row + 1, column + 1) != 4){
            return {1, 1};
        }
        if(row < grid.get_rows()-1 && column > 0 && grid.get_state(row + 1, column - 1) != 4){
            return {1, -1};
        }
        if(column < grid.get_columns()-1 && grid.get_state(row, column + 1) != 4){
            return {0, 1};
        }
        if(column > 0 && grid.get_state(row, column - 1) != 4){
            return {0, -1};
        }
    }
    else{
        if(row < grid.get_rows()-1 && column > 0 && grid.get_state(row + 1, column - 1) != 4){
            return {1, -1};
        }
        if(row < grid.get_rows()-1 && column < grid.get_columns()-1 && grid.get_state(row + 1, column + 1) != 4){
            return {1, 1};
        }
        if(column > 0 && grid.get_state(row, column - 1) != 4){
            return {0, -1};
        }
        if(column < grid.get_columns()-1 && grid.get_state(row, column + 1) != 4){
            return {0, 1};
        }
    }

    return {0, 0};
}