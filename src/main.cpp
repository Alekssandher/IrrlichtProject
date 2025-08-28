#include <irrlicht/irrlicht.h>
#include "irrlicht/driverChoice.h"

#define DEV

#include "headers/perfomance_infos.hpp"
#include "headers/config.hpp"
#include "headers/area.hpp"
#include "headers/home.hpp"

#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include <cstdint>

using namespace irr;


#ifdef CALC_DELTA
float calc_delta(IrrlichtDevice *& device, u32 & last_time)
{
    u32 now = device->getTimer()->getTime();
    float deltaTime = static_cast<float>((now - last_time)) / 1000.0f; 
    last_time = now;

    return deltaTime;
}
#endif

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

#ifdef CUBE

float r_degree_per_sec = 30.0f;

void rotate_cube(scene::ISceneNode* & cube, float delta_t)
{
    core::vector3df rot = cube->getRotation(); 
    rot.Y += r_degree_per_sec * delta_t; 
    rot.X += r_degree_per_sec * delta_t;

    cube->setRotation(rot);
}


void move_cube(scene::ISceneNode* & cube, float delta_t, MyEventReceiver &receiver, core::vector3df &nodePosition)
{
    float speed = receiver.IsKeyDown(irr::KEY_SPACE) ? 15.0f : 10.0f;

    if(receiver.IsKeyDown(irr::KEY_KEY_W))
        nodePosition.Z += speed * delta_t;
    else if(receiver.IsKeyDown(irr::KEY_KEY_S))
        nodePosition.Z -= speed * delta_t;

    if(receiver.IsKeyDown(irr::KEY_UP))
        nodePosition.Y += speed * delta_t;
    else if(receiver.IsKeyDown(irr::KEY_DOWN))
        nodePosition.Y -= speed * delta_t;

    if(receiver.IsKeyDown(irr::KEY_KEY_A))
        nodePosition.X -= speed * delta_t;
    else if(receiver.IsKeyDown(irr::KEY_KEY_D))
        nodePosition.X += speed * delta_t;

    cube->setPosition(nodePosition);
}
#endif

Area area(2, irr::core::vector3df(0,0,0));


void add_floor(core::vector3df pos, scene::IMesh* mesh, scene::ISceneManager* scenemgr)
{
    video::SColor randomColor(
        255,                    
        rand() % 256,            
        rand() % 256,            
        rand() % 256             
    );
    scene::IMeshSceneNode* floorNode = scenemgr->addMeshSceneNode(mesh);

    if(floorNode) {
        floorNode->setPosition(pos + irr::core::vector3df(area.size.X/2, -1, area.size.Z/2));
        floorNode->setMaterialFlag(video::EMF_LIGHTING, true);
        floorNode->getMaterial(0).DiffuseColor = randomColor;
        floorNode->getMaterial(0).EmissiveColor = randomColor;
    }


}

void generate_floors(int quantity, core::vector3df relative_to, scene::IMesh* mesh, scene::ISceneManager* scenemgr)
{
    core::vector3df pos = relative_to;

    core::aabbox3d<f32> bbox = mesh->getBoundingBox();
    core::vector3df size = bbox.getExtent();

    for(int i {}; i < quantity; i++)
    {
        add_floor(pos, mesh, scenemgr);
        pos.X -= size.X;

    }
}

int main()
{
    srand(time(0));

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
    
    irr::SKeyMap keyMap[5];
    keyMap[0].Action = irr::EKA_MOVE_FORWARD; keyMap[0].KeyCode = irr::KEY_KEY_W;
    keyMap[1].Action = irr::EKA_MOVE_BACKWARD; keyMap[1].KeyCode = irr::KEY_KEY_S;
    keyMap[2].Action = irr::EKA_STRAFE_LEFT; keyMap[2].KeyCode = irr::KEY_KEY_A;
    keyMap[3].Action = irr::EKA_STRAFE_RIGHT; keyMap[3].KeyCode = irr::KEY_KEY_D;
    keyMap[4].Action = irr::EKA_JUMP_UP; keyMap[4].KeyCode = irr::KEY_SPACE;
    

    scene::ICameraSceneNode* camera = scenemgr->addCameraSceneNodeFPS(
        0,        
        80.0f,   
        0.02f,    
        -1,       
        keyMap,   
        5,
        true,    
        0.0f,    
        false
    );

    camera->setPosition(core::vector3df(0,5,0));

    device->getCursorControl()->setVisible(false);


    //generate_floors(3, irr::core::vector3df(0,0,0), planeMesh, scenemgr);

    HomeRegion homeRegion(
        1,
        irr::core::vector3df(0, 0, 0),   
        "map1.irr"                       
    );
    
    homeRegion.load(scenemgr);

    while (device->run())
    {

        driver->beginScene(true, true, video::SColor(255,100,101,140));

        scenemgr->drawAll(); 
        guienv->drawAll();
        driver->endScene();
        
        #ifdef DEV
        print_memory_usage();
        #endif
        
    }

    device->drop();

    return 0;
}
