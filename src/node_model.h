#pragma once
#include "mesh.h"
#include "node.h"
#include "resources.h"
#include "shader.h"
#include "texture.h"

/**
 * Member of the scene graph, rendered using its associated mesh and shader.
 * 
 * @see SceneGraph
 */
class NodeModel : public Node
{
public:

    NodeModel()
    {

    }

    NodeModel(Shader& shader, Mesh& mesh)
    {
        this->shader = &shader;
        this->mesh = &mesh;
    }

    virtual void render(World& world, RenderPass pass, const glm::mat4& matrixStack) override
    {
        if (shader != nullptr && mesh != nullptr)
        {
            if (pass == RenderPass::Color)
            {
                shader->activate();
                shader->setModelMatrix(matrixStack);
                shader->setColor(color);
                if (texture == nullptr)
                    Resources::whiteTexture.useTexture();
                else
                    texture->useTexture();
            }
            else if (pass == RenderPass::Shadow)
            {
                Resources::shadowCastShader.activate();
                Resources::shadowCastShader.setModelMatrix(matrixStack);
            }

            mesh->draw();
        }
    }

    Shader* shader = nullptr;
    Mesh* mesh = nullptr;
    Texture* texture = nullptr;
    glm::vec3 color = Resources::colorWhite;
};
