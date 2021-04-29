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
 * Implements Programming Assignment 2 together with modules and classes:
 * * FPSCamera
 * * LightData
 * * Material
 * * SceneGraph
 * * Shadows
 * * Texture
 *
 * @see LightData
 * @see Material
 * @see Module
 * @see World
 * @see FPSCamera
 * @see SceneGraph
 * @see Shadows
 * @see Texture
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

        world.lights.push_back(&light);

        light.type = LightData::Type::Point;
        light.position = glm::vec3(0.0f, 50.0f * Resources::unitSize, 0.0f);
        light.direction = glm::vec3(0.0f, -1.0f, 0.0f);
        light.angle = 110.0f;
        light.constantAttenuation = 1.0f;
        light.constantAttenuation = 0.09f;
        light.quadraticAttenuation = 0.016f;
        light.shadowsRange = 50.0f * Resources::unitSize;
        light.shadowsBias = 0.001f;

        // Materials and textures
        stageTexture.loadTexture();
        groundTexture.loadTexture();
        pillarTexture.loadTexture();
        boxTexture.loadTexture();
        metalTexture.loadTexture();
       
        for (auto &texture : screenTextures)
        {
            texture.loadTexture();
        }

        stageMaterial.specularIntensity = 0.0f;

        groundMaterial.specularIntensity = 0.25f;
        groundMaterial.uvScale = glm::vec2(8.0f);

        pillarMaterial.specularIntensity = 0.0f;

        boxMaterial.specularIntensity = 0.0f;

        metalMaterial.diffuseIntensity = 0.5f;
        metalMaterial.specularIntensity = 2.0f;
        metalMaterial.shininess = 4.0f;

        screenMaterial.diffuseIntensity = 1.0f;
        screenMaterial.specularIntensity = 0.0f;
        screenMaterial.uvScale = glm::vec2(1.0f, 1.0f);

        UpdateTextures(true);


        const float characterScale = Resources::unitSize * 3.0f;

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
        setCharacters(*andrew, "AH41", characterScale);

        mark = new Node();
        setCharacters(*mark, "MB47", characterScale);

        nicholas = new Node();
        setCharacters(*nicholas, "NA40", characterScale);

        paul = new Node();
        setCharacters(*paul, "PV41", characterScale);

        fifth = new Node();
        setCharacters(*fifth, "AP00", characterScale);

        localRoot = new Node();
        world.sceneGraph->addChild(*localRoot);
        localRoot->addChild(*andrew);
        localRoot->addChild(*mark);
        localRoot->addChild(*nicholas);
        localRoot->addChild(*paul);
        localRoot->addChild(*fifth);


        // Stage and screen pieces
        stage = new NodeModel(Resources::halfCylinder, stageMaterial, Resources::litShader);
        screen = new NodeModel(Resources::unitCube, screenMaterial, Resources::litShader);
        pillar1Bottom = new NodeModel(Resources::unitCube, pillarMaterial, Resources::litShader);
        pillar1Top = new NodeModel(Resources::unitCube, pillarMaterial, Resources::litShader);
        pillar2Bottom = new NodeModel(Resources::unitCube, pillarMaterial, Resources::litShader);
        pillar2Top = new NodeModel(Resources::unitCube, pillarMaterial, Resources::litShader);

        localRoot->addChild(*stage);
        localRoot->addChild(*screen);
        localRoot->addChild(*pillar1Bottom);
        localRoot->addChild(*pillar1Top);
        localRoot->addChild(*pillar2Bottom);
        localRoot->addChild(*pillar2Top);

        stage->transform = glm::mat4(1.0f);
        stage->transform = glm::translate(stage->transform, glm::vec3(0.0f, 1.5f * 0.5f, -58.0f) * Resources::unitSize);
        stage->transform = glm::rotate(stage->transform, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        stage->transform = glm::rotate(stage->transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        stage->transform = glm::scale(stage->transform, glm::vec3(1.5f, 64.0f, 64.0f) * Resources::unitSize);

        screen->translate(glm::vec3(0.0f, 20.25f * Resources::unitSize, -53.5f * Resources::unitSize));
        screen->transform = glm::scale(screen->transform, glm::vec3(50.0f * Resources::unitSize, 50.0f * Resources::unitSize * (float)world.windowHeight/(float)world.windowWidth, 0.5f * Resources::unitSize));

        pillar1Bottom->translate(glm::vec3(-26.5f * Resources::unitSize, 2.0f * Resources::unitSize, -53.5f * Resources::unitSize));
        pillar1Bottom->transform = glm::scale(pillar1Bottom->transform, glm::vec3(3.0f * Resources::unitSize, 1.0f * Resources::unitSize, 5.0f * Resources::unitSize));

        pillar1Top->translate(glm::vec3(-26.5f * Resources::unitSize, 21.5f * Resources::unitSize, -53.5f * Resources::unitSize));
        pillar1Top->transform = glm::scale(pillar1Top->transform, glm::vec3(3.0f * Resources::unitSize, 38.0f * Resources::unitSize, 3.0f * Resources::unitSize));

        pillar2Bottom->translate(glm::vec3(26.5f * Resources::unitSize, 2.0f * Resources::unitSize, -53.5f * Resources::unitSize));
        pillar2Bottom->transform = glm::scale(pillar2Bottom->transform, glm::vec3(3.0f * Resources::unitSize, 1.0f * Resources::unitSize, 5.0f * Resources::unitSize));

        pillar2Top->translate(glm::vec3(26.5f * Resources::unitSize, 21.5f * Resources::unitSize, -53.5f * Resources::unitSize));
        pillar2Top->transform = glm::scale(pillar2Top->transform, glm::vec3(3.0f * Resources::unitSize, 38.0f * Resources::unitSize, 3.0f * Resources::unitSize));


        // Name tags
        const float zOffset = -20.0f;

        andrew->translate(glm::vec3(40.0f, 0.0f, -20.0f + zOffset) * Resources::unitSize);
        andrew->transform = glm::rotate(andrew->transform, glm::radians(-55.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        mark->translate(glm::vec3(40.0f, 0.0f, 20.0f + zOffset) * Resources::unitSize);
        mark->transform = glm::rotate(mark->transform, glm::radians(55.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        paul->translate(glm::vec3(-40.0f, 0.0f, 20.0f + zOffset) * Resources::unitSize);
        paul->transform = glm::rotate(paul->transform, glm::radians(-55.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        nicholas->translate(glm::vec3(-40.0f, 0.0f, -20.0f + zOffset) * Resources::unitSize);
        nicholas->transform = glm::rotate(nicholas->transform, glm::radians(55.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        fifth->translate(glm::vec3(0.0f, 0.0f, 32.0f + zOffset) * Resources::unitSize);


        // Ground
        NodeModel* ground = new NodeModel(Resources::quad, groundMaterial, Resources::litShader);
        localRoot->addChild(*ground);
        ground->transform = glm::scale(glm::mat4(1.0f), glm::vec3(128.0f * Resources::unitSize));
        ground->transform = glm::rotate(ground->transform, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));


        // Initial camera position
        world.camera->setPosition(glm::vec3(0.0f, 12.0f * Resources::unitSize, 64.0f * Resources::unitSize));


        setEnabled(enabled);
    }

    /// For every character in word, create a new NodeCharacter and add it to root
    void setCharacters(Node& root, const std::string& word, float scale)
    {
        float x = -scale * (word.size() - 1);

        for (size_t i = 0; i < word.size(); ++i)
        {
            const char& c = word.at(i);

            Material& mat = isdigit(c) ? metalMaterial : boxMaterial;
            NodeCharacter* nodeChar = new NodeCharacter(c, mat, Resources::litShader, scale);
            nodeChar->useSpheres = true;

            nodeChar->transform = glm::translate(glm::mat4(1.0f), glm::vec3(x, 0.0f, 0.0f));
            x += 2.0f * scale;

            root.addChild(*nodeChar);
        }
    }

    void UpdateTextures(bool texturesEnabled)
    {
        this->texturesEnabled = texturesEnabled;

        groundMaterial.diffuseTexture = texturesEnabled ? &groundTexture : &Resources::whiteTexture;
        stageMaterial.diffuseTexture = texturesEnabled ? &stageTexture : &Resources::whiteTexture;
        pillarMaterial.diffuseTexture = texturesEnabled ? &pillarTexture : &Resources::whiteTexture;
        boxMaterial.diffuseTexture = texturesEnabled ? &boxTexture : &Resources::whiteTexture;
        metalMaterial.diffuseTexture = texturesEnabled ? &metalTexture : &Resources::whiteTexture;
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
        light.enabled = enabled;
    }

    void Update(World& world, float deltaSeconds) override
    {
        if (selected != nullptr)
        {
            if (scaleUp)
                selected->scaleStep(deltaSeconds);
            if (scaleDown)
                selected->scaleStep(-deltaSeconds);
            if (modelMovement != glm::vec2())
                selected->translate(deltaSeconds * glm::vec3(modelMovement.x, modelMovement.y, 0.0f));
            if (modelShear != glm::vec2())
                selected->shear(modelShear.x * deltaSeconds/4, modelShear.y * deltaSeconds/4, modelShearDirection);
        }

        screenMaterial.diffuseTexture = texturesEnabled ? &screenTextures[((int)glm::floor(world.getTime() / 10.0f)) % 5] : &Resources::whiteTexture;
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
        if (key == GLFW_KEY_F || GLFW_KEY_G)
            modelShear.x = 0;
        if (key == GLFW_KEY_C || GLFW_KEY_V)
            modelShear.y = 0;
    }

    void OnKeyPressed(World& world, int key, int mods) override
    {
        // Shadows toggle
        if (key == GLFW_KEY_B)
            world.shadows->setEnabled(!world.shadows->getEnabled());

        // Textures toggle
        if (key == GLFW_KEY_X)
            UpdateTextures(!texturesEnabled);

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

        // Cycle through different shear options
        if (key == GLFW_KEY_N) {
            if (modelShearDirection == Node::ShearDirection::X)
                modelShearDirection = Node::ShearDirection::Y;
            else if (modelShearDirection == Node::ShearDirection::Y)
                modelShearDirection = Node::ShearDirection::Z;
            else if (modelShearDirection == Node::ShearDirection::Z)
                modelShearDirection = Node::ShearDirection::X;
        }


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
                bool isValid = false;

                selected->transform = glm::mat4(1.0f);

                while (!isValid)
                {
                   x = rand() % 128 * Resources::unitSize + (-64 * Resources::unitSize);
                   z = rand() % 128 * Resources::unitSize + (-64 * Resources::unitSize);

                   isValid = z >= -15.0f * Resources::unitSize;

                }
                selected->translate(glm::vec3(x, 0.0f, z));
            }

            if (caps)
            {
                if (key == GLFW_KEY_G)
                    selected->shear(0.1f, 0.0f, modelShearDirection);
                else if (key == GLFW_KEY_F)
                    selected->shear(-0.1f, 0.0f, modelShearDirection);
                else if (key == GLFW_KEY_V)
                    selected->shear(0.0f, 0.1f, modelShearDirection);
                else if (key == GLFW_KEY_C)
                    selected->shear(0.0f, -0.1f, modelShearDirection);
            }
            else
            {
                if (key == GLFW_KEY_G)
                    modelShear.x = 1.0f;
                if (key == GLFW_KEY_F)
                    modelShear.x = -1.0f;
                if (key == GLFW_KEY_V)
                    modelShear.y = 1.0f;
                if (key == GLFW_KEY_C)
                    modelShear.y = -1.0f;
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
                auto* character = dynamic_cast<NodeCharacter*>(child);
                if (character != nullptr)
                    character->renderMode = polygonMode;
            }
        }
    }

protected:

    bool scaleUp = false, scaleDown = false, rotate = false, caps = false;
    glm::vec2 modelMovement = glm::vec2(0.0f);
    glm::vec2 modelShear = glm::vec2(0.0f);
    Node::ShearDirection modelShearDirection = Node::ShearDirection::Y;
    Node* selected = nullptr;

    Node* localRoot = nullptr;
    Node* andrew = nullptr, * mark = nullptr, * nicholas = nullptr, * paul = nullptr, * fifth = nullptr;
    NodeModel* stage = nullptr;
    NodeModel* screen = nullptr;
    NodeModel* pillar1Top = nullptr;
    NodeModel* pillar1Bottom = nullptr;
    NodeModel* pillar2Top = nullptr;
    NodeModel* pillar2Bottom = nullptr;

    Material groundMaterial;
    Texture groundTexture = Texture("assets/woodParquet.png");

    Material stageMaterial;
    Texture stageTexture = Texture("assets/cloth.jpg");

    Material pillarMaterial;
    Texture pillarTexture = Texture("assets/metal.jpg");

    Material boxMaterial;
    Texture boxTexture = Texture("assets/fragile.jpg");

    Material metalMaterial;
    Texture metalTexture = Texture("assets/metal.jpg");

    Material screenMaterial;

    Texture screenTextures[5] = { Texture("assets/name_andrew.png"), Texture("assets/name_fifth.png"), Texture("assets/name_mark.png"), Texture("assets/name_nick.png"), Texture("assets/name_paul.png")};
    int currentScreenTexture = 0;

    bool texturesEnabled = false;

    LightData light;
};
