#include "render_system_vector.h"

#include <math.h>

#include "raylib.h"
#include "rlgl.h"

#include "../../core/config.h"

#include "../../components/transform.h"
#include "../../components/render.h"
#include "../../components/size.h"
#include "../../components/parallax_layer.h"
#include "../../components/vehicle.h"
#include "../../components/space_ship.h"
#include "../../game/scene.h"

static const int UI_FONT_SIZE = 40;
static const uint32_t PARALLAX_SKY_COLOR = 0xFBDEBFFF;
static const float VERTICAL_DAMPENER = 0.5f;

static void draw_rounded_vector_rectangle(const Vector2 center_pos, const float width, const float height,
                                          const float rotation_deg, const float corner_radius,
                                          const Color fill_color) {
    const Rectangle rec = {
        .x = -width * 0.5f,
        .y = -height * 0.5f,
        .width = width,
        .height = height
    };

    const float min_dim = width < height ? width : height;
    float roundness = min_dim > 0.0f ? corner_radius * 2.0f / min_dim : 0.0f;

    if (roundness > 1.0f) {
        roundness = 1.0f;
    }

    if (fabsf(rotation_deg) > 0.001f) {
        rlPushMatrix();

        rlTranslatef(center_pos.x, center_pos.y, 0.0f);
        rlRotatef(rotation_deg, 0.0f, 0.0f, 1.0f);

        DrawRectangleRounded(rec, roundness, 8, fill_color);

        rlPopMatrix();
    } else {
        const Rectangle top_left_rec = {
            .x = center_pos.x - width * 0.5f,
            .y = center_pos.y - height * 0.5f,
            .width = width,
            .height = height
        };

        DrawRectangleRounded(top_left_rec, roundness, 8, fill_color);
    }
}

static void draw_vector_space_ship(const Vector2 center_pos, const float body_width, const float body_height,
                                   const Color ship_color, const Vec2 facing_dir) {
    const float half_w = body_width * 0.5f;
    const float half_h = body_height * 0.5f;

    float rotation_deg = 0.0f;
    if (facing_dir.x != 0.0f || facing_dir.y != 0.0f) {
        const float angle_rad = atan2f(facing_dir.y, facing_dir.x);
        rotation_deg = angle_rad * (180.0f / 3.14159265358979323846f) + 90.0f;
    }

    rlPushMatrix();
    rlTranslatef(center_pos.x, center_pos.y, 0.0f);
    rlRotatef(rotation_deg, 0.0f, 0.0f, 1.0f);

    const Rectangle body_rec = {
        .x = -half_w,
        .y = -half_h,
        .width = body_width,
        .height = body_height
    };

    DrawRectangleRec(body_rec, ship_color);

    const Vector2 nose_tip = {.x = 0.0f, .y = -half_h - (body_height * 0.5f)};
    const Vector2 nose_left = {.x = -half_w, .y = -half_h};
    const Vector2 nose_right = {.x = half_w, .y = -half_h};

    DrawTriangle(nose_tip, nose_left, nose_right, ship_color);

    const Vector2 left_wing_tip = {.x = -half_w - (body_width * 0.5f), .y = half_h};
    const Vector2 left_wing_top = {.x = -half_w, .y = -half_h * 0.2f};
    const Vector2 left_wing_base = {.x = -half_w, .y = half_h};

    DrawTriangle(left_wing_top, left_wing_tip, left_wing_base, ship_color);

    const Vector2 right_wing_tip = {.x = half_w + (body_width * 0.5f), .y = half_h};
    const Vector2 right_wing_top = {.x = half_w, .y = -half_h * 0.2f};
    const Vector2 right_wing_base = {.x = half_w, .y = half_h};

    DrawTriangle(right_wing_top, right_wing_base, right_wing_tip, ship_color);

    rlPopMatrix();
}

static void render_ui(void) {
    const char *controls_text = "W A S D : MOVE";
    const char *scene_type_text = "C : TOGGLE EXAMPLES";

    DrawText(controls_text, 30, SCREEN_HEIGHT - 60 - UI_FONT_SIZE, UI_FONT_SIZE, GREEN);
    DrawText(scene_type_text, 30, SCREEN_HEIGHT - 20 - UI_FONT_SIZE, UI_FONT_SIZE, GREEN);
}

