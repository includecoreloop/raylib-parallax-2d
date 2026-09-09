#include "vehicle_prefab.h"

#include "../../components/parallax_layer.h"
#include "../../components/transform.h"
#include "../../components/render.h"
#include "../../components/velocity.h"
#include "../../components/vehicle.h"
#include "../../components/size.h"

#include "../../core/config.h"

Entity vehicle_prefab_create(void) {
    const Entity vehicle_entity = create_entity();

    const Transform2D vehicle_transform = {
        .position = {.x = SCREEN_CENTER_X, .y = SCREEN_CENTER_Y + 20},
        .scale = {.x = 1.0f, .y = 1.0f},
        .rotation = 0.0f
    };

    ADD_COMPONENT(transform, vehicle_entity, vehicle_transform);

    const Render vehicle_render = {
        .rgba = 0x0000FFFF
    };

    ADD_COMPONENT(render, vehicle_entity, vehicle_render);

    const Size2D vehicle_size = {
        .width = 400.0f,
        .height = 60.0f,
    };

    ADD_COMPONENT(size, vehicle_entity, vehicle_size);

    const Velocity vehicle_velocity = {
        .direction = {.x = 0.0f, .y = 0.0f},
        .speed = 0.0f
    };

    ADD_COMPONENT(velocity, vehicle_entity, vehicle_velocity);

    const Vehicle vehicle_component = {
        .speed = 600.0f,
        .direction = 1.0f,
    };

    ADD_COMPONENT(vehicle, vehicle_entity, vehicle_component);

    const ParallaxLayer vehicle_parallax = {
        .scroll_factor = 1.0f,
    };

    ADD_COMPONENT(parallax_layer, vehicle_entity, vehicle_parallax);

    return vehicle_entity;
}

void vehicle_prefab_destroy(const Entity entity) {
    REMOVE_COMPONENT(transform, entity);
    REMOVE_COMPONENT(render, entity);
    REMOVE_COMPONENT(size, entity);
    REMOVE_COMPONENT(parallax_layer, entity);
    REMOVE_COMPONENT(vehicle, entity);
    REMOVE_COMPONENT(velocity, entity);
    destroy_entity(entity);
}
