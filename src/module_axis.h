#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "module.h"
#include "resources.h"
#include "world.h"

class ModuleAxis : public Module
{
public:
    virtual void Startup(World& world)
    {

        axis.vertices.clear();

        Vertex center, x, y, z;
        center.position = glm::vec3(0.0f, 0.0f, 0.0f);
        x.position = glm::vec3(Resources::unitSize * 7.0f, 0.0f, 0.0f);
        y.position = glm::vec3(0.0f, Resources::unitSize * 7.0f, 0.0f);
        z.position = glm::vec3(0.0f, 0.0f, Resources::unitSize * 7.0f);

        x.color = glm::vec3(1.0f, 0.0f, 0.0f);
        y.color = glm::vec3(0.0f, 1.0f, 0.0f);
        z.color = glm::vec3(0.0f, 0.0f, 1.0f);

        center.color = x.color;
        axis.vertices.push_back(center);
        axis.vertices.push_back(x);
        center.color = y.color;
        axis.vertices.push_back(center);
        axis.vertices.push_back(y);
        center.color = z.color;
        axis.vertices.push_back(center);
        axis.vertices.push_back(z);

        axis.setPolygonMode(GL_LINES);
        axis.setDrawingMode(DrawMode::VERTEX);
        axis.createGPUBuffers();

    };


    virtual void Render(World& world)
    {
        Module::Render(world);

        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 1.0f, -6.0f));

        glm::mat4 viewMatrix = glm::mat4(1.0f);

        glm::mat4 projectionMatrix = glm::perspective(
            glm::radians(45.0f), // field of view in degrees
            world.windowAspectRatio,
            0.01f, 100.0f); // near and far (near > 0)

        Resources::basicShader.setModelMatrix(modelMatrix);
        Resources::basicShader.setViewMatrix(viewMatrix);
        Resources::basicShader.setProjectionMatrix(projectionMatrix);
        Resources::basicShader.setColor(Resources::colorWhite);

        Resources::basicShader.activate();
        axis.draw();
    }

protected:
    Mesh axis;
};
