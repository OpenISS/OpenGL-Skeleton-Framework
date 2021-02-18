#pragma once
#include "mesh.h"
#include "modules/rendering_mode.h"
#include "node.h"
#include "node_model.h"
#include "resources.h"
#include "resources_alphabet.h"
#include "shader.h"
#include "world.h"

/**
 * Member of the scene graph, renders cubes that compose a character.
 * 
 * Note that not all characters are supported.
 * 
 * @see ResourcesAlphabet
 * @see SceneGraph
 */
class NodeCharacter : public Node
{
public:

    NodeCharacter(char character, Shader& shader, float scale = 1.0f)
    {
        this->scale = scale;
        this->shader = &shader;
        auto res = ResourcesAlphabet::getCubes(character);
        if (res != nullptr)
            cubes = res;
    }

    virtual void render(World& world, const glm::mat4& matrixStack) override
    {
        if (shader != nullptr)
        {
            world.renderingMode->SetupPolygonMode(renderMode);

            shader->setColor(color);
            shader->activate();

            // Render the transformed unit cubes that compose the current character
            for (auto transform : *cubes)
            {
                glm::mat4 cubeMatrix = glm::scale(matrixStack, glm::vec3(scale)) * transform;
                Resources::basicShader.setModelMatrix(cubeMatrix);
                Resources::unitCube.draw();
            }
        }
    }

    const std::vector<glm::mat4>* cubes = nullptr;
    Shader* shader = nullptr;
    glm::vec3 color = Resources::colorWhite;
    float scale = 1.0f;
    RenderMode renderMode = RenderMode::Triangle;
};
