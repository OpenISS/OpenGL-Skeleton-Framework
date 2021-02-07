#pragma once
#include <vector>
#include "mesh.h"
#include "module_rendering_mode.h"
#include "module_scene_graph.h"
#include "shader.h"
#include "camera.h"

class World
{
public:

    World();

    void Startup();
    void Shutdown();

    void Update(float deltaSeconds);
    void Render();

    void OnKey(int key, int action, int mods);

    void OnMouseMoved(double x, double y);
    void OnMousePressed(int button, int mods);
    void OnMouseReleased(int button, int mods);

    ModuleSceneGraph* sceneGraph;
    Camera* camera;

    int windowWidth;
    int windowHeight;
    float windowAspectRatio;
    int windowSamples;
    const char* windowTitle;
    bool debug = false;

protected:

    void AddModules();

    std::vector<Module*> modules = std::vector<Module*>();

    ModuleRenderingMode* renderingMode;
};
