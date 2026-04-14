#include "ui.hpp"

bool Button::is_pressed(){
    if(CheckCollisionPointRec(GetMousePosition(), rec) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
        return true;
    }
    return false;
}

void Button::draw(){
    DrawRectangleLinesEx(rec, 10, {100, 100, 100, 255});
    DrawText(txt, rec.x + 20, rec.y + 20, 50, WHITE);
}