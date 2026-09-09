cmake_minimum_required(VERSION 4.0)
project(parallax C)

set(CMAKE_C_STANDARD 17)

add_executable(parallax src/game/main.c)

target_sources(parallax PRIVATE
        src/core/config.h
        src/core/input_bridge.h
        src/core/math.h
        src/ecs/ecs.c
        src/ecs/ecs.h
)

target_sources(parallax PRIVATE
        src/components/render.c
        src/components/render.h
        src/components/size.c
        src/components/size.h
        src/components/transform.c
        src/components/transform.h
        src/components/velocity.c
        src/components/velocity.h
        src/components/vehicle.c
        src/components/vehicle.h
        src/components/space_ship.c
        src/components/space_ship.h
        src/components/parallax_layer.c
        src/components/parallax_layer.h
)

target_sources(parallax PRIVATE
        src/systems/input_system.c
        src/systems/input_system.h
        src/systems/movement_system.c
        src/systems/movement_system.h
        src/systems/raylib/camera_system.c
        src/systems/raylib/camera_system.h
        src/systems/raylib/input_system.c
        src/systems/raylib/input_system.h
        src/systems/raylib/render_system_vector.c
        src/systems/raylib/render_system_vector.h
)

target_sources(parallax PRIVATE
        src/game/scene.c
        src/game/scene.h
        src/game/prefabs/vehicle_prefab.c
        src/game/prefabs/vehicle_prefab.h
        src/game/prefabs/space_ship_prefab.c
        src/game/prefabs/space_ship_prefab.h
        src/game/prefabs/block_prefab.c
        src/game/prefabs/block_prefab.h
)

if (MSVC)
    set(RAYLIB_SUBDIR "msvc")
    set(RAYLIB_LIB_NAME "raylib.lib")
    set(PLATFORM_LIBS winmm gdi32 user32 shell32)
elseif (MINGW)
    set(RAYLIB_SUBDIR "mingw")
    set(RAYLIB_LIB_NAME "libraylib.a")
    set(PLATFORM_LIBS winmm gdi32 user32 shell32)
elseif (APPLE)
    set(RAYLIB_SUBDIR "macos")
    set(RAYLIB_LIB_NAME "libraylib.a")
    set(PLATFORM_LIBS "-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo")
else ()
    message(FATAL_ERROR "Unsupported platform or compiler!")
endif ()

target_include_directories(parallax PRIVATE "${CMAKE_SOURCE_DIR}/external/raylib/${RAYLIB_SUBDIR}/include")

target_link_libraries(parallax PRIVATE
        "${CMAKE_SOURCE_DIR}/external/raylib/${RAYLIB_SUBDIR}/lib/${RAYLIB_LIB_NAME}"
        ${PLATFORM_LIBS}
)