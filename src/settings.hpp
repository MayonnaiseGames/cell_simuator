#pragma once

void save_settings();
void load_settings();

struct Settings{
    bool wireframe;
    bool show_debug;
    bool show_console;
    int game_mode;
};

extern Settings settings;