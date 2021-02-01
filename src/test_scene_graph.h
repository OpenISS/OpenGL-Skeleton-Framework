#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "module.h"
#include "node_model.h"
#include "world.h"

class TestSceneGraph : public Module
{
public:

    virtual void Startup(World& world)
    {
        Module::Startup(world);

        cube1 = new NodeModel(world.basicShader, world.unitCube);
        cube2 = new NodeModel(world.basicShader, world.unitCube);
        cube3 = new NodeModel(world.basicShader, world.unitCube);
        cube4 = new NodeModel(world.basicShader, world.unitCube);

        world.sceneGraph->root.addChild(*cube1);
        world.sceneGraph->root.addChild(*cube2);
        cube1->addChild(*cube3);
        cube2->addChild(*cube4);

        cube1->transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 3.0f));
        cube2->transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    }

    virtual void Shutdown(World& world)
    {
        delete cube1;
        delete cube2;
        delete cube3;
        delete cube4;
    }

    virtual void Update(World& world, float deltaSeconds)
    {
        Module::Update(world, deltaSeconds);

        angle += anglesPerSecond * deltaSeconds;

        world.sceneGraph->root.transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
        world.sceneGraph->root.transform = glm::rotate(world.sceneGraph->root.transform, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

        cube3->transform = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
        cube3->transform = glm::translate(cube3->transform, glm::vec3(0.0f, 0.0f, 3.0f));

        cube4->transform = glm::rotate(glm::mat4(1.0f), glm::radians(-angle), glm::vec3(1.0f, 0.0f, 0.0f));
        cube4->transform = glm::translate(cube4->transform, glm::vec3(0.0f, 0.0f, -3.0f));
    }

    virtual void Render(World& world)
    {
        Module::Render(world);

        glm::mat4 viewMatrix = glm::mat4(1.0f);

        glm::mat4 projectionMatrix = glm::perspective(
            glm::radians(45.0f), // field of view in degrees
            world.windowAspectRatio,
            0.01f, 100.0f); // near and far (near > 0)

        world.basicShader.setViewMatrix(viewMatrix);
        world.basicShader.setProjectionMatrix(projectionMatrix);
    }

protected:

    NodeModel* cube1;
    NodeModel* cube2;
    NodeModel* cube3;
    NodeModel* cube4;

    float angle;
    float anglesPerSecond = 4.0f;
};
