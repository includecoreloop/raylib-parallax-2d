#include "scene.h"

#include "../components/vehicle.h"
#include "../components/transform.h"
#include "../core/config.h"
#include "../core/math.h"

#include "prefabs/vehicle_prefab.h"
#include "prefabs/block_prefab.h"

Entity vehicle_entity = 0;
Camera2D game_camera = {0};
uint8_t scene_type = 1;

static const uint32_t PARALLAX_LAYER_1_COLOR = 0xD0B6ACFF;
static const float PARALLAX_LAYER_1_SCROLL = 0.15f;

static const uint32_t PARALLAX_LAYER_2_COLOR = 0xAD8486FF;
static const float PARALLAX_LAYER_2_SCROLL = 0.35f;

static const uint32_t PARALLAX_LAYER_3_COLOR = 0x7C5265FF;
static const float PARALLAX_LAYER_3_SCROLL = 0.55f;

static const uint32_t PARALLAX_LAYER_4_COLOR = 0x51374DFF;
static const float PARALLAX_LAYER_4_SCROLL = 0.75f;

static const uint32_t PARALLAX_LAYER_5_COLOR = 0x342135FF;
static const float PARALLAX_LAYER_5_SCROLL_BACK = 0.90f;
static const float PARALLAX_LAYER_5_SCROLL_FRONT = 1.30f;

static const uint32_t GROUND_COLOR = 0x2A1828FF;
static const float GROUND_SCROLL = 1.00f;

static Entity spawn_building_block(const float center_x, const float width, const float height, const float y_offset,
                                   const float scroll, const uint32_t color) {
    return block_prefab_create(
        (Vec2){.x = center_x, .y = SCREEN_CENTER_Y - height * 0.5f + y_offset},
        scroll,
        (Size2D){.width = width, .height = height},
        color
    );
}

static void build_ground_plane(void) {
    spawn_building_block(SCREEN_CENTER_X, 10000.0f, 340.0f, 340.0f, GROUND_SCROLL, GROUND_COLOR);
}

