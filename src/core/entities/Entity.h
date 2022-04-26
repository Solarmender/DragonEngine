#ifndef DRAGONENGINE_ENTITY_H
#define DRAGONENGINE_ENTITY_H

#include "Transform.h"
#include <DirectXMath.h>

class DragonEngine;

class Entity
{
public:
	Entity(DragonEngine* parent);

    virtual void update();

    virtual void render();

    Transform& getTransform();
protected:
	Transform transform;

	DragonEngine* engine;
private:
};

#endif //DRAGONENGINE_ENTITY_H