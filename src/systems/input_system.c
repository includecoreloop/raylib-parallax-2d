#include "input_system.h"
#include "../core/input_bridge.h"
#include "../components/velocity.h"
#include "../components/vehicle.h"
#include "../components/space_ship.h"
#include "../game/scene.h"
#include <math.h>

void input_system_update(void) {
    if (input_bridge.toggle_scene_type) {
        scene_type = scene_type == 1 ? 2 : 1;

        scene_destroy();
        scene_init();

        input_bridge_consume_action(&input_bridge.toggle_scene_type);
        return;
    }

    if (!HAS_COMPONENT(velocity, vehicle_entity)) return;

    Velocity *v = GET_COMPONENT(velocity, vehicle_entity);
    v->direction.x = 0.0f;
    v->direction.y = 0.0f;

    float speed = 0.0f;

    if (HAS_COMPONENT(vehicle, vehicle_entity)) {
        Vehicle *ve = GET_COMPONENT(vehicle, vehicle_entity);
        speed = ve->speed;

        if (input_bridge.move_left) v->direction.x -= 1.0f;
        if (input_bridge.move_right) v->direction.x += 1.0f;

        if (v->direction.x != 0.0f) {
            ve->direction.x = v->direction.x;
            ve->direction.y = 0.0f;
        }
    } else if (HAS_COMPONENT(space_ship, vehicle_entity)) {
        SpaceShip *sp = GET_COMPONENT(space_ship, vehicle_entity);
        speed = sp->speed;

        if (input_bridge.move_up) v->direction.y -= 1.0f;
        if (input_bridge.move_down) v->direction.y += 1.0f;
        if (input_bridge.move_left) v->direction.x -= 1.0f;
        if (input_bridge.move_right) v->direction.x += 1.0f;
    }

    const float mag = sqrtf(v->direction.x * v->direction.x + v->direction.y * v->direction.y);
    const bool is_moving = mag > 0.0f;

    if (is_moving) {
        v->direction.x /= mag;
        v->direction.y /= mag;
        v->speed = speed;

        if (HAS_COMPONENT(space_ship, vehicle_entity)) {
            SpaceShip *sp = GET_COMPONENT(space_ship, vehicle_entity);
            sp->direction.x = v->direction.x;
            sp->direction.y = v->direction.y;
        }
    } else {
        v->speed = 0.0f;
    }
}
