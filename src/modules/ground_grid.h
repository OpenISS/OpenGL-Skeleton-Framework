#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../module.h"
#include "../resources.h"
#include "../world.h"

class GroundGrid : public Module
{
public:

    virtual void Startup(World& world) 
    {
        grid.vertices.clear();

        for (int x = 0; x <= 128; x++)
        {
            Vertex start, end;
            start.position = glm::vec3(static_cast <float> (x) * Resources::unitSize, 0.0f, 0.0f);
            end.position = glm::vec3(static_cast <float> (x) * Resources::unitSize, 0.0f, 128.0f * Resources::unitSize);
            start.color = Resources::colorWhite;
            end.color = Resources::colorWhite;
            grid.vertices.push_back(start);
            grid.vertices.push_back(end);
        }

        for (int z = 0; z <= 128; z++)
        {
            Vertex start, end;
            start.position = glm::vec3(0.0, 0.0f, static_cast <float> (z) * Resources::unitSize);
            end.position = glm::vec3(128.0f * Resources::unitSize, 0.0f, static_cast <float> (z) * Resources::unitSize);
            start.color = Resources::colorWhite;
            end.color = Resources::colorWhite;
            grid.vertices.push_back(start);
            grid.vertices.push_back(end);
        }

        grid.setPolygonMode(GL_LINES);
        grid.setDrawingMode(DrawMode::VERTEX);
        grid.uploadBuffersToGPU();
    };

    virtual void Render(World& world)
    {
        Module::Render(world);

        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-64.0f * Resources::unitSize, 0.0f, -64.0f * Resources::unitSize));
        modelMatrix = world.sceneGraph->root.transform * modelMatrix; // Take world orientation into account

        Resources::basicShader.setModelMatrix(modelMatrix);
        Resources::basicShader.setColor(Resources::colorWhite);

        Resources::basicShader.activate();
        grid.draw();
    }

protected:

    Mesh grid;
};