static void build_layer_1_blocks(void) {
    spawn_building_block(SCREEN_CENTER_X - 1800.0f, 160.0f, 740.0f, 0.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1620.0f, 130.0f, 560.0f, 0.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1440.0f, 190.0f, 690.0f, 0.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1240.0f, 140.0f, 800.0f, 0.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1040.0f, 180.0f, 610.0f, 0.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 820.0f, 120.0f, 550.0f, 0.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 620.0f, 200.0f, 620.0f, 0.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 420.0f, 150.0f, 820.0f, 0.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 230.0f, 170.0f, 580.0f, 0.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X, 200.0f, 680.0f, 0.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 220.0f, 120.0f, 520.0f, 0.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 410.0f, 180.0f, 750.0f, 0.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 600.0f, 140.0f, 590.0f, 0.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 790.0f, 200.0f, 810.0f, 0.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1000.0f, 150.0f, 640.0f, 0.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1210.0f, 190.0f, 720.0f, 0.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1420.0f, 130.0f, 540.0f, 0.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1630.0f, 180.0f, 780.0f, 0.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1850.0f, 150.0f, 600.0f, 0.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
}

static void build_layer_2_blocks(void) {
    spawn_building_block(SCREEN_CENTER_X - 1900.0f, 150.0f, 440.0f, 0.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1720.0f, 170.0f, 510.0f, 0.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1545.0f, 140.0f, 430.0f, 0.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1360.0f, 180.0f, 490.0f, 0.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1165.0f, 160.0f, 460.0f, 0.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 970.0f, 180.0f, 530.0f, 0.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 785.0f, 140.0f, 420.0f, 0.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 610.0f, 160.0f, 480.0f, 0.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 415.0f, 180.0f, 520.0f, 0.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 235.0f, 140.0f, 460.0f, 0.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 60.0f, 160.0f, 410.0f, 0.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 115.0f, 150.0f, 490.0f, 0.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 295.0f, 170.0f, 450.0f, 0.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 480.0f, 160.0f, 540.0f, 0.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 670.0f, 180.0f, 470.0f, 0.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 855.0f, 150.0f, 420.0f, 0.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1035.0f, 170.0f, 500.0f, 0.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1210.0f, 140.0f, 440.0f, 0.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1390.0f, 180.0f, 520.0f, 0.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1580.0f, 160.0f, 470.0f, 0.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
}

static void build_layer_3_blocks(void) {
    spawn_building_block(SCREEN_CENTER_X - 1880.0f, 160.0f, 352.0f, 0.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1710.0f, 140.0f, 308.0f, 0.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1530.0f, 180.0f, 385.0f, 0.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1360.0f, 130.0f, 286.0f, 0.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1180.0f, 170.0f, 363.0f, 0.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1000.0f, 150.0f, 330.0f, 0.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 810.0f, 190.0f, 396.0f, 0.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 630.0f, 140.0f, 319.0f, 0.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 450.0f, 160.0f, 352.0f, 0.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 280.0f, 140.0f, 308.0f, 0.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 100.0f, 180.0f, 385.0f, 0.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 70.0f, 130.0f, 286.0f, 0.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 250.0f, 170.0f, 363.0f, 0.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 430.0f, 150.0f, 330.0f, 0.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 620.0f, 190.0f, 396.0f, 0.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 800.0f, 140.0f, 319.0f, 0.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 970.0f, 160.0f, 352.0f, 0.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1150.0f, 180.0f, 385.0f, 0.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1320.0f, 130.0f, 286.0f, 0.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1500.0f, 170.0f, 363.0f, 0.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
}

static void build_layer_4_blocks(void) {
    spawn_building_block(SCREEN_CENTER_X - 1850.0f, 120.0f, 242.0f, 0.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1690.0f, 150.0f, 275.0f, 0.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1530.0f, 110.0f, 209.0f, 0.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1380.0f, 140.0f, 154.0f, 0.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1220.0f, 130.0f, 231.0f, 0.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1040.0f, 160.0f, 297.0f, 0.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 870.0f, 120.0f, 220.0f, 0.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 710.0f, 120.0f, 242.0f, 0.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 540.0f, 150.0f, 275.0f, 0.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 390.0f, 110.0f, 209.0f, 0.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 240.0f, 140.0f, 154.0f, 0.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 80.0f, 130.0f, 231.0f, 0.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 90.0f, 160.0f, 297.0f, 0.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 260.0f, 120.0f, 220.0f, 0.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 410.0f, 150.0f, 275.0f, 0.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 570.0f, 110.0f, 209.0f, 0.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 720.0f, 140.0f, 154.0f, 0.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 880.0f, 130.0f, 231.0f, 0.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1060.0f, 160.0f, 297.0f, 0.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1230.0f, 120.0f, 220.0f, 0.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1390.0f, 150.0f, 275.0f, 0.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1550.0f, 110.0f, 209.0f, 0.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1710.0f, 140.0f, 154.0f, 0.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
}

static void build_layer_5_blocks_back(void) {
    spawn_building_block(SCREEN_CENTER_X - 1600.0f, 20.0f, 420.0f, 0.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1100.0f, 1000.0f, 10.0f, 0.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1100.0f, 1000.0f, 5.0f, -15.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1100.0f, 1000.0f, 5.0f, -25.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1100.0f, 1000.0f, 5.0f, -35.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1100.0f, 1000.0f, 5.0f, -45.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1100.0f, 1000.0f, 5.0f, -55.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 600.0f, 20.0f, 420.0f, 0.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 100.0f, 1000.0f, 10.0f, 0.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 100.0f, 1000.0f, 5.0f, -15.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 100.0f, 1000.0f, 5.0f, -25.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 100.0f, 1000.0f, 5.0f, -35.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 100.0f, 1000.0f, 5.0f, -45.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 100.0f, 1000.0f, 5.0f, -55.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 400.0f, 20.0f, 420.0f, 0.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 900.0f, 1000.0f, 10.0f, 0.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 900.0f, 1000.0f, 5.0f, -15.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 900.0f, 1000.0f, 5.0f, -25.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 900.0f, 1000.0f, 5.0f, -35.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 900.0f, 1000.0f, 5.0f, -45.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 900.0f, 1000.0f, 5.0f, -55.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1400.0f, 20.0f, 420.0f, 0.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
}

static void build_layer_5_blocks_front(void) {
    spawn_building_block(SCREEN_CENTER_X - 2200.0f, 20.0f, 520.0f, 250.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1700.0f, 1000.0f, 10.0f, 145.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1700.0f, 1000.0f, 10.0f, 175.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1700.0f, 1000.0f, 10.0f, 205.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1700.0f, 1000.0f, 10.0f, 235.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1200.0f, 20.0f, 520.0f, 250.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 700.0f, 1000.0f, 10.0f, 145.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 700.0f, 1000.0f, 10.0f, 175.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 700.0f, 1000.0f, 10.0f, 205.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 700.0f, 1000.0f, 10.0f, 235.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 200.0f, 20.0f, 520.0f, 250.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 300.0f, 1000.0f, 10.0f, 145.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 300.0f, 1000.0f, 10.0f, 175.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 300.0f, 1000.0f, 10.0f, 205.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 300.0f, 1000.0f, 10.0f, 235.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 800.0f, 20.0f, 520.0f, 250.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1300.0f, 1000.0f, 10.0f, 145.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1300.0f, 1000.0f, 10.0f, 175.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1300.0f, 1000.0f, 10.0f, 205.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1300.0f, 1000.0f, 10.0f, 235.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1800.0f, 20.0f, 520.0f, 250.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
}

static void build_floating_rectangles_back(void) {
    spawn_building_block(SCREEN_CENTER_X - 1400.0f, 220.0f, 60.0f, -420.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 950.0f, 180.0f, 50.0f, 320.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 200.0f, 260.0f, 70.0f, -380.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1100.0f, 200.0f, 60.0f, 350.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 700.0f, 80.0f, 280.0f, -150.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 250.0f, 70.0f, 240.0f, 220.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 550.0f, 90.0f, 320.0f, 180.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1300.0f, 75.0f, 260.0f, -220.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1150.0f, 110.0f, 110.0f, 100.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 50.0f, 130.0f, 130.0f, -500.0f, PARALLAX_LAYER_1_SCROLL,
                         PARALLAX_LAYER_1_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1200.0f, 280.0f, 80.0f, -280.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 450.0f, 240.0f, 75.0f, 360.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 350.0f, 300.0f, 85.0f, -180.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 950.0f, 260.0f, 70.0f, 240.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 850.0f, 90.0f, 340.0f, 120.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 150.0f, 100.0f, 300.0f, -320.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 650.0f, 85.0f, 290.0f, 400.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1250.0f, 95.0f, 360.0f, -100.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 600.0f, 140.0f, 140.0f, -420.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 100.0f, 150.0f, 150.0f, 200.0f, PARALLAX_LAYER_2_SCROLL,
                         PARALLAX_LAYER_2_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1300.0f, 320.0f, 95.0f, 150.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 650.0f, 290.0f, 90.0f, -220.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 150.0f, 340.0f, 100.0f, 280.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 800.0f, 310.0f, 85.0f, -350.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1000.0f, 110.0f, 380.0f, -120.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 300.0f, 125.0f, 350.0f, 260.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 450.0f, 115.0f, 400.0f, -240.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1150.0f, 120.0f, 360.0f, 190.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 400.0f, 160.0f, 160.0f, -400.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 600.0f, 170.0f, 170.0f, 340.0f, PARALLAX_LAYER_3_SCROLL,
                         PARALLAX_LAYER_3_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1100.0f, 380.0f, 110.0f, -200.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 350.0f, 360.0f, 105.0f, 220.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 250.0f, 420.0f, 120.0f, -310.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1000.0f, 390.0f, 115.0f, 160.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 800.0f, 135.0f, 420.0f, 300.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 100.0f, 140.0f, 440.0f, -280.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 500.0f, 130.0f, 410.0f, 110.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1300.0f, 145.0f, 450.0f, -360.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 550.0f, 180.0f, 180.0f, 120.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 750.0f, 190.0f, 190.0f, -140.0f, PARALLAX_LAYER_4_SCROLL,
                         PARALLAX_LAYER_4_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1250.0f, 440.0f, 125.0f, 240.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 500.0f, 460.0f, 130.0f, -160.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 300.0f, 410.0f, 115.0f, 330.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 900.0f, 480.0f, 135.0f, -260.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 900.0f, 155.0f, 480.0f, -220.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 200.0f, 160.0f, 460.0f, 180.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 600.0f, 150.0f, 500.0f, -340.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1150.0f, 165.0f, 470.0f, 120.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 700.0f, 200.0f, 200.0f, -380.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 50.0f, 210.0f, 210.0f, 250.0f, PARALLAX_LAYER_5_SCROLL_BACK,
                         PARALLAX_LAYER_5_COLOR);
}

static void build_floating_rectangles_front(void) {
    spawn_building_block(SCREEN_CENTER_X - 1350.0f, 520.0f, 140.0f, -300.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 600.0f, 560.0f, 150.0f, 280.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 200.0f, 500.0f, 135.0f, -220.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 850.0f, 580.0f, 160.0f, 340.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 1050.0f, 175.0f, 540.0f, 160.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 350.0f, 185.0f, 510.0f, -360.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 450.0f, 180.0f, 550.0f, 220.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 1200.0f, 190.0f, 520.0f, -140.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X - 150.0f, 230.0f, 230.0f, -120.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
    spawn_building_block(SCREEN_CENTER_X + 650.0f, 240.0f, 240.0f, 390.0f, PARALLAX_LAYER_5_SCROLL_FRONT,
                         PARALLAX_LAYER_5_COLOR);
}

void scene_init(void) {
    game_camera.target = (Vector2){.x = SCREEN_CENTER_X, .y = SCREEN_CENTER_Y};
    game_camera.offset = (Vector2){.x = SCREEN_CENTER_X, .y = SCREEN_CENTER_Y + 300.0f};
    game_camera.rotation = 0.0f;
    game_camera.zoom = 1.0f;

    if (scene_type == 1) {
        build_layer_1_blocks();
        build_layer_2_blocks();
        build_layer_3_blocks();
        build_layer_4_blocks();
        build_ground_plane();
        build_layer_5_blocks_back();
        vehicle_entity = vehicle_prefab_create();
        build_layer_5_blocks_front();
    }

    if (scene_type == 2) {
        build_floating_rectangles_back();
        vehicle_entity = vehicle_prefab_create();
        build_floating_rectangles_front();
    }
}

void scene_destroy(void) {
    for (int i = MAX_ENTITIES - 1; i >= 0; --i) {
        if (HAS_COMPONENT(vehicle, i)) {
            vehicle_prefab_destroy(i);
        } else if (HAS_COMPONENT(transform, i)) {
            block_prefab_destroy(i);
        }
    }

    vehicle_entity = 0;
    game_camera = (Camera2D){0};
}
