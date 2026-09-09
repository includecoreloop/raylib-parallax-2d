#pragma once

#include <stdbool.h>

typedef struct {
    bool move_up;
    bool move_down;
    bool move_left;
    bool move_right;
    bool toggle_scene_type;
} InputBridge;

extern InputBridge input_bridge;

static inline void input_bridge_consume_action(bool *action) {
    *action = false;
}