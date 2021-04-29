#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../module.h"
#include "../resources_alphabet.h"
#include "../resources.h"
#include "../world.h"

/**
 * Tests ResourcesAlphabet's import and parsing of the character model data.
 * Displays a spinning character composed of transformed unit cubes.
 * Press any key to display the corresponding character (if its model exists).
 * 
 * @see ResourcesAlphabet::getCubes()
 */
class TestAlphabet : public Module
{
public:

    MODULE_CONSTRUCTOR(TestAlphabet)

    void Startup(World& world) override
    {
        auto res = ResourcesAlphabet::getCubes('M');
        if (res != nullptr)
            cubes = *res;
    }

    void Update(World& world, float deltaSeconds) override
    {
        Module::Update(world, deltaSeconds);

        angle += anglesPerSecond * deltaSeconds;
    }

    void Render(World& world, RenderPass pass) override
    {
        Module::Render(world, pass);

        // Push back and down + rotate around itself over time
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, -6.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

        if (pass == RenderPass::Color)
        {
            Resources::basicShader.activate();
            Resources::basicShader.setColor(Resources::colorWhite);
        }
        else if (pass == RenderPass::Shadow)
        {
            Resources::shadowCastShader.activate();
        }


        // Render the transformed models that compose the current character
        for (auto transform : cubes)
        {
            glm::mat4 cubeMatrix = modelMatrix * transform;
            if (pass == RenderPass::Color)
                Resources::basicShader.setModelMatrix(cubeMatrix);
            else if (pass == RenderPass::Shadow)
                Resources::shadowCastShader.setModelMatrix(cubeMatrix);
            Resources::unitCube.draw();
        }
    }

    void OnKey(World& world, int key, int action, int mods) override
    {
        Module::OnKey(world, key, action, mods);

        if (action == GLFW_PRESS)
        {
            bool isDigit = key >= '0' && key <= '9';
            bool isLetter = key >= 'A' && key <= 'Z';
            if (isDigit || isLetter) // Only process alphanumerical keypresses
            {
                auto resCubes = ResourcesAlphabet::getCubes(static_cast<char>(key));
                auto resSpheres = ResourcesAlphabet::getSpheres(static_cast<char>(key));
                if (resCubes != nullptr && resSpheres != nullptr) // Only proceed if this character has a defined model
                {
                    // Merge cubes and spheres
                    cubes = *resCubes;
                    cubes.insert(cubes.end(), resSpheres->begin(), resSpheres->end());
                }
            }
        }
    }

protected:

    std::vector<glm::mat4> cubes;

    float angle = 0.0f;
    float anglesPerSecond = 180.0f;
};
