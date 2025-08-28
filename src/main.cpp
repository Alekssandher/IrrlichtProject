#include <irrlicht/irrlicht.h>
#include "irrlicht/driverChoice.h"

#define DEV

#include "headers/perfomance_infos.hpp"
#include "headers/config.hpp"

#include <iostream>
#include <cstdint>

using namespace irr;

float r_degree_per_sec = 30.0f;

void rotate_cube(scene::ISceneNode* & cube, float delta_t)
{
    core::vector3df rot = cube->getRotation(); 
    rot.Y += r_degree_per_sec * delta_t; 
    rot.X += r_degree_per_sec * delta_t;

    cube->setRotation(rot);
}


float calc_delta(IrrlichtDevice *& device, u32 & last_time)
{
    u32 now = device->getTimer()->getTime();
    float deltaTime = static_cast<float>((now - last_time)) / 1000.0f; 
    last_time = now;

    return deltaTime;
}

class MyEventReceiver : public IEventReceiver
{
public:
    virtual bool OnEvent(const SEvent& event)
    {
        if(event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        
        return false;
    }

    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }
    
    MyEventReceiver()
    {
        for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    }

private:
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

void move_cube(scene::ISceneNode* & cube, float delta_t, MyEventReceiver &receiver)
{
    float speed = receiver.IsKeyDown(irr::KEY_SPACE) ? 15.0f : 10.0f;

    core::vector3df nodePosition = cube->getPosition();

    if(receiver.IsKeyDown(irr::KEY_KEY_W))
        nodePosition.Y += speed * delta_t;
    else if(receiver.IsKeyDown(irr::KEY_KEY_S))
        nodePosition.Y -= speed * delta_t;

    if(receiver.IsKeyDown(irr::KEY_KEY_A))
        nodePosition.X -= speed * delta_t;
    else if(receiver.IsKeyDown(irr::KEY_KEY_D))
        nodePosition.X += speed * delta_t;

    cube->setPosition(nodePosition);
}

int main()
{
    MyEventReceiver receiver;
    
    IrrlichtDevice *device = createDevice(
        video::EDT_OPENGL, Config::SCREEN_SIZE,
        Config::COLOR_DEPTH,
        Config::FULL_SCREEN, 
        Config::STENCIL_BUFFER, 
        Config::VSYNC, 
        &receiver
    );

    if (!device)
        device = createDevice(
            video::EDT_SOFTWARE,
            Config::SCREEN_SIZE,
            Config::COLOR_DEPTH,
            Config::FULL_SCREEN,
            Config::STENCIL_BUFFER,
            Config::VSYNC,
            &receiver
        );

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* scenemgr = device->getSceneManager();

    gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

    guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
        core::rect<s32>(10,10,260,22), true);

    device->setWindowCaption(L"TestProject");

    scene::ISceneNode* cube = scenemgr->addCubeSceneNode();

    if (cube)
        cube->setMaterialFlag(video::EMF_LIGHTING, false);
    
    core::vector3df cameraPos(0, 10, -20);  
    core::vector3df target(0, 0, 0);

    scenemgr->addCameraSceneNode(0, cameraPos, target);

    u32 last_time = device->getTimer()->getTime(); 

    while (device->run())
    {
        float delta = calc_delta(device, last_time);
        rotate_cube(cube, delta);
        move_cube(cube, delta, receiver);
        driver->beginScene(true, true, video::SColor(255,100,101,140));

        scenemgr->drawAll(); 
        guienv->drawAll();
        driver->endScene();
        
        #ifdef DEV
        get_memory_usage();
        #endif
    }

    device->drop();

    return 0;
}
