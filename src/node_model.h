#pragma once
#include "mesh.h"
#include "node.h"
#include "resources.h"
#include "shader.h"

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

    virtual void render(World& world, glm::mat4& matrixStack)
    {
        if (shader != NULL && mesh != NULL)
        {
            shader->setModelMatrix(matrixStack);
            shader->setColor(color);
            shader->activate();
            mesh->draw();
        }
    }

    Shader* shader = NULL;
    Mesh* mesh = NULL;
    glm::vec3 color = Resources::colorWhite;
};
