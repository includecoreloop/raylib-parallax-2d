#include "camera_system.h"
#include "../../game/scene.h"
#include "../../components/transform.h"
#include "../../ecs/ecs.h"
#include "../../core/config.h"
#include "../../core/math.h"

void camera_system_update(void) {
    if (!HAS_COMPONENT(transform, vehicle_entity)) return;

    const Transform2D *t = GET_COMPONENT(transform, vehicle_entity);

    game_camera.target.x = t->position.x;

    const float min_camera_y = scene_type == 1 ? SCREEN_CENTER_Y : SCREEN_CENTER_Y - 800.0f;
    const float max_camera_y = scene_type == 1 ? SCREEN_CENTER_Y : SCREEN_CENTER_Y + 800.0f;

    game_camera.target.y = math_clamp(t->position.y, min_camera_y, max_camera_y);
}
