#include <raylib.h>
#include "game_of_life.hpp"
#include "ui.hpp"
#include "particle_simulation.hpp"
#include <iostream>

int main(){
    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 720;
    const int FPS = 60;
    const int GOL_CELL_SIZE = 10;
    const int PARTICLE_CELL_SIZE = 4;
    bool game_running = true;
    int game_state =0;

    Color GREY = {55, 55, 55, 255};

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Cellular Automata Sandbox");
    SetTargetFPS(FPS);
    //ToggleFullscreen();
    Gol gol{WINDOW_WIDTH, WINDOW_HEIGHT, GOL_CELL_SIZE};
    Particle_simulation particle_simulation{WINDOW_WIDTH, WINDOW_HEIGHT, PARTICLE_CELL_SIZE};
    Button gol_button{{10, 125}, 200, 100, "GOL"};
    Button particle_button{{10, 275}, 500, 100, "Particle simulation"};
    Button quit_button{{10, 425}, 200, 100, "Quit"};
    //simulation
    gol.start();
    particle_simulation.start();
    while(game_running){
        if(IsKeyPressed(KEY_F11)){
            ToggleFullscreen();
        }
        else if(IsKeyReleased(KEY_ESCAPE)){
            game_state = 0;
        }

        BeginDrawing();
        ClearBackground(GREY);
        
        switch(game_state){
            case 0:
                if(gol_button.is_pressed()){
                    game_state = 1;
                }
                else if(particle_button.is_pressed()){
                    game_state = 2;
                }
                else if(quit_button.is_pressed()){
                    game_running = false;
                }
                gol_button.draw();
                particle_button.draw();
                quit_button.draw();
                DrawText("Cellular Automata sandbox", 10, 10, 75, WHITE);
                break;
            case 1:
                gol.input();
                gol.update();
                gol.draw();
                break;
            case 2:
                particle_simulation.update();
                particle_simulation.draw();
                break;

            
        }
        DrawFPS(WINDOW_WIDTH - 30, WINDOW_HEIGHT - 20);
        EndDrawing();
        if(WindowShouldClose() && !IsKeyDown(KEY_ESCAPE)){
            game_running = false;
        }

    }
    CloseWindow();
    return 0;
}
