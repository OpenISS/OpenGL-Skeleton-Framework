#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../module.h"
#include "../resources.h"
#include "../world.h"

/**
 * Tests the Mesh class DrawMode::VERTEX codepath using the simple quad mesh Resources::quad.
 * Displays a simple spinning cube.
 * 
 * Backface culling should have visible effect if enabled.
 * 
 * @see DrawMode::Vertex
 */
class TestVertexDrawing : public Module
{
public:

    MODULE_CONSTRUCTOR(TestVertexDrawing)

    void Update(World& world, float deltaSeconds) override
    {
        Module::Update(world, deltaSeconds);

        angle += anglesPerSecond * deltaSeconds;
    }

    void Render(World& world, RenderPass pass) override
    {
        Module::Render(world, pass);

        // Push up and back from camera + rotate around itself over time
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.75f, -6.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

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

        Resources::quad.draw();
    }

protected:

    float angle = 0.0f;
    float anglesPerSecond = 30.0f;
};
