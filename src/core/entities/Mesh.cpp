#include "Mesh.h"

Mesh* createCube()
{
    Mesh* cube = new Mesh();

    float cubeVertices[] = {
            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,
    };

    for(int i{ 0 }; i < sizeof(cubeVertices)/sizeof(cubeVertices[0]); i++)
    {
        cube->vertices.push_back(cubeVertices[i]);
    }

    unsigned short cubeIndices[] =
            {
                    3,1,0,
                    2,1,3,

                    0,5,4,
                    1,5,0,

                    3,4,7,
                    0,4,3,

                    1,6,5,
                    2,6,1,

                    2,7,6,
                    3,7,2,

                    6,4,5,
                    7,4,6,
            };

    for(int i{ 0 }; i < sizeof(cubeIndices)/sizeof(cubeIndices[0]); i++)
    {
        cube->indices.push_back(cubeIndices[i]);
    }

    return cube;
}

static Mesh* createSphere()
{
    Mesh* sphere = new Mesh();

    return sphere;
}
