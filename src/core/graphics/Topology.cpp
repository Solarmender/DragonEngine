#include "Topology.h"

Topology::Topology(GraphicsSystem* gfx)
{
	graphics = gfx;
}

void Topology::set()
{
	graphics->getDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
