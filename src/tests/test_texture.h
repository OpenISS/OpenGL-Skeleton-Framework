#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../module.h"
#include "../resources.h"
#include "../world.h"
#include "../texture.h"

class TestTexture : public Module
{
public:

    MODULE_CONSTRUCTOR(TestTexture)

    void Startup(World &world) override {
        crateTexture = Texture("assets/fragile.jpg");
        crateTexture.loadTexture();
    }

    void Update(World& world, float deltaSeconds) override
    {
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
            Resources::basicTexturedShader.activate();
            Resources::basicTexturedShader.setModelMatrix(modelMatrix);
            Resources::basicTexturedShader.setColor(Resources::colorWhite);
            Resources::basicTexturedShader.setUVScale(glm::vec2(1.0f));
        }
        else if (pass == RenderPass::Shadow)
        {
            Resources::shadowCastShader.activate();
            Resources::shadowCastShader.setModelMatrix(modelMatrix);
        }

        crateTexture.useTexture();
        Resources::unitCube.draw();

        // Demonstrates uvScale
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -12.0f));
        if (pass == RenderPass::Color)
        {
            Resources::basicTexturedShader.setModelMatrix(modelMatrix);
            Resources::basicTexturedShader.setUVScale(glm::vec2(2.0f));
        }
        else if (pass == RenderPass::Shadow)
        {
            Resources::shadowCastShader.setModelMatrix(modelMatrix);
        }
        Resources::unitCube.draw();
        if (pass == RenderPass::Color)
            Resources::basicTexturedShader.setUVScale(glm::vec2(1.0f));
    }

protected:

    float angle = 0.0f, anglesPerSecond = 180.0f;
    Texture crateTexture;
};
