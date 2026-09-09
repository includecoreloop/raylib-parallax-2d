#include "space_ship_prefab.h"

#include "../../components/parallax_layer.h"
#include "../../components/transform.h"
#include "../../components/render.h"
#include "../../components/velocity.h"
#include "../../components/space_ship.h"
#include "../../components/size.h"

#include "../../core/config.h"

Entity space_ship_prefab_create(void) {
    const Entity space_ship_entity = create_entity();

    const Transform2D space_ship_transform = {
        .position = {.x = SCREEN_CENTER_X, .y = SCREEN_CENTER_Y + 20},
        .scale = {.x = 1.0f, .y = 1.0f},
        .rotation = 0.0f
    };

    ADD_COMPONENT(transform, space_ship_entity, space_ship_transform);

    const Render space_ship_render = {
        .rgba = 0x0000FFFF
    };

    ADD_COMPONENT(render, space_ship_entity, space_ship_render);

    const Size2D space_ship_size = {
        .width = 80.0f,
        .height = 160.0f,
    };

    ADD_COMPONENT(size, space_ship_entity, space_ship_size);

    const Velocity space_ship_velocity = {
        .direction = {.x = 0.0f, .y = 0.0f},
        .speed = 0.0f
    };

    ADD_COMPONENT(velocity, space_ship_entity, space_ship_velocity);

    const SpaceShip space_ship_component = {
        .speed = 600.0f,
        .direction = 1.0f,
    };

    ADD_COMPONENT(space_ship, space_ship_entity, space_ship_component);

    const ParallaxLayer space_ship_parallax = {
        .scroll_factor = 1.0f,
    };

    ADD_COMPONENT(parallax_layer, space_ship_entity, space_ship_parallax);

    return space_ship_entity;
}

void space_ship_prefab_destroy(const Entity entity) {
    REMOVE_COMPONENT(transform, entity);
    REMOVE_COMPONENT(render, entity);
    REMOVE_COMPONENT(size, entity);
    REMOVE_COMPONENT(parallax_layer, entity);
    REMOVE_COMPONENT(space_ship, entity);
    REMOVE_COMPONENT(velocity, entity);
    destroy_entity(entity);
}
