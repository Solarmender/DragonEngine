#ifndef DRAGONENGINE_TRANSFORM_H
#define DRAGONENGINE_TRANSFORM_H

#include "DirectXMath.h"

class Transform {
public:
    Transform();

    DirectX::XMMATRIX getTranslationMatrix() const;

    void moveAbsolute(float x, float y, float z);

    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 rotation;
    DirectX::XMFLOAT3 scale;
private:
};

#endif //DRAGONENGINE_TRANSFORM_H