static void draw_vector_vehicle(const Vector2 center_pos, const float body_width, const float body_height,
                                const Color body_color, const Vec2 facing_dir) {
    const float dir = facing_dir.x < 0.0f ? -1.0f : 1.0f;

    const float wedge_height = body_height * 0.16f;
    const float cabin_height = body_height * 0.91f;

    const float half_w = body_width * 0.5f;
    const float half_h = body_height * 0.5f;

    rlPushMatrix();
    rlTranslatef(center_pos.x, center_pos.y, 0.0f);

    const Vector2 wedge_p1 = {.x = -half_w * dir, .y = -half_h - wedge_height};
    const Vector2 wedge_p2 = {.x = -half_w * dir, .y = -half_h};
    const Vector2 wedge_p3 = {.x = half_w * dir, .y = -half_h};

    if (dir < 0.0f) {
        DrawTriangle(wedge_p3, wedge_p2, wedge_p1, body_color);
    } else {
        DrawTriangle(wedge_p1, wedge_p2, wedge_p3, body_color);
    }

    const float rear_x = -half_w + body_width * 0.025f;
    const float front_x = half_w - body_width * 0.25f;

    const float slope = wedge_height / body_width;
    const float rear_y = -half_h - wedge_height + (rear_x + half_w) * slope;
    const float front_y = -half_h - wedge_height + (front_x + half_w) * slope;

    const Vector2 roof_peak = {
        .x = body_width * 0.025f * dir, .y = -half_h - wedge_height - cabin_height
    };

    const Vector2 roof_rear = {.x = rear_x * dir, .y = rear_y};
    const Vector2 roof_front = {.x = front_x * dir, .y = front_y};

    if (dir < 0.0f) {
        DrawTriangle(roof_peak, roof_front, roof_rear, BLACK);
    } else {
        DrawTriangle(roof_peak, roof_rear, roof_front, BLACK);
    }

    const Rectangle body_rec = {
        .x = -half_w,
        .y = -half_h,
        .width = body_width,
        .height = body_height
    };

    DrawRectangleRounded(body_rec, 0.15f, 8, body_color);

    const float rear_wheel_radius = body_height * 0.75f;
    const float front_wheel_radius = body_height * 0.667f;

    const Vector2 rear_wheel_pos = {
        .x = (-half_w + body_width * 0.20f) * dir, .y = half_h - body_height * 0.333f
    };

    const Vector2 front_wheel_pos = {
        .x = (half_w - body_width * 0.1875f) * dir, .y = half_h - body_height * 0.25f
    };

    DrawCircleV(rear_wheel_pos, rear_wheel_radius, BLACK);
    DrawCircleV(front_wheel_pos, front_wheel_radius, BLACK);

    rlPopMatrix();
}

static inline Vector2 calculate_parallax_position(const Vec2 world_pos,
                                                  const Vector2 camera_target,
                                                  const float scroll_factor) {
    const float cam_delta_x = camera_target.x - SCREEN_CENTER_X;
    const float cam_delta_y = camera_target.y - SCREEN_CENTER_Y;

    const float parallax_offset_x = cam_delta_x * (1.0f - scroll_factor);
    const float parallax_offset_y = cam_delta_y * (1.0f - scroll_factor) * VERTICAL_DAMPENER;

    return (Vector2){
        .x = world_pos.x + parallax_offset_x,
        .y = world_pos.y + parallax_offset_y
    };
}

typedef struct {
    Entity entity;
    float scroll_factor;
} RenderCommand;

void render_system_vector_update(void) {
    static RenderCommand commands[MAX_ENTITIES];
    uint16_t command_count = 0;

    for (Entity i = 0; i < MAX_ENTITIES; i++) {
        if (HAS_COMPONENT(transform, i) && HAS_COMPONENT(render, i) && HAS_COMPONENT(size, i)) {
            float scroll_factor = 1.0f;

            if (HAS_COMPONENT(parallax_layer, i)) {
                const ParallaxLayer *pl = GET_COMPONENT(parallax_layer, i);
                scroll_factor = pl->scroll_factor;
            }

            commands[command_count++] = (RenderCommand){
                .entity = i,
                .scroll_factor = scroll_factor
            };
        }
    }

    for (int i = 1; i < command_count; ++i) {
        const RenderCommand key = commands[i];
        int j = i - 1;

        while (j >= 0 && commands[j].scroll_factor > key.scroll_factor) {
            commands[j + 1] = commands[j];
            j--;
        }

        commands[j + 1] = key;
    }

    BeginDrawing();
    ClearBackground(GetColor(PARALLAX_SKY_COLOR));

    BeginMode2D(game_camera);

    for (uint16_t idx = 0; idx < command_count; idx++) {
        const Entity i = commands[idx].entity;
        const float scroll_factor = commands[idx].scroll_factor;

        const Transform2D *t = GET_COMPONENT(transform, i);
        const Render *r = GET_COMPONENT(render, i);
        const Size2D *s = GET_COMPONENT(size, i);

        const Vector2 entity_pos = calculate_parallax_position(t->position, game_camera.target, scroll_factor);

        const Color color = GetColor(r->rgba);
        const float width = s->width * t->scale.x;
        const float height = s->height * t->scale.y;

        if (HAS_COMPONENT(vehicle, i)) {
            const Vehicle *ve = GET_COMPONENT(vehicle, i);
            draw_vector_vehicle(entity_pos, width, height, color, ve->direction);
        } else if (HAS_COMPONENT(space_ship, i)) {
            const SpaceShip *sp = GET_COMPONENT(space_ship, i);
            draw_vector_space_ship(entity_pos, width, height, color, sp->direction);
        } else {
            const float corner_radius = (width < height ? width : height) * 0.05f;
            draw_rounded_vector_rectangle(entity_pos, width, height, t->rotation, corner_radius, color);
        }
    }

    EndMode2D();

    if (RENDER_FPS_COUNTER) {
        DrawFPS(10, 10);
    }

    render_ui();

    EndDrawing();
}
