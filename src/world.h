#pragma once
#include <vector>
#include <string>
#include "mesh.h"
#include "module_rendering_mode.h"
#include "shader.h"

class World
{
public:

    World();

    void Startup();
    void Shutdown();

    void Update(float deltaSeconds);
    void Render();

    void OnKey(int key, int action, int mods);

    int windowWidth;
    int windowHeight;
    std::string windowTitle;

    Shader basicShader;
    Mesh unitCube;

protected:

    void AddModules();

    std::vector<Module*> modules = std::vector<Module*>();

    ModuleRenderingMode* renderingMode;
};
