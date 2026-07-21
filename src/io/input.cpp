#include "io/input.hpp"
#include <raylib.h>

InputSnapshot poll_input() {
    InputSnapshot input{};
    input.MoveRight    = IsKeyDown(KEY_RIGHT);
    input.MoveLeft     = IsKeyDown(KEY_LEFT);
    input.MoveUp       = IsKeyDown(KEY_UP);
    input.MoveDown     = IsKeyDown(KEY_DOWN);
    input.ShootPressed = IsKeyPressed(KEY_X);
    input.JumpPressed  = IsKeyPressed(KEY_Z);
    input.JumpReleased = IsKeyReleased(KEY_Z);
    input.DashPressed  = IsKeyPressed(KEY_C);
    input.SpellPressed = IsKeyPressed(KEY_V);
    return input;
}
