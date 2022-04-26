#include "Scene.h"
#include <stdexcept>
#include "Windows.h"

Scene::Scene()
{
	previousTime = std::chrono::high_resolution_clock::now();
}

void Scene::addEntity(Entity* newEntity)
{
    gameEntities.push_back(newEntity);
}

void Scene::removeEntity(Entity* removalEntity)
{
    for(auto it = gameEntities.begin(); it != gameEntities.end();)
    {
        if((*it) == removalEntity)
        {
            delete *it;
            gameEntities.erase(it);
            return;
        }
    }
}

void Scene::setCamera(Camera* newCamera)
{
	currentCamera = newCamera;
}

void Scene::update()
{
	std::chrono::time_point<std::chrono::high_resolution_clock> currentTime = std::chrono::high_resolution_clock::now();
	auto elapsed = currentTime - previousTime;
	auto seconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);

	deltaTime = seconds.count() / 1000.0f;

	if(currentCamera == nullptr)
	{
		throw std::runtime_error("There is no camera");
	}

    for(Entity* entity: gameEntities)
    {
        entity->update();
    }

	previousTime = currentTime;
}

Camera* Scene::getCamera()
{
	return currentCamera;
}

void Scene::render()
{
    for(Entity* entity: gameEntities)
    {
        entity->render();
    }
}
