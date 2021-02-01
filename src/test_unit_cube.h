#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "module.h"
#include "resources.h"
#include "world.h"

class TestUnitCube : public Module
{
public:

    virtual void Update(World& world, float deltaSeconds)
    {
        Module::Update(world, deltaSeconds);

        angle += anglesPerSecond * deltaSeconds;
    }

    virtual void Render(World& world)
    {
        Module::Render(world);

        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1.01f, 1.01f, 1.01f));

        glm::mat4 viewMatrix = glm::mat4(1.0f);

        glm::mat4 projectionMatrix = glm::perspective(
            glm::radians(45.0f), // field of view in degrees
            world.windowAspectRatio,
            0.01f, 100.0f); // near and far (near > 0)

        Resources::basicShader.setModelMatrix(modelMatrix);
        Resources::basicShader.setViewMatrix(viewMatrix);
        Resources::basicShader.setProjectionMatrix(projectionMatrix);
        Resources::basicShader.setColor(glm::vec3(1.0f, 1.0f, 1.0f));

        Resources::basicShader.activate();
        Resources::unitCube.draw();
    }

protected:

    float angle;
    float anglesPerSecond = 12.0f;
};
