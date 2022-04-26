#ifndef DRAGONENGINE_SRC_CORE_ENTITIES_CAMERA_H
#define DRAGONENGINE_SRC_CORE_ENTITIES_CAMERA_H

#include "Entity.h"

class Camera : public Entity
{
public:
	explicit Camera(DragonEngine* parent);

	void update() override;

	DirectX::XMMATRIX getViewMatrix();
	DirectX::XMMATRIX getProjectionMatrix();
private:
};

#endif //DRAGONENGINE_SRC_CORE_ENTITIES_CAMERA_H
