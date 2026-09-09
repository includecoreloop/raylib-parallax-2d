#pragma once

#include "../ecs/ecs.h"
#include "raylib.h"

extern Entity vehicle_entity;
extern Camera2D game_camera;
extern uint8_t scene_type;

void scene_init(void);
void scene_destroy(void);