#include "Camera.h"
#include "../DragonEngine.h"
#include <string>
#include "../logger/Logger.h"

Camera::Camera(DragonEngine* parent) : Entity(parent)
{
	transform.position = DirectX::XMFLOAT3(0, 3, -10);
    transform.rotation = DirectX::XMFLOAT3(0.5, 0, 0);
}

void Camera::update()
{
    float deltaTime = engine->getScene()->deltaTime;

    if(engine->getInput()->isPressed('W'))
    {
        transform.moveAbsolute(0, 0, 50 * deltaTime);
    }
    if(engine->getInput()->isPressed('A'))
    {
        transform.moveAbsolute(-50 * deltaTime, 0, 0);
    }
    if(engine->getInput()->isPressed('S'))
    {
        transform.moveAbsolute(0, 0, -50 * deltaTime);
    }
    if(engine->getInput()->isPressed('D'))
    {
        transform.moveAbsolute(+50 * deltaTime, 0, 0);
    }
    if(engine->getInput()->isPressed('Q'))
    {
        transform.moveAbsolute(0, 50 * deltaTime, 0);
    }
    if(engine->getInput()->isPressed('Z'))
    {
        transform.moveAbsolute(0, -50 * deltaTime, 0);
    }

    if(engine->getInput()->isPressed('I'))
    {
        transform.rotation.x -= 15 * deltaTime;
    }
    if(engine->getInput()->isPressed('J'))
    {
        transform.rotation.y -= 15 * deltaTime;
    }
    if(engine->getInput()->isPressed('K'))
    {
        transform.rotation.x += 15 * deltaTime;
    }
    if(engine->getInput()->isPressed('L'))
    {
        transform.rotation.y += 15 * deltaTime;
    }
    if(engine->getInput()->isPressed('U'))
    {
        transform.rotation.z += 15 * deltaTime;
    }
    if(engine->getInput()->isPressed('O'))
    {
        transform.rotation.z -= 15 * deltaTime;
    }
}

DirectX::XMMATRIX Camera::getViewMatrix()
{
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(transform.rotation.x, transform.rotation.y, transform.rotation.z);
	DirectX::XMVECTOR eyePosition = DirectX::XMVectorSet( transform.position.x, transform.position.y, transform.position.z, 1);
	DirectX::XMVECTOR lookVector = XMVector3Transform(DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), rotationMatrix);
    DirectX::XMVECTOR upDirection = XMVector3TransformCoord(DirectX::XMVectorSet(0, 1, 0, 0), rotationMatrix);
	return DirectX::XMMatrixLookAtLH( eyePosition, DirectX::XMVectorAdd(lookVector, eyePosition), upDirection);
}

DirectX::XMMATRIX Camera::getProjectionMatrix()
{
	RECT rect;
	GetWindowRect( engine->getWindow()->getWindow(), &rect);
	float windowWidth = rect.right - rect.left;
	float windowHeight = rect.bottom - rect.top;

	return DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(45.0f), windowWidth/windowHeight, 0.1f, 100.0f);
}
