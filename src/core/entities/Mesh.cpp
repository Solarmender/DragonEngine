#include "Mesh.h"
#include "DirectXMath.h"


inline void CheckIndexOverflow(size_t value)
{
	if (value >= USHRT_MAX)
		abort();
}

inline void index_push_back(IndexVector& indices, size_t value)
{
	CheckIndexOverflow(value);
	indices.push_back(static_cast<uint16_t>(value));
}

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

Mesh* createSphere()
{
    Mesh* sphere = new Mesh();

	float diameter = 3;
	size_t tessellation = 16;

	if (tessellation < 3)
	{
		abort();
	}

	const size_t verticalSegments = tessellation;
	const size_t horizontalSegments = tessellation * 2;

	const float radius = diameter / 2;

	for (size_t i = 0; i <= verticalSegments; i++)
	{
		const float latitude = (float(i) * DirectX::XM_PI / float(verticalSegments)) - DirectX::XM_PIDIV2;
		float dy, dxz;

		DirectX::XMScalarSinCos(&dy, &dxz, latitude);

		for (size_t j = 0; j <= horizontalSegments; j++)
		{
			const float longitude = float(j) * DirectX::XM_2PI / float(horizontalSegments);
			float dx, dz;

			DirectX::XMScalarSinCos(&dx, &dz, longitude);

			dx *= dxz;
			dz *= dxz;

			const DirectX::XMVECTOR normal = DirectX::XMVectorSet(dx, dy, dz, 0);

			DirectX::XMFLOAT3 pos;
			DirectX::XMStoreFloat3(&pos, DirectX::XMVectorScale(normal, radius));
			sphere->vertices.push_back(pos.x);
			sphere->vertices.push_back(pos.y);
			sphere->vertices.push_back(pos.z);
		}
	}

	const size_t stride = horizontalSegments + 1;

	for (size_t i = 0; i < verticalSegments; i++)
	{
		for (size_t j = 0; j <= horizontalSegments; j++)
		{
			const size_t nextI = i + 1;
			const size_t nextJ = (j + 1) % stride;

			index_push_back(sphere->indices, i * stride + j);
			index_push_back(sphere->indices, nextI * stride + j);
			index_push_back(sphere->indices, i * stride + nextJ);

			index_push_back(sphere->indices, i * stride + nextJ);
			index_push_back(sphere->indices, nextI * stride + j);
			index_push_back(sphere->indices, nextI * stride + nextJ);
		}
	}

    return sphere;
}
