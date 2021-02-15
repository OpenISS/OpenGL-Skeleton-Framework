#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../color.h"
#include "../module.h"
#include "../node_character.h"
#include "../node_model.h"
#include "../resources.h"
#include "../world.h"

class TestSceneGraph : public Module
{
public:

    virtual void Startup(World& world)
    {
        Module::Startup(world);

        localRoot = new Node();

        cube1 = new NodeModel(Resources::basicShader, Resources::unitCube);
        cube2 = new NodeModel(Resources::basicShader, Resources::unitCube);
        cube3 = new NodeModel(Resources::basicShader, Resources::unitCube);
        cube4 = new NodeModel(Resources::basicShader, Resources::unitCube);

        letter1 = new NodeCharacter('M', Resources::basicShader, 2.0f);
        letter2 = new NodeCharacter('N', Resources::basicShader, 2.0f);
        letter3 = new NodeCharacter('P', Resources::basicShader, 2.0f);

        cube1->color = hexToFloatRGB(0xfaf489);
        cube2->color = hexToFloatRGB(0xfaf489);
        cube3->color = hexToFloatRGB(0xadebf7);
        cube4->color = hexToFloatRGB(0xadebf7);

        world.sceneGraph->addChild(*localRoot);
        localRoot->addChild(*cube1);
        localRoot->addChild(*cube2);
        cube1->addChild(*cube3);
        cube2->addChild(*cube4);

        cube1->transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.5f));
        cube2->transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.5f));

        localRoot->addChild(*letter1);
        localRoot->addChild(*letter2);
        localRoot->addChild(*letter3);

        letter1->transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f,  2.5f));
        letter2->transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f,  3.5f));
        letter3->transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f,  4.5f));
    }

    virtual void Shutdown(World& world)
    {
        world.sceneGraph->removeChild(*localRoot);
        delete localRoot;
    }

    virtual void Update(World& world, float deltaSeconds)
    {
        Module::Update(world, deltaSeconds);

        angle += anglesPerSecond * deltaSeconds;

        localRoot->transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -6.0f));
        localRoot->transform = glm::rotate(localRoot->transform, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

        cube3->transform = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotates in place
        cube3->transform = glm::translate(cube3->transform, glm::vec3(0.0f, 0.0f, 1.5f)); // Gives it a radius of rotation

        cube4->transform = glm::rotate(glm::mat4(1.0f), glm::radians(-angle), glm::vec3(1.0f, 0.0f, 0.0f));
        cube4->transform = glm::translate(cube4->transform, glm::vec3(0.0f, 0.0f, -1.5f));
    }

protected:

    Node* localRoot;
    NodeModel* cube1;
    NodeModel* cube2;
    NodeModel* cube3;
    NodeModel* cube4;
    NodeCharacter* letter1;
    NodeCharacter* letter2;
    NodeCharacter* letter3;

    float angle;
    float anglesPerSecond = 60.0f;
};
