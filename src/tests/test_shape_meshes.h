#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../module.h"
#include "../resources.h"
#include "../world.h"

class TestShapeMeshes : public Module
{
public:

    MODULE_CONSTRUCTOR(TestShapeMeshes)

    void Startup(World &world) override
    {
        texture = Texture("assets/fragile.jpg");
        texture.loadTexture();
    }

    void Render(World& world, RenderPass pass) override
    {
        Module::Render(world, pass);

        glm::vec3 positions[] = {{-7.5f, 0.0f, 0.0f}, {-4.5f, 0.0f, 0.0f}, {-1.5f, 0.0f, 0.0f}, {1.5f, 0.0f, 0.0f}, {4.5f, 0.0f, 0.0f}, {7.5f, 0.0f, 0.0f}};
        Mesh* meshes[] = {&Resources::quad, &Resources::unitCube, &Resources::sphere, &Resources::cylinder, &Resources::cone, &Resources::halfCylinder};

        for (int i = 0; i < 6; ++i)
        {
            glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), positions[i]);

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
            meshes[i]->draw();
        }


        glm::mat4 modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(30.0f));

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
        Resources::inverseCube.draw();
    }

protected:

    Texture texture;
};
