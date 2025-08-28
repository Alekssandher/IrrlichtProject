#ifndef HOME_REGION_HPP
#define HOME_REGION_HPP

#include <string>
#include <vector>
#include <irrlicht/irrlicht.h>

class HomeRegion
{
public:
    HomeRegion(int id, const irr::core::vector3df& pos, const std::string& mapFile);

    void load(irr::scene::ISceneManager* smgr);  
    void unload();                               
    void update();

    int getId() const { return id; }
    irr::core::vector3df getPosition() const { return position; }
    irr::core::vector3df getSize() const { return size; }

private:
    int id;
    irr::core::vector3df position;
    irr::core::vector3df size;
    std::string mapFile;

    std::vector<irr::scene::ISceneNode*> sceneNodes;
};

#endif