#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../color.h"
#include "../module.h"
#include "../node_character.h"
#include "../node_model.h"
#include "../resources.h"
#include "../world.h"

/**
 * Tests the SceneGraph hierarchy system.
 * Displays complex circular motion thanks to a nested hierarchy.
 * 
 * @see NodeModel
 * @see SceneGraph
 */
class TestSceneGraph : public Module
{
public:

    MODULE_CONSTRUCTOR(TestSceneGraph)

    void Startup(World& world) override
    {
        Module::Startup(world);

        // Hierarchy and movement:
        // * localRoot (rotates around itself)
        //     * cube1 (no local motion)
        //         * cube3 (rotates in a circle around local origin)
        //     * cube2 (no local motion)
        //         * cube4 (rotates in a circle around local origin)
        //     * letter1 (no local motion)
        //     * letter2 (no local motion)
        //     * letter3 (no local motion)

        localRoot = new Node();

        cube1 = new NodeModel(Resources::basicShader, Resources::unitCube);
        cube2 = new NodeModel(Resources::basicShader, Resources::unitCube);
        cube3 = new NodeModel(Resources::basicShader, Resources::unitCube);
        cube4 = new NodeModel(Resources::basicShader, Resources::unitCube);

        letter1 = new NodeCharacter('M', Resources::basicShader, 2.0f);
        letter2 = new NodeCharacter('N', Resources::basicShader, 2.0f);
        letter3 = new NodeCharacter('P', Resources::basicShader, 2.0f);

        const glm::vec3 yellow = hexToFloatRGB(0xfaf489);
        const glm::vec3 blue   = hexToFloatRGB(0xadebf7);
        cube1->color = yellow;
        cube2->color = yellow;
        cube3->color = blue;
        cube4->color = blue;

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

        setEnabled(enabled);
    }

    void Shutdown(World& world) override
    {
        world.sceneGraph->removeChild(*localRoot);
        delete localRoot; // Recursively deletes all its children
    }

    void setEnabled(bool enabled) override
    {
        this->enabled = enabled;
        localRoot->visible = enabled;
    }

    void Update(World& world, float deltaSeconds) override
    {
        Module::Update(world, deltaSeconds);

        angle += anglesPerSecond * deltaSeconds;

        localRoot->transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -6.0f)); // Pushes back from origin
        localRoot->transform = glm::rotate(localRoot->transform, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotates around itself

        cube3->transform = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotates in place
        cube3->transform = glm::translate(cube3->transform, glm::vec3(0.0f, 0.0f, 1.5f)); // Gives it a radius of rotation

        cube4->transform = glm::rotate(glm::mat4(1.0f), glm::radians(-angle), glm::vec3(1.0f, 0.0f, 0.0f));
        cube4->transform = glm::translate(cube4->transform, glm::vec3(0.0f, 0.0f, -1.5f));
    }

protected:

    Node* localRoot = nullptr;
    NodeModel* cube1 = nullptr;
    NodeModel* cube2 = nullptr;
    NodeModel* cube3 = nullptr;
    NodeModel* cube4 = nullptr;
    NodeCharacter* letter1 = nullptr;
    NodeCharacter* letter2 = nullptr;
    NodeCharacter* letter3 = nullptr;

    float angle = 0.0f;
    float anglesPerSecond = 60.0f;
};
