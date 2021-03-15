#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../module.h"
#include "../resources.h"
#include "../world.h"

/**
 * OriginAxis class
 *
 * Each line are for each world direction (x,y,z), where each line is 7 units long
 * Width size set to the consatnt unitsize (0.25f) same as the grid
 * Creation and rendering of OriginAxis
 */
class OriginAxis : public Module
{
public:

    MODULE_CONSTRUCTOR(OriginAxis)

    void Startup(World& world) override
    {
        axis.vertices.clear();

        // Coordinates for OriginAxis
        Vertex center, x, y, z;
        center.position = glm::vec3(0.0f, 0.0f, 0.0f);
        x.position = glm::vec3(Resources::unitSize * 7.0f, 0.0f, 0.0f);
        y.position = glm::vec3(0.0f, Resources::unitSize * 7.0f, 0.0f);
        z.position = glm::vec3(0.0f, 0.0f, Resources::unitSize * 7.0f);

        // Colour for OriginAxis
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
        axis.uploadBuffersToGPU();
    };

    void Render(World& world, RenderPass pass) override
    {
        Module::Render(world, pass);

        // A bit raised to avoid Z-fighting with the grid
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.02f * Resources::unitSize, 0.0f));
        modelMatrix = world.sceneGraph->root.transform * modelMatrix; // Take world orientation into account

        if (pass == RenderPass::Color)
        {
            Resources::basicShader.activate();
            Resources::basicShader.setModelMatrix(modelMatrix);
            Resources::basicShader.setColor(Resources::colorWhite);
        }
        else if (pass == RenderPass::Shadow)
        {
            Resources::shadowCastShader.activate();
            Resources::shadowCastShader.setModelMatrix(modelMatrix);
        }

        axis.draw();
    }

protected:

    Mesh axis;
};
