#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../loader_obj.h"
#include "../mesh.h"
#include "../module.h"
#include "../resources.h"
#include "../world.h"

class TestLoaderObj : public Module
{
public:

    void Startup(World& world) override
    {
        loader.loadFile(mesh, "teapot.obj");
        if (loader.getStatus() == LoaderOBJ::Status::SUCCESS)
            mesh.uploadBuffersToGPU();
    }

    void Render(World& world) override
    {
        Module::Render(world);

        // Push back from camera + rotate around itself over time
        float angle = world.getTime() * anglesPerSecond;
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -6.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

        Resources::basicShader.activate();
        Resources::basicShader.setModelMatrix(modelMatrix);
        Resources::basicShader.setColor(Resources::colorWhite);

        glDisable(GL_CULL_FACE);
        mesh.draw();
    }

protected:

    Mesh mesh;
    LoaderOBJ loader;

    float anglesPerSecond = 180.0f;
};
