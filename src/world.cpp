#include "world.h"

#include <GL/glew.h>
#include "modules/assignment1.h"
#include "modules/assignment2.h"
#include "modules/assignment3.h"
#include "modules/fps_camera.h"
#include "modules/ground_grid.h"
#include "modules/module_manager_ui.h"
#include "modules/origin_axis.h"
#include "modules/rendering_mode.h"
#include "modules/world_orientation.h"
#include "resources.h"
#include "resources_alphabet.h"
#include "tests/test_alphabet.h"
#include "tests/test_half_cylinder.h"
#include "tests/test_imgui_integration.h"
#include "tests/test_lit_shader.h"
#include "tests/test_loader_obj.h"
#include "tests/test_multi_lights.h"
#include "tests/test_scene_graph.h"
#include "tests/test_shape_meshes.h"
#include "tests/test_texture.h"
#include "tests/test_unit_cube.h"
#include "tests/test_vertex_drawing.h"
#include "tests/test_openiss.h"

World::World()
{
    imgui = new ImGuiIntegration(true);
    sceneGraph = new SceneGraph(true);
    renderingMode = new RenderingMode(true);
    shadows = new Shadows(true);

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
    modules.push_back(shadows);
    modules.push_back(new FPSCamera());
    modules.push_back(new WorldOrientation(false));
    modules.push_back(new GroundGrid(false));
    modules.push_back(new OriginAxis(false));

    // Tests
    modules.push_back(new TestAlphabet(false));
    modules.push_back(new TestHalfCylinder(false));
    modules.push_back(new TestImGuiIntegration(false));
    modules.push_back(new TestLitShader(false));
    modules.push_back(new TestLoaderObj(false));
    modules.push_back(new TestUnitCube(false));
    modules.push_back(new TestVertexDrawing(false));
    modules.push_back(new TestSceneGraph(false));
    modules.push_back(new TestShapeMeshes(false));
    modules.push_back(new TestTexture(false));
    modules.push_back(new TestMultiLights(false));
    modules.push_back(new TestOpenISS(false));

    modules.push_back(new Assignment1(false));
    modules.push_back(new Assignment2(false));
    modules.push_back(new Assignment3(true));

    // Should always be last
    modules.push_back(sceneGraph);
    modules.push_back(new ModuleManagerUI(true));
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
        if (m->getEnabled())
            m->Update(*this, deltaSeconds);
    }

    time += deltaSeconds;
}

void World::Render()
{
    glm::mat4 view = camera->view();
    glm::mat4 projection = camera->projection();
    for (auto shader : Resources::getShaders())
    {
        if (shader->needsCamera)
        {
            shader->activate();
            shader->setViewProjectionMatrix(view, projection);
            shader->setViewPosition(camera->getPosition());
        }
    }


    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Enable MSAA
    if (windowSamples > 0)
        glEnable(GL_MULTISAMPLE);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    if (shadows->getEnabled())
        shadows->PreRender();

    int lightIndex = 0;
    for (size_t i = 0; i < lights.size(); ++i)
    {
        auto light = lights.at(i);

        if (light->enabled)
        {
            shadows->clearShadowmap(lightIndex);

            if (shadows->getEnabled() && light->shadowsEnabled)
            {
                shadows->computeShadowsMatrix(*this, *light);

                for (Module* m : modules)
                {
                    if (m->getEnabled())
                        m->Render(*this, RenderPass::Shadow);
                }
            }

            lightIndex++;
            if (lightIndex >= MAX_ACTIVE_LIGHTS)
                        std::cerr << "Exceeding " << MAX_ACTIVE_LIGHTS << " active lights in the scene" << std::endl;
        }
    }

    if (shadows->getEnabled())
        shadows->bindShadowMaps();


    // Render to screen
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Setup screen dimensions
    glViewport(0, 0, windowWidth, windowHeight);

    // Each frame, reset color of each pixel to glClearColor and clear depth
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable backface culling
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    imgui->PreRender(*this);

    LightData emptyLight;
    emptyLight.ambientIntensity = 0.0f;
    emptyLight.diffuseIntensity = 0.0f;
    emptyLight.specularIntensity = 0.0f;

    for (auto shader : Resources::getShaders())
    {
        if (shader->needsLight)
        {
            shader->activate();

            int lightIndex = 0;
            for (size_t i = 0; i < lights.size(); ++i)
            {
                auto light = lights.at(i);
                if (light->enabled)
                {
                    shader->setLight(lightIndex, *light);

                    lightIndex++;
                    if (lightIndex >= MAX_ACTIVE_LIGHTS)
                        std::cerr << "Exceeding " << MAX_ACTIVE_LIGHTS << " active lights in the scene" << std::endl;
                }
            }
            for (; lightIndex < MAX_ACTIVE_LIGHTS; ++lightIndex)
            {
                shader->setLight(lightIndex, emptyLight);
            }
        }
    }

    for (Module* m : modules)
    {
        if (m->getEnabled())
            m->Render(*this, RenderPass::Color);
    }

    imgui->PostRender(*this);
}

void World::OnKey(int key, int action, int mods)
{
    if (imgui->wantCaptureKeyboard())
        return;

    if (key == GLFW_KEY_M && action == GLFW_PRESS)
    {
        imgui->setEnabled(!imgui->getEnabled());
        skipNextMouseDelta = true;
    }

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
        if (m->getEnabled())
        {
            m->OnKey(*this, key, action, mods);

            if (action == GLFW_RELEASE)
                m->OnKeyReleased(*this, key, mods);
            else if (action == GLFW_PRESS || action == GLFW_REPEAT)
                m->OnKeyPressed(*this, key, mods);
        }
    }
}

void World::OnMouseMoved(float x, float y)
{
    if (imgui->wantCaptureMouse())
    {
        lastMouseX = x;
        lastMouseY = y;
        return;
    }

    for (Module* m : modules)
    {
        if (m->getEnabled())
            m->OnMouseMoved(*this, x, y);
    }

    const float deltaX = x - lastMouseX;
    const float deltaY = y - lastMouseY;
    if (skipNextMouseDelta)
    {
        skipNextMouseDelta = false;
    }
    else
    {
        for (Module* m : modules)
        {
            if (m->getEnabled())
                m->OnMouseMovedDelta(*this, deltaX, deltaY);
        }
    }
    lastMouseX = x;
    lastMouseY = y;
}

void World::OnMousePressed(int button, int mods)
{
    if (imgui->wantCaptureMouse())
        return;

    for (Module* m : modules)
    {
        if (m->getEnabled())
            m->OnMousePressed(*this, button, mods);
    }
}

void World::OnMouseReleased(int button, int mods)
{
    if (imgui->wantCaptureMouse())
        return;

    for (Module* m : modules)
    {
        if (m->getEnabled())
            m->OnMouseReleased(*this, button, mods);
    }
}
