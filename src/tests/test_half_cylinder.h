#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../module.h"
#include "../resources.h"
#include "../texture.h"
#include "../world.h"

class TestHalfCylinder : public Module
{
public:

    MODULE_CONSTRUCTOR(TestHalfCylinder)

    void Startup(World &world) override
    {
        texture = Texture("assets/fragile.jpg");
        texture.loadTexture();
    }

    void Render(World& world, RenderPass pass) override
    {
        Module::Render(world, pass);

        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.25f * 0.5f, -6.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f, 1.0f, 1.0f));

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

        texture.useTexture();
        Resources::halfCylinder.draw();
    }

protected:

    Texture texture;
};
