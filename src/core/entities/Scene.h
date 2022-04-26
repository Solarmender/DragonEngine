#ifndef DRAGONENGINE_SCENE_H
#define DRAGONENGINE_SCENE_H

#include "Camera.h"
#include "Entity.h"
#include <chrono>
#include <vector>
#include <memory>

class Scene
{
public:
	Scene();

    void addEntity(Entity* newEntity);
    void removeEntity(Entity* removalEntity);

	Camera* getCamera();
	void setCamera(Camera* newCamera);

    void update();
    void render();

	float deltaTime = 0;
private:
	Camera* currentCamera;

    std::vector<Entity*> gameEntities;

	std::chrono::time_point<std::chrono::high_resolution_clock> previousTime;
};

#endif //DRAGONENGINE_SCENE_H