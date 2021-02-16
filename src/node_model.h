#pragma once
#include "mesh.h"
#include "node.h"
#include "resources.h"
#include "shader.h"

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

    virtual void render(World& world, const glm::mat4& matrixStack) override
    {
        if (shader != nullptr && mesh != nullptr)
        {
            shader->setModelMatrix(matrixStack);
            shader->setColor(color);
            shader->activate();
            mesh->draw();
        }
    }

    Shader* shader = nullptr;
    Mesh* mesh = nullptr;
    glm::vec3 color = Resources::colorWhite;
};
