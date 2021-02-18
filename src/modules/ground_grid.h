#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../module.h"
#include "../resources.h"
#include "../world.h"

/**
 * Grid class
 * 
 * Each line is set to a constant unit size (0.25f), set in resources
 * 128x128 lines set along x and z axis
 * Creation and rendering of grid
 */
class GroundGrid : public Module
{
public:
    
    void Startup(World& world) override
    {
        grid.vertices.clear();

        // Loop for creating 128 lines along x axis
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

        // Loop for creating 128 lines along z axis
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
  
    void Render(World& world) override
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
