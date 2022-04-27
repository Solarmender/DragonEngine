#ifndef DRAGONENGINE_MESH_H
#define DRAGONENGINE_MESH_H

#include <vector>

using vertexVector = std::vector<float>;
using IndexVector = std::vector<uint16_t>;

class Mesh
{
public:
	vertexVector vertices;
	IndexVector indices;
private:
};

Mesh* createCube();
Mesh* createSphere();

#endif //DRAGONENGINE_MESH_H
