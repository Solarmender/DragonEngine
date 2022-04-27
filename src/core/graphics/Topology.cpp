#include "Topology.h"

Topology::Topology(GraphicsSystem* gfx)
{
	graphics = gfx;
}

void Topology::set()
{
	// D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP
	graphics->getDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
