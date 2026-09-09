#include "block_prefab.h"

#include "../../components/parallax_layer.h"
#include "../../components/transform.h"
#include "../../components/render.h"

Entity block_prefab_create(const Vec2 position, const float scroll_factor, const Size2D building_size,
                           const uint32_t rgba) {
    const Entity building_entity = create_entity();

    const ParallaxLayer parallax_layer_component = {
        .scroll_factor = scroll_factor,
    };

    ADD_COMPONENT(parallax_layer, building_entity, parallax_layer_component);

    const Transform2D building_transform = {
        .position = position,
        .scale = {.x = 1.0f, .y = 1.0f},
        .rotation = 0.0f,
    };

    ADD_COMPONENT(transform, building_entity, building_transform);

    const Size2D building_size_component = building_size;

    ADD_COMPONENT(size, building_entity, building_size_component);

    const Render building_render = {.rgba = rgba};

    ADD_COMPONENT(render, building_entity, building_render);

    return building_entity;
}

void block_prefab_destroy(const Entity entity) {
    REMOVE_COMPONENT(transform, entity);
    REMOVE_COMPONENT(render, entity);
    REMOVE_COMPONENT(size, entity);
    REMOVE_COMPONENT(parallax_layer, entity);
    destroy_entity(entity);
}
