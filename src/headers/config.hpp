#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <irrlicht/irrlicht.h>

namespace Config {
    const irr::core::dimension2d<irr::u32> SCREEN_SIZE(640, 480);
    const irr::core::vector3df MAP_SIZE(40, 0, 40);
    constexpr int COLOR_DEPTH = 16;
    constexpr float MOVEMENT_SPEED = 5.0f;
    constexpr bool FULL_SCREEN = false;
    constexpr bool STENCIL_BUFFER = false;
    constexpr bool VSYNC = false;
}

#endif