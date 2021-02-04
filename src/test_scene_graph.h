#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "color.h"
#include "module.h"
#include "node_model.h"
#include "resources.h"
#include "world.h"

class TestSceneGraph : public Module
{
public:

    virtual void Startup(World& world)
    {
        Module::Startup(world);

        cube1 = new NodeModel(Resources::basicShader, Resources::unitCube);
        cube2 = new NodeModel(Resources::basicShader, Resources::unitCube);
        cube3 = new NodeModel(Resources::basicShader, Resources::unitCube);
        cube4 = new NodeModel(Resources::basicShader, Resources::unitCube);

        cube1->color = hexToFloatRGB(0xfaf489);
        cube2->color = hexToFloatRGB(0xfaf489);
        cube3->color = hexToFloatRGB(0xadebf7);
        cube4->color = hexToFloatRGB(0xadebf7);

        world.sceneGraph->root.addChild(*cube1);
        world.sceneGraph->root.addChild(*cube2);
        cube1->addChild(*cube3);
        cube2->addChild(*cube4);

        cube1->transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.5f));
        cube2->transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.5f));
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

        world.sceneGraph->root.transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -6.0f));
        world.sceneGraph->root.transform = glm::rotate(world.sceneGraph->root.transform, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

        cube3->transform = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f)); //rotates in place
        cube3->transform = glm::translate(cube3->transform, glm::vec3(0.0f, 0.0f, 1.5f)); //gives radius of rotation

        cube4->transform = glm::rotate(glm::mat4(1.0f), glm::radians(-angle), glm::vec3(1.0f, 0.0f, 0.0f));
        cube4->transform = glm::translate(cube4->transform, glm::vec3(0.0f, 0.0f, -1.5f));
    }

    virtual void Render(World& world)
    {
        Module::Render(world);

        glm::mat4 viewMatrix = glm::mat4(1.0f);

        glm::mat4 projectionMatrix = glm::perspective(
            glm::radians(45.0f), // field of view in degrees
            world.windowAspectRatio,
            0.01f, 100.0f); // near and far (near > 0)

        Resources::basicShader.setViewMatrix(viewMatrix);
        Resources::basicShader.setProjectionMatrix(projectionMatrix);
    }

protected:

    NodeModel* cube1;
    NodeModel* cube2;
    NodeModel* cube3;
    NodeModel* cube4;

    float angle;
    float anglesPerSecond = 60.0f;
};
