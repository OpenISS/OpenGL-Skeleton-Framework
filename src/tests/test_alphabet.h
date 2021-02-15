#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../module.h"
#include "../resources_alphabet.h"
#include "../resources.h"
#include "../world.h"

class TestAlphabet : public Module
{
public:

    virtual void Startup(World& world)
    {
        auto res = ResourcesAlphabet::getCubes('M');
        if (res != nullptr)
            cubes = *res;
    }

    virtual void Update(World& world, float deltaSeconds)
    {
        Module::Update(world, deltaSeconds);

        angle += anglesPerSecond * deltaSeconds;
    }

    virtual void Render(World& world)
    {
        Module::Render(world);

        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, -6.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

        Resources::basicShader.setColor(Resources::colorWhite);

        Resources::basicShader.activate();

        for (auto transform : cubes)
        {
            glm::mat4 cubeMatrix = modelMatrix * transform;
            Resources::basicShader.setModelMatrix(cubeMatrix);
            Resources::unitCube.draw();
        }
    }

    virtual void OnKey(World& world, int key, int action, int mods)
    {
        Module::OnKey(world, key, action, mods);

        if (action == GLFW_PRESS)
        {
            bool isDigit = key >= '0' && key <= '9';
            bool isLetter = key >= 'A' && key <= 'Z';
            if (isDigit || isLetter)
            {
                auto res = ResourcesAlphabet::getCubes(static_cast<char>(key));
                if (res != nullptr)
                    cubes = *res;
            }
        }
    }

protected:

    std::vector<glm::mat4> cubes;

    float angle;
    float anglesPerSecond = 180.0f;
};
