#include "world.h"

#include <GL/glew.h>
#include "module_rendering_mode.h"
#include "test_unit_cube.h"

World::World()
{
    renderingMode = new ModuleRenderingMode();

    windowWidth = 1024;
    windowHeight = 768;
    windowTitle = "SunRay";
}

// Add your modules here
void World::AddModules()
{
    modules.push_back(renderingMode);
    modules.push_back(new TestUnitCube());
}

void World::Startup()
{
    AddModules();
    for (Module* m : modules)
    {
        m->Startup(*this);
    }

    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Basic shader
    const char* vertexSrc =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;"
        "uniform mat4 worldMatrix = mat4(1.0);"
        "uniform mat4 viewMatrix = mat4(1.0);"
        "uniform mat4 projectionMatrix = mat4(1.0);"
        "void main()"
        "{"
        "   gl_Position = projectionMatrix * viewMatrix * worldMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);"
        "}";
    const char* fragmentSrc =
        "#version 330 core\n"
        "out vec4 FragColor;"
        "void main()"
        "{"
        "   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);"
        "}";
    basicShader.create(vertexSrc, fragmentSrc);

    // Unit cube
    unitCube.vertices = {
        {glm::vec3(-1, -1, -1)}, {glm::vec3(1, -1, -1)}, {glm::vec3(1, 1, -1)}, {glm::vec3(-1, 1, -1)},
        {glm::vec3(-1, -1, 1)}, {glm::vec3(1, -1, 1)}, {glm::vec3(1, 1, 1)}, {glm::vec3(-1, 1, 1)}
    };
    unitCube.indices = {
        0, 1, 3, 3, 1, 2,
        1, 5, 2, 2, 5, 6,
        5, 4, 6, 6, 4, 7,
        4, 0, 7, 7, 0, 3,
        3, 2, 7, 7, 2, 6,
        4, 5, 0, 0, 5, 1
    };
    unitCube.createGPUBuffers();
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
