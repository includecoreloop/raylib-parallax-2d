#include "raylib.h"
#include "../../core/input_bridge.h"

InputBridge input_bridge = {0};

void input_system_poll(void) {
    input_bridge.move_up = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP);
    input_bridge.move_down = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN);
    input_bridge.move_left = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT);
    input_bridge.move_right = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);

    input_bridge.toggle_scene_type = IsKeyPressed(KEY_C);
}
