#pragma once
class World;

class Module
{
public:

    virtual void Startup(World& world) {};
    virtual void Shutdown(World& world) {};

    virtual void Update(World& world, float deltaSeconds) {};
    virtual void Render(World& world) {};

    virtual void OnKey(World& world, int key, int action, int mods) {};
};
