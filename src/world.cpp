#include "world.h"

#include <GL/glew.h>
#include "module_grid.h"
#include "module_rendering_mode.h"
#include "module_world_orientation.h"
#include "resources.h"
#include "test_scene_graph.h"
#include "test_unit_cube.h"
#include "test_vertex_drawing.h"


World::World()
{
    sceneGraph = new ModuleSceneGraph();
    renderingMode = new ModuleRenderingMode();

    windowWidth = 1024;
    windowHeight = 768;
    windowAspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
    windowSamples = 8;
    windowTitle = "SunRay";
}

// Add your modules here (note: order in vector is the order of execution)
void World::AddModules()
{
    // Modules
    modules.push_back(renderingMode);
    modules.push_back(new ModuleGrid());
    // world orientation
    //RE-ENABLE WHEN CAMERA IS DONE
    //modules.push_back(new ModuleWorldOrientation());

    // Tests
    modules.push_back(new TestUnitCube());
    modules.push_back(new TestVertexDrawing());
    modules.push_back(new TestSceneGraph());

    // Should always be last
    modules.push_back(sceneGraph);
}

void World::Startup()
{
    Resources::initialize();

    AddModules();
    for (Module* m : modules)
    {
        m->Startup(*this);
    }

    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void World::Shutdown()
{
    for (int i = modules.size() - 1; i >= 0; --i)
    {
        modules.at(i)->Shutdown(*this);
    }
    for (int i = modules.size() - 1; i >= 0; --i)
    {
        delete modules.at(i);
    }
}

void World::Update(float deltaSeconds)
{
    for (Module* m : modules)
    {
        m->Update(*this, deltaSeconds);
    }
}

void World::Render()
{
    renderingMode->SetupPolygonMode();

    // Each frame, reset color of each pixel to glClearColor and clear depth
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Enable backface culling
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    // Enalbe MSAA
    if (windowSamples > 0)
        glEnable(GL_MULTISAMPLE);

    for (Module* m : modules)
    {
        m->Render(*this);
    }
}

void World::OnKey(int key, int action, int mods)
{
    for (Module* m : modules)
    {
        m->OnKey(*this, key, action, mods);
    }
}
