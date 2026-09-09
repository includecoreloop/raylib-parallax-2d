#pragma once

#include "../ecs/ecs.h"

typedef struct {
    float speed;
    float direction;
} Vehicle;

COMPONENT_DEFINE(Vehicle, vehicle);
