#include "raylib.h"

#include "../core/config.h"

#include "../systems/raylib/render_system_vector.h"
#include "../systems/movement_system.h"
#include "../systems/raylib/input_system.h"
#include "../systems/input_system.h"
#include "../systems/raylib/camera_system.h"
#include "scene.h"

static void tick(const double dt) {
    input_system_update();
    movement_system_update(dt);
    camera_system_update();
}

int main(void) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(TARGET_FPS);

    scene_init();

    double previous = GetTime();
    double accumulator = 0.0;

    while (!WindowShouldClose()) {
        const double current = GetTime();
        double frameTime = current - previous;

        if (frameTime > 0.25)
            frameTime = 0.25;

        previous = current;
        accumulator += frameTime;

        input_system_poll();

        while (accumulator >= FIXED_DT) {
            tick(FIXED_DT);
            accumulator -= FIXED_DT;
        }

        render_system_vector_update();
    }

    CloseWindow();

    return 0;
}
