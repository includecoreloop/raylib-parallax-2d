#pragma once

#include "../../ecs/ecs.h"
#include "../../core/math.h"
#include "../../components/size.h"

Entity block_prefab_create(Vec2 position, float scroll_factor, Size2D building_size, uint32_t rgba);

void block_prefab_destroy(Entity entity);
