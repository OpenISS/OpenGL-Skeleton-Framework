#pragma once
#include "mesh.h"
#include "node.h"
#include "node_model.h"
#include "modules/rendering_mode.h"
#include "resources.h"
#include "resources_alphabet.h"
#include "shader.h"
#include "world.h"

class NodeCharacter : public Node
{
public:
    const std::vector<glm::mat4>* cubes;
    Shader* shader = nullptr;
    glm::vec3 color = Resources::colorWhite;
    float scale;
    RenderMode renderMode = RenderMode::Triangle;

    NodeCharacter(char letter, Shader& shader, float scale = 1.0f)
    {
        this->scale = scale;
        this->shader = &shader;
        auto res = ResourcesAlphabet::getCubes(letter);
        if (res != nullptr)
            cubes = res;
    }

    virtual void render(World& world, glm::mat4& matrixStack)
    {
        if (shader != NULL)
        {
            world.renderingMode->SetupPolygonMode(renderMode);

            shader->setColor(color);
            shader->activate();
            
            for (auto transform : *cubes)
            {
                glm::mat4 cubeMatrix = glm::scale(matrixStack, glm::vec3(scale)) * transform;
                Resources::basicShader.setModelMatrix(cubeMatrix);
                Resources::unitCube.draw();
            }
        }
    }
};
