#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../module.h"
#include "../resources.h"
#include "../world.h"

class TestUnitCube : public Module
{
public:

    void Update(World& world, float deltaSeconds) override
    {
        Module::Update(world, deltaSeconds);

        angle += anglesPerSecond * deltaSeconds;
    }

    void Render(World& world) override
    {
        Module::Render(world);

        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -6.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

        Resources::basicShader.setModelMatrix(modelMatrix);
        Resources::basicShader.setColor(Resources::colorWhite);

        Resources::basicShader.activate();
        Resources::unitCube.draw();
    }

protected:

    float angle;
    float anglesPerSecond = 180.0f;
};
