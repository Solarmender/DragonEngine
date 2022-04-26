#ifndef DRAGONENGINE_ENTITY_H
#define DRAGONENGINE_ENTITY_H

#include <DirectXMath.h>

class DragonEngine;

class Entity
{
public:
	Entity(DragonEngine* parent);

    virtual void update();

    virtual void render();

	DirectX::XMFLOAT3 getPosition();
	DirectX::XMFLOAT3 getRotation();
	DirectX::XMMATRIX getTranslationMatrix();
protected:
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;

	DragonEngine* engine;
private:
};

#endif //DRAGONENGINE_ENTITY_H