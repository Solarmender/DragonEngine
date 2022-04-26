#include "Entity.h"

#include "../DragonEngine.h"

Entity::Entity(DragonEngine* parent)
{
	engine = parent;

	position = DirectX::XMFLOAT3(0, 0, 0);
	rotation = DirectX::XMFLOAT3(0, 0, 0);
	scale = DirectX::XMFLOAT3(1, 1, 1);
}

void Entity::update()
{

}

void Entity::render()
{

}

DirectX::XMFLOAT3 Entity::getPosition()
{
	return position;
}

DirectX::XMFLOAT3 Entity::getRotation()
{
	return rotation;
}

DirectX::XMMATRIX Entity::getTranslationMatrix()
{
	return DirectX::XMMatrixTranslation(position.x, position.y, position.z) *
			DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z) *
			DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
}
