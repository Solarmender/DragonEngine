#ifndef DRAGONENGINE_MESH_H
#define DRAGONENGINE_MESH_H

#include <vector>

class Mesh
{
public:
    std::vector<float> vertices;
    std::vector<unsigned short> indices;
private:
};

Mesh* createCube();
Mesh* createSphere();

#endif //DRAGONENGINE_MESH_H
