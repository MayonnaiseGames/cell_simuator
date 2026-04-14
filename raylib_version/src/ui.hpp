#pragma once

#include <raylib.h>

class Button{
    public:
        Button(Vector2 position, float width, float height, const char* text){
            rec = {
                position.x,
                position.y,
                width,
                height
            };

            txt = text;
        };

        void draw();

        bool is_pressed();

    private:
        const char* txt;
        Rectangle rec;

};