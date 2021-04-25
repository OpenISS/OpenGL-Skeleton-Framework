#pragma once
#include "material.h"
#include "mesh.h"
#include "modules/rendering_mode.h"
#include "node.h"
#include "node_model.h"
#include "resources.h"
#include "resources_alphabet.h"
#include "shader.h"
#include "texture.h"
#include "world.h"

/**
 * Member of the scene graph, renders cubes that compose a character.
 * 
 * Note that not all characters are supported.
 * 
 * @see ResourcesAlphabet
 * @see SceneGraph
 */
class NodeCharacter : public NodeModel
{
public:

    NodeCharacter(char character, Material& material, Shader& shader, float scale = 1.0f)
    {
        this->scale = scale;
        this->material = &material;
        this->shader = &shader;
        this->mesh = &Resources::unitCube;
        auto res = ResourcesAlphabet::getCubes(character);
        if (res != nullptr)
            cubes = res;
    }

    virtual void render(World& world, RenderPass pass, const glm::mat4& matrixStack) override
    {
        if (material != nullptr && shader != nullptr && cubes != nullptr)
        {
            world.renderingMode->SetupPolygonMode(renderMode);

            if (pass == RenderPass::Color)
            {
                shader->activate();
                shader->setMaterial(*material);
                Resources::useTexture(material->diffuseTexture, 0);
                Resources::useTexture(material->specularTexture, 1);
            }
            else if (pass == RenderPass::Shadow)
            {
                Resources::shadowCastShader.activate();
            }

            // Render the transformed unit cubes that compose the current character
            for (auto transform : *cubes)
            {
                glm::mat4 cubeMatrix = glm::scale(matrixStack, glm::vec3(scale)) * transform;
                if (pass == RenderPass::Color)
                    shader->setModelMatrix(cubeMatrix);
                else if (pass == RenderPass::Shadow)
                    Resources::shadowCastShader.setModelMatrix(cubeMatrix);
                mesh->draw();
            }
        }
    }

    float scale = 1.0f;
    const std::vector<glm::mat4>* cubes = nullptr;
};
