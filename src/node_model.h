#pragma once
#include "material.h"
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

    NodeModel(Mesh& mesh, Material& material, Shader& shader)
    {
        this->mesh = &mesh;
        this->material = &material;
        this->shader = &shader;
    }

    virtual void render(World& world, RenderPass pass, const glm::mat4& matrixStack) override
    {
        if (mesh != nullptr && material != nullptr && shader != nullptr)
        {
            if (pass == RenderPass::Color)
            {
                shader->activate();
                shader->setModelMatrix(matrixStack);
                shader->setMaterial(*material);
                Resources::useTexture(material->diffuseTexture, TEXTURE_SLOT_DIFFUSE);
                Resources::useTexture(material->specularTexture, TEXTURE_SLOT_SPECULAR);
            }
            else if (pass == RenderPass::Shadow)
            {
                Resources::shadowCastShader.activate();
                Resources::shadowCastShader.setModelMatrix(matrixStack);
            }

            mesh->draw();
        }
    }

    Mesh* mesh = nullptr;
    Material* material = nullptr;
    Shader* shader = nullptr;
    RenderMode renderMode = RenderMode::Triangle;
};
