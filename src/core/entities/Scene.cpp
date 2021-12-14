#include "Scene.h"

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

void Scene::update()
{
    for(Entity* entity: gameEntities)
    {
        entity->update();
    }
}

void Scene::render()
{
    for(Entity* entity: gameEntities)
    {
        entity->render();
    }
}

Scene::~Scene()
{
    for(Entity* entity: gameEntities)
    {
        delete entity;
    }
}