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
        crateTexture = Texture("assets/fragile.jpg", GL_RGB);
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
        }
        else if (pass == RenderPass::Shadow)
        {
            Resources::shadowCastShader.activate();
            Resources::shadowCastShader.setModelMatrix(modelMatrix);
        }
        crateTexture.useTexture();
        Resources::unitCube.draw();
    }

protected:

    float angle = 0.0f, anglesPerSecond = 180.0f;
    Texture crateTexture;
};
