#include "world.h"

#include <GL/glew.h>
#include "modules/assignment1.h"
#include "modules/fps_camera.h"
#include "modules/ground_grid.h"
#include "modules/origin_axis.h"
#include "modules/rendering_mode.h"
#include "modules/world_orientation.h"
#include "resources.h"
#include "resources_alphabet.h"
#include "tests/test_alphabet.h"
#include "tests/test_imgui_integration.h"
#include "tests/test_loader_obj.h"
#include "tests/test_scene_graph.h"
#include "tests/test_unit_cube.h"
#include "tests/test_vertex_drawing.h"

World::World()
{
    imgui = new ImGuiIntegration();
    sceneGraph = new SceneGraph();
    renderingMode = new RenderingMode();

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
    modules.push_back(imgui);
    modules.push_back(renderingMode);
    modules.push_back(new FPSCamera());
    modules.push_back(new WorldOrientation());
    modules.push_back(new GroundGrid());
    modules.push_back(new OriginAxis());

    // Tests
    // modules.push_back(new TestAlphabet());
    // modules.push_back(new TestImGuiIntegration());
    // modules.push_back(new TestLoaderObj());
    // modules.push_back(new TestUnitCube());
    // modules.push_back(new TestVertexDrawing());
    // modules.push_back(new TestSceneGraph());

    modules.push_back(new Assignment1());

    // Should always be last
    modules.push_back(sceneGraph);
}

void World::Startup(void* window)
{
    this->window = window;

    Resources::initialize();
    ResourcesAlphabet::initialize();

    AddModules();
    for (Module* m : modules)
    {
        m->Startup(*this);
    }

    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Shuts down modules in reverse order
void World::Shutdown()
{
    for (int i = static_cast<int>(modules.size() - 1); i >= 0; --i)
    {
        modules.at(i)->Shutdown(*this);
    }
    for (int i = static_cast<int>(modules.size() - 1); i >= 0; --i)
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

    time += deltaSeconds;
}

void World::Render()
{
    // Each frame, reset color of each pixel to glClearColor and clear depth
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Enable backface culling
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    // Enable MSAA
    if (windowSamples > 0)
        glEnable(GL_MULTISAMPLE);

    imgui->PreRender(*this);
    for (Module* m : modules)
    {
        m->Render(*this);
    }
    imgui->PostRender(*this);
}

void World::OnKey(int key, int action, int mods)
{
    if (imgui->wantCaptureKeyboard())
        return;
    if (key == GLFW_KEY_M && action == GLFW_PRESS)
        imgui->enabled = !imgui->enabled;

    if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
    {
        debug = !debug;

        std::cout << std::endl << "DEBUG OUTPUT: " << (debug ? "ENABLED" : "DISABLED") << std::endl;
        std::cout << "GL_VENDOR: " << glGetString(GL_VENDOR) << std::endl;
        std::cout << "GL_RENDERER: " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "GL_SHADING_LANGUAGE_VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl << std::endl;
    }

    for (Module* m : modules)
    {
        m->OnKey(*this, key, action, mods);

        if (action == GLFW_RELEASE)
            m->OnKeyReleased(*this, key, mods);
        else if (action == GLFW_PRESS || action == GLFW_REPEAT)
            m->OnKeyPressed(*this, key, mods);
    }
}

void World::OnMouseMoved(float x, float y)
{
    if (imgui->wantCaptureMouse())
        return;

    for (Module* m : modules)
    {
        m->OnMouseMoved(*this, x, y);
    }
}

void World::OnMousePressed(int button, int mods)
{
    if (imgui->wantCaptureMouse())
        return;

    for (Module* m : modules)
    {
        m->OnMousePressed(*this, button, mods);
    }
}

void World::OnMouseReleased(int button, int mods)
{
    if (imgui->wantCaptureMouse())
        return;

    for (Module* m : modules)
    {
        m->OnMouseReleased(*this, button, mods);
    }
}
