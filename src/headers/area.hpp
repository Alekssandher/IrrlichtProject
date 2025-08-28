#ifndef AREA_HPP
#define AREA_HPP

#include "irrlicht/irrlicht.h"

constexpr float AREA_WIDTH = 100.0f;
constexpr float AREA_HEIGHT = 100.0f;

struct Area {
    int id;
    irr::core::vector3df position;
    irr::core::vector3df size = irr::core::vector3df(AREA_WIDTH, 20.0f, AREA_HEIGHT);

    Area(int _id, irr::core::vector3df _position)
        : id(_id), position(_position), size(AREA_WIDTH, 20.0f, AREA_HEIGHT) {}
};

#endif