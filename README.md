# 🌇 raylib-parallax-2d

**raylib-parallax-2d** is a lightweight 2D parallax side-scroller template.

It is perfect for anyone starting with low-level game development or looking for a base template to build parallax scrolling effects.

---

### ✨ Features

* **Tech Stack:** Built with C17 and Raylib.
* **Multi-Axis Parallax Engine:** Supports independent horizontal and vertical scrolling depth per layer.
* **Automatic Depth Sorting:** Back-to-front rendering pass based on layer scroll factors to eliminate draw order dependencies.
* **Configurable Layer Dynamics:** Adjustable dampening factors, scroll speeds, and custom bounding limits for precise camera constraints.
* **Cache-Friendly Architecture:** Custom macro-based ECS using parallel component arrays with $O(1)$ component access.
* **Zero Assets:** 100% procedural vector graphics.
* **Cross-Platform & Toolchain Ready:** Automatic compiler detection for MinGW and MSVC (Windows) and macOS. Works out
  of the box in CLion and Visual Studio.
* **Single Binary Output:** Compiles directly into a single executable for easy distribution.
* **Free & Open:** Completely free to use and modify for any project.

---

### 🧮 Parallax Calculation

**Parallax offsets** are computed per-entity based on camera displacement relative to screen center and scaled by the layer's `scroll_factor`:

```c++
// src/systems/raylib/render_system_vector.c

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
```

**Scroll factors** determine how fast a layer moves relative to the camera, creating the illusion of 3D depth in a 2D scene—where values closer to 0.0 represent distant background elements and values closer to 1.0 align directly with the gameplay action.

```c++
// src/game/scene.c

static const float PARALLAX_LAYER_1_SCROLL = 0.15f;
static const float PARALLAX_LAYER_2_SCROLL = 0.35f;
static const float PARALLAX_LAYER_3_SCROLL = 0.55f;
static const float PARALLAX_LAYER_4_SCROLL = 0.75f;

static const float PARALLAX_LAYER_5_SCROLL_BACK = 0.90f;
static const float PARALLAX_LAYER_5_SCROLL_FRONT = 1.30f;

static const float GROUND_SCROLL = 1.00f;
```
**Examples**

* **`0.0 - 0.3` (Far Background):** Moves very slowly; tracks closely with the camera (e.g., mountains, sky).
* **`0.4 - 0.8` (Midground):** Moves at moderate speed (e.g., distant buildings, trees).
* **`1.0` (Gameplay Layer):** Anchored 1:1 with world space (e.g., player vehicle, road, obstacles).
* **`> 1.0` (Foreground):** Moves faster than the camera to appear close to the lens.

**ParallaxLayer** component should be added to entity in order for it to work as parallax element.

```c++
// src/components/parallax_layer.h
typedef struct {
    float scroll_factor;
} ParallaxLayer;


// src/game/prefabs/block_prefab.c
const ParallaxLayer parallax_layer_component = {
    .scroll_factor = scroll_factor,
};

ADD_COMPONENT(parallax_layer, building_entity, parallax_layer_component);

```

---

### 🙏 Credits

Built with [raylib](https://www.raylib.com/) by [@raysan5](https://github.com/raysan5).