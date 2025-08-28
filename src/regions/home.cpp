#include "../headers/home.hpp"
#include <irrlicht/irrlicht.h>
#include <iostream>


HomeRegion::HomeRegion(int id, const irr::core::vector3df& pos, const std::string& mapFile)
    : id(id), position(pos), mapFile(mapFile) {}

void HomeRegion::load(irr::scene::ISceneManager* smgr) {
    
    irr::scene::ISceneNode* floor = smgr->addCubeSceneNode(
        1.0f,        
        0,           
        -1,          
        position     
    );

    if (floor) {
        floor->setScale(irr::core::vector3df(50, 0, 50));
        floor->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        floor->setMaterialTexture(0, nullptr);
        sceneNodes.push_back(floor);
    }

    #ifdef DEV
    std::cout << "Region " << id << " loaded with map: " << mapFile << '\n';
    #endif
}

void HomeRegion::unload() {
    for (auto* node : sceneNodes) {
        if (node) node->remove();
    }
    sceneNodes.clear();
    #ifdef DEV
    std::cout << "Region " << id << " unloaded." << '\n';
    #endif
}

void HomeRegion::update() {
    // to do
}