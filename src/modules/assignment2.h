#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../color.h"
#include "../light_data.h"
#include "../material.h"
#include "../module.h"
#include "../node_character.h"
#include "../node_model.h"
#include "../resources.h"
#include "../texture.h"
#include "../world.h"

/**
 * Implements Programming Assignment 1 together with modules:
 * * FPSCamera
 * * GroundGrid
 * * OriginAxis
 * * SceneGraph
 * * WorldOrientation
 *
 * @see Module
 * @see World
 * @see FPSCamera
 * @see GroundGrid
 * @see OriginAxis
 * @see SceneGraph
 * @see WorldOrientation
 */
class Assignment2 : public Module
{
public:

    MODULE_CONSTRUCTOR(Assignment2)

        /**
         * Sets up model hierarchy
         *
         * @see Node
         * @see NodeCharacter
         */
        void Startup(World& world) override
    {
        Module::Startup(world);

        const float scale = Resources::unitSize * 3.0f; // Character scale
        const float interval_degrees = 10.0f; // Character spacing along arc (in degrees)
        const float radius = Resources::unitSize * 64.0f; // Circle radius, matches grid size

        // Hierarchy:
        // * root (Node) (rotated by WorldOrientation module)
        //     * localRoot (Node) (not transformed)
        //         * andrew (Node) (translated, rotated, scaled)
        //             * A (NodeCharacter)
        //             * H (NodeCharacter)
        //             * 4 (NodeCharacter)
        //             * 1 (NodeCharacter)
        //         * mark
        //             * M (NodeCharacter)
        //             * B (NodeCharacter)
        //             * 4 (NodeCharacter)
        //             * 7 (NodeCharacter)
        //         * nicholas (Node)
        //             ...
        //         * paul (Node)
        //             ...
        //         * fifth (Node)
        //             ...

        andrew = new Node();
        setCharacters(*andrew, "AH41", scale);

        mark = new Node();
        setCharacters(*mark, "MB47", scale);

        nicholas = new Node();
        setCharacters(*nicholas, "NA40", scale);

        paul = new Node();
        setCharacters(*paul, "PV41", scale);

        fifth = new Node();
        setCharacters(*fifth, "AP00", scale);

        localRoot = new Node();
        world.sceneGraph->addChild(*localRoot);
        localRoot->addChild(*andrew);
        localRoot->addChild(*mark);
        localRoot->addChild(*nicholas);
        localRoot->addChild(*paul);
        localRoot->addChild(*fifth);


        // Stage and screen pieces
        stageTexture.loadTexture();
        stageMaterial.diffuseTexture = &stageTexture;
        stageMaterial.specularIntensity = 0.0f;

        stagePiece1 = new NodeModel(Resources::unitCube, stageMaterial, Resources::litShader);
        stagePiece2 = new NodeModel(Resources::unitCube, stageMaterial, Resources::litShader);
        stagePiece3 = new NodeModel(Resources::unitCube, stageMaterial, Resources::litShader);
        screen = new NodeModel(Resources::unitCube, Resources::unshadedWhiteMaterial, Resources::basicShader);
        pillar1Bottom = new NodeModel(Resources::unitCube, Resources::unshadedWhiteMaterial, Resources::basicShader);
        pillar1Top = new NodeModel(Resources::unitCube, Resources::unshadedWhiteMaterial, Resources::basicShader);
        pillar2Bottom = new NodeModel(Resources::unitCube, Resources::unshadedWhiteMaterial, Resources::basicShader);
        pillar2Top = new NodeModel(Resources::unitCube, Resources::unshadedWhiteMaterial, Resources::basicShader);

        localRoot->addChild(*stagePiece1);
        localRoot->addChild(*stagePiece2);
        localRoot->addChild(*stagePiece3);
        localRoot->addChild(*screen);
        localRoot->addChild(*pillar1Bottom);
        localRoot->addChild(*pillar1Top);
        localRoot->addChild(*pillar2Bottom);
        localRoot->addChild(*pillar2Top);

        stagePiece1->translate(glm::vec3(0.0f, 0.75f * Resources::unitSize, -50.0f * Resources::unitSize));
        stagePiece1->transform = glm::scale(stagePiece1->transform, glm::vec3(64.0f * Resources::unitSize, 1.5f * Resources::unitSize, 12.0f * Resources::unitSize));

        stagePiece2->translate(glm::vec3(26.0f * Resources::unitSize, 0.75f * Resources::unitSize, -38.0f * Resources::unitSize));
        stagePiece2->transform = glm::scale(stagePiece2->transform, glm::vec3(12.0f * Resources::unitSize, 1.5f * Resources::unitSize, 12.0f * Resources::unitSize));

        stagePiece3->translate(glm::vec3(-26.0f * Resources::unitSize, 0.75f * Resources::unitSize, -38.0f * Resources::unitSize));
        stagePiece3->transform = glm::scale(stagePiece3->transform, glm::vec3(12.0f * Resources::unitSize, 1.5f * Resources::unitSize, 12.0f * Resources::unitSize));

        screen->translate(glm::vec3(0.0f, 23.0f * Resources::unitSize, -53.5f * Resources::unitSize));
        screen->transform = glm::scale(screen->transform, glm::vec3(58.0f * Resources::unitSize, 58.0f * Resources::unitSize * (float)world.windowHeight/(float)world.windowWidth, 0.5f * Resources::unitSize));

        pillar1Bottom->translate(glm::vec3(-30.5f * Resources::unitSize, 2.0f * Resources::unitSize, -53.5f * Resources::unitSize));
        pillar1Bottom->transform = glm::scale(pillar1Bottom->transform, glm::vec3(3.0f * Resources::unitSize, 1.0f * Resources::unitSize, 5.0f * Resources::unitSize));

        pillar1Top->translate(glm::vec3(-30.5f * Resources::unitSize, 21.5f * Resources::unitSize, -53.5f * Resources::unitSize));
        pillar1Top->transform = glm::scale(pillar1Top->transform, glm::vec3(3.0f * Resources::unitSize, 38.0f * Resources::unitSize, 3.0f * Resources::unitSize));

        pillar2Bottom->translate(glm::vec3(30.5f * Resources::unitSize, 2.0f * Resources::unitSize, -53.5f * Resources::unitSize));
        pillar2Bottom->transform = glm::scale(pillar2Bottom->transform, glm::vec3(3.0f * Resources::unitSize, 1.0f * Resources::unitSize, 5.0f * Resources::unitSize));

        pillar2Top->translate(glm::vec3(30.5f * Resources::unitSize, 21.5f * Resources::unitSize, -53.5f * Resources::unitSize));
        pillar2Top->transform = glm::scale(pillar2Top->transform, glm::vec3(3.0f * Resources::unitSize, 38.0f * Resources::unitSize, 3.0f * Resources::unitSize));



        // Positions and orients characters on an arc
        placeCharacters(*andrew, interval_degrees, radius);
        placeCharacters(*mark, interval_degrees, radius);
        placeCharacters(*nicholas, interval_degrees, radius);
        placeCharacters(*paul, interval_degrees, radius);
        placeCharacters(*fifth, interval_degrees, radius);

        // letters 
        andrew->translate(glm::vec3(12.0f, 0.0f, -5.0f));
        andrew->transform = glm::rotate(andrew->transform, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        mark->translate(glm::vec3(10.0f, 0.0f, 5.0f));
        mark->transform = glm::rotate(mark->transform, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));


        paul->translate(glm::vec3(-10.0f, 0.0f, 5.0f));
        paul->transform = glm::rotate(paul->transform, glm::radians(-135.0f), glm::vec3(0.0f, 1.0f, 0.0f));


        nicholas->translate(glm::vec3(-12.0f, 0.0f, -5.0f));
        nicholas->transform = glm::rotate(nicholas->transform, glm::radians(-210.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        fifth->translate(glm::vec3(0.0f, 0.0f, 8.0f));
        fifth->transform = glm::rotate(fifth->transform, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));




        // Ground
        groundTexture.loadTexture();
        groundMaterial.diffuseTexture = &groundTexture;
        groundMaterial.specularIntensity = 0.25f;
        groundMaterial.uvScale = glm::vec2(8.0f);

        NodeModel* ground = new NodeModel(Resources::quad, groundMaterial, Resources::litShader);
        localRoot->addChild(*ground);
        ground->transform = glm::scale(glm::mat4(1.0f), glm::vec3(128.0f * Resources::unitSize));
        ground->transform = glm::rotate(ground->transform, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        setEnabled(enabled);
    }

    /// For every character in word, create a new NodeCharacter and add it to root
    void setCharacters(Node& root, const std::string& word, float scale) const
    {
        for (const char& c : word)
        {
            root.addChild(*new NodeCharacter(c, Resources::unshadedWhiteMaterial, Resources::basicShader, scale));
        }
    }

    /**
     * Places each child in root in an arc centered at (radius, 0, 0), evenly spaced out by interval_degrees.
     *
     * Children are rotated to face (0, 0, 0). Their positions are relative to (radius, 0, 0).
     */
    void placeCharacters(Node& root, float interval_degrees, float radius) const
    {
        // For symmetry around angle 0
        float theta = interval_degrees * -(static_cast<float>(root.numChildren() - 1) / 2.0f);

        for (auto child : root)
        {
            child->transform =
                // Position on arc, relative to (radius, 0, 0)
                glm::translate(glm::mat4(1.0f), getPosOnCircle(theta, radius) - glm::vec3(radius, 0.0f, 0.0f)) *
                // Rotation to face (0, 0, 0)
                glm::rotate(glm::mat4(1.0f), glm::radians(-theta - 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            theta += interval_degrees;
        }
    }

    /// Converts from polar to cartesian (x, 0, z) coordinates
    glm::vec3 getPosOnCircle(float degrees, float radius) const
    {
        float radians = glm::radians(degrees);
        return glm::vec3(glm::cos(radians) * radius, 0.0f, glm::sin(radians) * radius);
    }

    void Shutdown(World& world) override
    {
        selected = nullptr;
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
        world.light.type = LightData::Type::Point;
        world.light.position = glm::vec3(0.0f, 64.0f * Resources::unitSize, 0.0f);
        world.light.direction = glm::vec3(0.0f, -1.0f, 0.0f);
        world.light.angle = 90.0f;
        world.light.constantAttenuation = 1.0f;
        world.light.constantAttenuation = 0.09f;
        world.light.quadraticAttenuation = 0.016f;

        world.shadows->setLight(world.light);
        world.shadows->range = 64.0f * Resources::unitSize;
        world.shadows->bias = 0.0001f;

        if (selected != nullptr)
        {
            if (scaleUp)
                selected->scaleStep(deltaSeconds);
            if (scaleDown)
                selected->scaleStep(-deltaSeconds);
            if (modelMovement != glm::vec2())
                selected->translate(deltaSeconds * glm::vec3(0.0f, modelMovement.y, modelMovement.x));
        }
    }

    void OnKeyReleased(World& world, int key, int mods) override
    {
        if (key == GLFW_KEY_Y)
            scaleUp = false;
        if (key == GLFW_KEY_I)
            scaleDown = false;
        if (key == GLFW_KEY_H || key == GLFW_KEY_K)
            modelMovement.x = 0;
        if (key == GLFW_KEY_U || key == GLFW_KEY_J)
            modelMovement.y = 0;
    }

    void OnKeyPressed(World& world, int key, int mods) override
    {
        // Model selection
        if (key == GLFW_KEY_1)
            selected = andrew;
        if (key == GLFW_KEY_2)
            selected = mark;
        if (key == GLFW_KEY_3)
            selected = nicholas;
        if (key == GLFW_KEY_4)
            selected = paul;
        if (key == GLFW_KEY_5)
            selected = fifth;

        // Setup model scaling
        if (key == GLFW_KEY_Y)
            scaleUp = true;
        if (key == GLFW_KEY_I)
            scaleDown = true;

        // Setup model manipulation mode: move vs rotate
        caps = !(mods & GLFW_MOD_SHIFT) != !(mods & GLFW_MOD_CAPS_LOCK); // Bitwise xor didn't work here

       // srand(time(0));
        float x, z;

        if (selected != nullptr)
        {
            if (key == GLFW_KEY_H && !caps)
                selected->rotate(-5.0f, selected->up());
            else if (key == GLFW_KEY_H && caps)
                modelMovement.x = -1.0f;

            if (key == GLFW_KEY_K && !caps)
                selected->rotate(5.0f, selected->up());
            else if (key == GLFW_KEY_K && caps)
                modelMovement.x = 1.0f;

            if (key == GLFW_KEY_U)
                modelMovement.y = 1.0f;
            if (key == GLFW_KEY_J)
                modelMovement.y = -1.0f;
            if (key == GLFW_KEY_SPACE)
            {
                selected->transform = glm::mat4(1.0f);
                x = rand() % 128 * Resources::unitSize + (-64 * Resources::unitSize);
                z = rand() % 128 * Resources::unitSize + (-64 * Resources::unitSize);
                selected->translate(glm::vec3(x, 0.0f, z));
            }
        }

        // Set polygon mode on characters of selected word
        if (selected != nullptr && (key == GLFW_KEY_P || key == GLFW_KEY_L || key == GLFW_KEY_T))
        {
            RenderMode polygonMode;
            if (key == GLFW_KEY_P)
                polygonMode = RenderMode::Point;
            else if (key == GLFW_KEY_L)
                polygonMode = RenderMode::Line;
            else
                polygonMode = RenderMode::Triangle;

            for (auto child : *selected)
            {
                NodeCharacter* character = dynamic_cast<NodeCharacter*>(child);
                if (character != nullptr)
                    character->renderMode = polygonMode;
            }
        }
    }

protected:

    bool scaleUp = false, scaleDown = false, rotate = false, caps = false;
    glm::vec2 modelMovement = glm::vec2(0.0f);
    Node* selected = nullptr;

    Node* localRoot = nullptr;
    Node* andrew = nullptr, * mark = nullptr, * nicholas = nullptr, * paul = nullptr, * fifth = nullptr;
    NodeModel* stagePiece1 = nullptr;
    NodeModel* stagePiece2 = nullptr;
    NodeModel* stagePiece3 = nullptr;
    NodeModel* screen = nullptr;
    NodeModel* pillar1Top = nullptr;
    NodeModel* pillar1Bottom = nullptr;
    NodeModel* pillar2Top = nullptr;
    NodeModel* pillar2Bottom = nullptr;

    Material groundMaterial;
    Texture groundTexture = Texture("assets/woodParquet.png");

    Material stageMaterial;
    Texture stageTexture = Texture("assets/cloth.jpg");
};
