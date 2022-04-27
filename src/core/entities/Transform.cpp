#include "Transform.h"

Transform::Transform()
{
    position = DirectX::XMFLOAT3(0, 0, 0);
    rotation = DirectX::XMFLOAT3(0, 0, 0);
    scale = DirectX::XMFLOAT3(1, 1, 1);
}

DirectX::XMMATRIX Transform::getTranslationMatrix() const
{
    return DirectX::XMMatrixTranslation(position.x, position.y, position.z) *
            DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z) *
            DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
}

void Transform::moveAbsolute(float x, float y, float z)
{
    position.x += x;
    position.y += y;
    position.z += z;
}

void Transform::setPosition(float x, float y, float z)
{
    position.x = x;
    position.y = y;
    position.z = z;
}

void Transform::setRotation(float x, float y, float z)
{
    rotation.x = x;
    rotation.y = y;
    rotation.z = z;
}

void Transform::setScale(float x, float y, float z)
{
    scale.x = x;
    scale.y = y;
    scale.z = z;
}

