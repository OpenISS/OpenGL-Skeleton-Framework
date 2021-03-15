#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../module.h"
#include "../resources.h"
#include "../world.h"

/**
 * This is SunRay's hello world.
 * Displays a simple spinning cube.
 * 
 * @see Mesh
 * @see Module
 * @see Resources::basicShader
 * @see Resources::unitCube
 * @see Shader
 */
class TestUnitCube : public Module
{
public:

    MODULE_CONSTRUCTOR(TestUnitCube)

    void Update(World& world, float deltaSeconds) override
    {
        Module::Update(world, deltaSeconds);

        angle += anglesPerSecond * deltaSeconds;
    }

    void Render(World& world, RenderPass pass) override
    {
        Module::Render(world, pass);

        // Push back from camera + rotate around itself over time
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -6.0f));
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

        Resources::unitCube.draw();
    }

protected:

    float angle = 0.0f;
    float anglesPerSecond = 180.0f;
};
