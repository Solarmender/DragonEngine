#ifndef DRAGONENGINE_SCENE_H
#define DRAGONENGINE_SCENE_H

#include "Entity.h"
#include <vector>
#include <memory>

class Scene
{
public:
    Scene() = default;
    ~Scene();

    void addEntity(Entity* newEntity);
    void removeEntity(Entity* removalEntity);

    void update();
    void render();
private:
    std::vector<Entity*> gameEntities;
};

#endif //DRAGONENGINE_SCENE_H