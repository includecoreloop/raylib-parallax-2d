#pragma once

#include "../ecs/ecs.h"
#include "../core/math.h"

typedef struct {
    float speed;
    Vec2 direction;
} SpaceShip;

COMPONENT_DEFINE(SpaceShip, space_ship);
