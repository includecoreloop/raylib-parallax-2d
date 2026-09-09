#pragma once

#include "../ecs/ecs.h"

typedef struct {
    float scroll_factor;
} ParallaxLayer;

COMPONENT_DEFINE(ParallaxLayer, parallax_layer);