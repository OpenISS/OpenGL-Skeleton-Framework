#pragma once
#include <vector>
#include "module_rendering_mode.h"

class World
{
public:

    World();

    void Startup();
    void Shutdown();

    void Update(float deltaSeconds);
    void Render();

    void OnKey(int key, int action, int mods);

protected:

    void AddModules();

    std::vector<Module*> modules = std::vector<Module*>();

    ModuleRenderingMode* renderingMode;
};
