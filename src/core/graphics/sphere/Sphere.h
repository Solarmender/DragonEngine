#ifndef DRAGONENGINE_SPHERE_H
#define DRAGONENGINE_SPHERE_H

#include "../../entities/Entity.h"
#include "../VertexShader.h"
#include "../PixelShader.h"
#include "../InputLayout.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../ConstantBuffer.h"
#include "../Topology.h"
#include "../../entities/Mesh.h"

class Sphere : public Entity
{
public:
    explicit Sphere(DragonEngine* parent);

    void update() override;
    void render() override;

	void orbit(float x, float y, float z, float r, float a);
private:
    Mesh* sphereMesh;
    VertexShader* vertexShader;
    PixelShader* pixelShader;
    InputLayout* inputLayout;
    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;
    ConstantBuffer* constantBuffer;
    Topology* topology;

	float radius = 2;
	float orbitSpeed = 1;
	bool shouldOrbit = false;
	float orbitAngle = 0;
};

#endif //DRAGONENGINE_SPHERE_H
