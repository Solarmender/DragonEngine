#ifndef DRAGONENGINE_SRC_CORE_GRAPHICS_TOPOLOGY_H
#define DRAGONENGINE_SRC_CORE_GRAPHICS_TOPOLOGY_H

#include "GraphicsSystem.h"
#include "d3d11.h"

class Topology
{
public:
	explicit Topology(GraphicsSystem* gfx);

	void set();
private:
	GraphicsSystem* graphics;
};

#endif //DRAGONENGINE_SRC_CORE_GRAPHICS_TOPOLOGY_H
