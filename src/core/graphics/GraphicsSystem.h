#ifndef DRAGONENGINE_GRAPHICSSYSTEM_H
#define DRAGONENGINE_GRAPHICSSYSTEM_H

class DragonEngine;

class GraphicsSystem
{
public:
    GraphicsSystem(DragonEngine* parentEngine);
    ~GraphicsSystem();
private:
    DragonEngine* engine;
};

#endif //DRAGONENGINE_GRAPHICSSYSTEM_H
