#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../module.h"
#include "../resources.h"
#include "../world.h"

class OriginAxis : public Module
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

        // A bit raised to avoid Z-fighting with the grid
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.02f * Resources::unitSize, 0.0f));
        modelMatrix = world.sceneGraph->root.transform * modelMatrix; // Take world orientation into account

        Resources::basicShader.setModelMatrix(modelMatrix);
        Resources::basicShader.setColor(Resources::colorWhite);

        Resources::basicShader.activate();
        axis.draw();
    }

protected:

    Mesh axis;
};
