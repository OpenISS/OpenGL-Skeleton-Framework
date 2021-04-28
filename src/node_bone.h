#pragma once
#include <glm/gtx/quaternion.hpp>
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

    NodeBone(Material& material, Shader& shader, const glm::vec3& pointA, const glm::vec3& pointB, float radius)
    {
        this->material = &material;
        this->shader = &shader;
        setPoints(pointA, pointB, radius);
    }

    void setPoints(const glm::vec3& pointA, const glm::vec3& pointB, float radius)
    {
        glm::vec3 position = (pointA + pointB) / 2.0f;
        glm::vec3 dir = pointB - pointA;
        float distance = glm::length(dir);
        dir = glm::normalize(dir);
        glm::quat rotation = glm::rotation(glm::vec3(1.0f, 0.0f, 0.0f), dir);

        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, position);
        transform *= glm::toMat4(rotation);
        transform = glm::scale(transform, glm::vec3(distance, radius / 2.0f, radius / 2.0f));
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
                Resources::useTexture(material->diffuseTexture, TEXTURE_SLOT_DIFFUSE);
                Resources::useTexture(material->specularTexture, TEXTURE_SLOT_SPECULAR);
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
};
