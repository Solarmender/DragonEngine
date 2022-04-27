#include "Entity.h"

#include "../DragonEngine.h"

Entity::Entity(DragonEngine* parent)
{
	engine = parent;
}

void Entity::update()
{

}

void Entity::render()
{

}

Transform& Entity::getTransform()
{
    return transform;
}

DragonEngine* Entity::getEngine()
{
	return engine;
}
