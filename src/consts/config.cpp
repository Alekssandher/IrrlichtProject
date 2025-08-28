#include "irrlicht/irrlicht.h"

using namespace irr;

namespace Config {
    const core::dimension2d<u32> SCREEN_SIZE(640, 480);
    const core::vector3df MAP_SIZE(40, 0, 40);
    constexpr int COLOR_DEPTH = 16;
    constexpr float MOVEMENT_SPEED = 5.0f;
    constexpr bool FULL_SCREEN = false;
    constexpr bool STENCIL_BUFFER = false;
    constexpr bool VSYNC = false;
}