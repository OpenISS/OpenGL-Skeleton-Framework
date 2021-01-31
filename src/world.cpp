#include "world.h"

#include <GL/glew.h>
#include "module_rendering_mode.h"

World::World()
{
    renderingMode = new ModuleRenderingMode();
}

// Add your modules here
void World::AddModules()
{
    modules.push_back(renderingMode);
}

void World::Startup()
{
    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    AddModules();
    for (Module* m : modules)
    {
        m->Startup();
    }
}

void World::Shutdown()
{
    for (int i = modules.size() - 1; i >= 0; --i)
    {
        modules.at(i)->Shutdown();
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
        m->Update(deltaSeconds);
    }
}

void World::Render()
{
    renderingMode->SetupPolygonMode();

    // Each frame, reset color of each pixel to glClearColor and clear depth
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (Module* m : modules)
    {
        m->Render();
    }
}

void World::OnKey(int key, int action, int mods)
{
    for (Module* m : modules)
    {
        m->OnKey(key, action, mods);
    }
}
