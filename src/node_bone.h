#pragma once
#include "material.h"
#include "mesh.h"
#include "node.h"
#include "resources.h"
#include "shader.h"
#include "texture.h"

/**
 * Member of the scene graph, renders a cylindrical bone between two joints
 *
 * @see SceneGraph
 */
class NodeBone : public Node
{
public:

    NodeBone()
    {

    }

    NodeBone(Material& material, Shader& shader)
    {
        this->material = &material;
        this->shader = &shader;
    }

    void setPoints(const glm::vec3& pointA, const glm::vec3& pointB)
    {


        glm::vec3 position = (pointA + pointB) / 2.0f;
        float distance = (pointA - pointB).length();

        transform = glm::mat4(1.0f);
        transform = glm::scale(transform, glm::vec3(distance/2.0f, radius/2.0f, radius/2.0f));
        transform = glm::translate(transform, position);
        //transform = glm::rotate(transform, )
      



    }


   

    virtual void render(World& world, RenderPass pass, const glm::mat4& matrixStack) override
    {
        if (material != nullptr && shader != nullptr)
        {
            if (pass == RenderPass::Color)
            {
                shader->activate();
                shader->setModelMatrix(matrixStack);
                shader->setMaterial(*material);
                Resources::useTexture(material->diffuseTexture, 0);
                Resources::useTexture(material->specularTexture, 1);
            }
            else if (pass == RenderPass::Shadow)
            {
                Resources::shadowCastShader.activate();
                Resources::shadowCastShader.setModelMatrix(matrixStack);
            }

            Resources::cylinder.draw();
        }
    }

    Material* material = nullptr;
    Shader* shader = nullptr;
    float radius = 1.0f;
};
