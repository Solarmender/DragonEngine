#include "Camera.h"
#include "../DragonEngine.h"
#include <string>
#include "../logger/Logger.h"

Camera::Camera(DragonEngine* parent) : Entity(parent)
{
	position = DirectX::XMFLOAT3(0, 0, -10);
	rotation = DirectX::XMFLOAT3(0, 0, 0);
}

void Camera::update()
{

	DirectX::XMFLOAT3 translation = DirectX::XMFLOAT3();

	float deltaTime = engine->getScene()->deltaTime;

	if(engine->getInput()->isPressed('W'))
	{
		translation.z = translation.z + deltaTime;
	}
	if(engine->getInput()->isPressed('A'))
	{
		translation.x = translation.x - deltaTime;
	}
	if(engine->getInput()->isPressed('S'))
	{
		translation.z = translation.z - deltaTime;
	}
	if(engine->getInput()->isPressed('D'))
	{
		translation.x = translation.x + deltaTime;
	}
	if(engine->getInput()->isPressed('Q'))
	{
		rotation.z = rotation.z + deltaTime * 2;
	}
	if(engine->getInput()->isPressed('E'))
	{
		rotation.z = rotation.z - deltaTime * 2;
	}

	DirectX::XMStoreFloat3(&translation, DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&translation), DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z) * DirectX::XMMatrixScaling(5, 5, 5)));
	position = { position.x + translation.x, position.y + translation.y, position.z + translation.z };
}

DirectX::XMMATRIX Camera::getViewMatrix()
{
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	DirectX::XMVECTOR eyePosition = DirectX::XMVectorSet( position.x, position.y, position.z, 1 );
	DirectX::XMVECTOR lookVector = XMVector3Transform(DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), rotationMatrix);
	return DirectX::XMMatrixLookAtLH( eyePosition, DirectX::XMVectorAdd(lookVector, eyePosition), XMVector3TransformCoord(DirectX::XMVectorSet(0, 1, 0, 0), rotationMatrix));
}

DirectX::XMMATRIX Camera::getProjectionMatrix()
{
	RECT rect;
	GetWindowRect( engine->getWindow()->getWindow(), &rect);
	float windowWidth = rect.right - rect.left;
	float windowHeight = rect.bottom - rect.top;

	return DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(45.0f), windowWidth/windowHeight, 0.1f, 100.0f);
}
