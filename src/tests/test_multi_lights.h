#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../camera.h"
#include "../color.h"
#include "../light_data.h"
#include "../material.h"
#include "../module.h"
#include "../node_character.h"
#include "../node_model.h"
#include "../resources.h"
#include "../texture.h"
#include "../world.h"
#include "../thirdparty/imgui/imgui.h"
#include "../modules/imgui_integration.h"


class TestMultiLights : public Module
{
public:

    MODULE_CONSTRUCTOR(TestMultiLights)

    void Startup(World& world) override
    {
        Module::Startup(world);

        // Lights and cameras
        {
            world.lights.push_back(&ambientLight);
            world.lights.push_back(&mainLight);
            world.lights.push_back(&orbitLight);

            ambientLight.type = LightData::Type::Spot;
            ambientLight.ambientIntensity = 0.016f;
            ambientLight.diffuseIntensity = 0.0f;
            ambientLight.specularIntensity = 0.0f;
            ambientLight.shadowsEnabled = false;

            mainLight.type = LightData::Type::Spot;
            mainLight.position = glm::vec3(0.0f, 30.0, 30.0f) * Resources::unitSize;
            mainLight.direction = glm::vec3(0.0f, -1.0f, -1.0f);
            mainLight.angle = 90.0f;
            mainLight.constantAttenuation = 1.0f;
            mainLight.linearAttenuation = 0.09f;
            mainLight.quadraticAttenuation = 0.016f;
            mainLight.shadowsRange = 128.0f * Resources::unitSize;
            mainLight.shadowsBias = 0.0005f;

            orbitLight.type = LightData::Type::Spot;
            orbitLight.angle = 25.0f;
            orbitLight.diffuseColor = hexToFloatRGB(0xe600ff);
            orbitLight.constantAttenuation = 1.0f;
            orbitLight.linearAttenuation = 0.09f;
            orbitLight.quadraticAttenuation = 0.004f;
            orbitLight.shadowsRange = 128.0f * Resources::unitSize;
            orbitLight.shadowsBias = 0.0005f;

            frontCam = new Camera(world.windowAspectRatio, glm::vec3(0.0f, 20.0f, -5.0f) * Resources::unitSize, glm::vec3(0.0f, -0.75f, 0.5f));
            backCam = new Camera(world.windowAspectRatio, glm::vec3(0.0f, 20.0f, -5.0f) * Resources::unitSize, glm::vec3(0.0f, -0.75f, -0.5f));
            lightCam = new Camera(world.windowAspectRatio, mainLight.position, glm::normalize(-mainLight.position));
            orbitCam = new Camera(world.windowAspectRatio);
            fpsCam = world.camera;

            // Initial camera position
            world.camera->setPosition(glm::vec3(0.0f, 12.0f * Resources::unitSize, 64.0f * Resources::unitSize));
            world.camera->setDirection(glm::vec3(0.0f, 0.0f, -1.0f));
        }


        // Materials and textures
        {
            stageTexture.loadTexture();
            groundTexture.loadTexture();
            boxTexture.loadTexture();

            stageMaterial.specularIntensity = 0.0f;

            groundMaterial.specularIntensity = 0.25f;
            groundMaterial.uvScale = glm::vec2(8.0f);

            boxMaterial.specularIntensity = 0.0f;

            UpdateTextures(true);
        }


        // Name
        {
            nameGroup = new Node();
            setCharacters(*nameGroup, "AMPN47", Resources::unitSize * 3.0f);
            nameGroup->translate(glm::vec3(0.0f, 0.0f, -5.0f) * Resources::unitSize);

            localRoot = new Node();
            world.sceneGraph->addChild(*localRoot);
            localRoot->addChild(*nameGroup);
        }


        // Stage and screen pieces
        {
            stage = new NodeModel(Resources::halfCylinder, stageMaterial, Resources::litShader);
            localRoot->addChild(*stage);

            stage->transform = glm::mat4(1.0f);
            stage->transform = glm::translate(stage->transform, glm::vec3(0.0f, 1.5f * 0.5f, -58.0f) * Resources::unitSize);
            stage->transform = glm::rotate(stage->transform, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            stage->transform = glm::rotate(stage->transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            stage->transform = glm::scale(stage->transform, glm::vec3(1.5f, 64.0f, 64.0f) * Resources::unitSize);
        }


        // Ground
        {
            NodeModel* ground = new NodeModel(Resources::quad, groundMaterial, Resources::litShader);
            localRoot->addChild(*ground);
            ground->transform = glm::scale(glm::mat4(1.0f), glm::vec3(128.0f * Resources::unitSize));
            ground->transform = glm::rotate(ground->transform, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        }


        setEnabled(enabled);
    }

    /// For every character in word, create a new NodeCharacter and add it to root
    void setCharacters(Node& root, const std::string& word, float scale)
    {
        float y = 0.0f;

        for (size_t i = 0; i < word.size(); ++i)
        {
            const char& c = word.at(i);
            NodeCharacter* nodeChar = new NodeCharacter(c, boxMaterial, Resources::litShader, scale);

            nodeChar->transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, y, 0.0f));
            y += 2.5f * scale;

            root.addChild(*nodeChar);
        }
    }

    void UpdateTextures(bool texturesEnabled)
    {
        this->texturesEnabled = texturesEnabled;

        groundMaterial.diffuseTexture = texturesEnabled ? &groundTexture : &Resources::whiteTexture;
        stageMaterial.diffuseTexture = texturesEnabled ? &stageTexture : &Resources::whiteTexture;
        boxMaterial.diffuseTexture = texturesEnabled ? &boxTexture : &Resources::whiteTexture;
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
        ambientLight.enabled = enabled;
        mainLight.enabled = enabled;
        orbitLight.enabled = enabled;
    }

    void Update(World& world, float deltaSeconds) override
    {
        glm::vec3 orbitCamPos = glm::vec3(40.0f * glm::sin(orbitCamAngle), 20.0f, 40.0f * glm::cos(orbitCamAngle)) * Resources::unitSize;
        orbitCam->setPosition(orbitCamPos);
        orbitCam->setDirection(glm::normalize(-orbitCamPos));

        orbitLight.position = orbitCam->getPosition();
        orbitLight.direction = orbitCam->getDirection();

        // Cameras
        if (camControlIdx == 0)
            world.camera = fpsCam;
        else if (camControlIdx == 1)
            world.camera = frontCam;
        else if (camControlIdx == 2)
            world.camera = backCam;
        else if (camControlIdx == 3)
            world.camera = lightCam;
        else if (camControlIdx == 4)
            world.camera = orbitCam;
    }

    void Render(World& world, RenderPass pass) override
    {
        // Display controls UI
        if (world.imgui->getEnabled() && pass == RenderPass::Color)
        {
            ImGui::SetNextWindowPos(ImVec2(600.0f, 60.0f), ImGuiCond_FirstUseEver);
            ImGui::Begin("Quiz #2", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

            ImGui::Text("Close/Open UI with 'M' key.");

            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();

            if (ImGui::Checkbox("Textures", &texturesEnabled))
                UpdateTextures(texturesEnabled);

            ImGui::PushID("Lights");
            ImGui::Text("Lights:"); ImGui::SameLine();
            ImGui::Checkbox("Ambient", &ambientLight.enabled); ImGui::SameLine();
            ImGui::Checkbox("Main", &mainLight.enabled); ImGui::SameLine();
            ImGui::Checkbox("Orbit", &orbitLight.enabled);
            ImGui::PopID();

            ImGui::PushID("Shadows");
            ImGui::Text("Shadows:"); ImGui::SameLine();
            ImGui::Checkbox("Main", &mainLight.shadowsEnabled); ImGui::SameLine();
            ImGui::Checkbox("Orbit", &orbitLight.shadowsEnabled);
            ImGui::PopID();

            ImGui::PushID("Cameras");
            ImGui::Text("Cameras:"); ImGui::SameLine();
            ImGui::RadioButton("FPS", &camControlIdx, 0); ImGui::SameLine();
            ImGui::RadioButton("Front", &camControlIdx, 1); ImGui::SameLine();
            ImGui::RadioButton("Back", &camControlIdx, 2); ImGui::SameLine();
            ImGui::RadioButton("Main Light", &camControlIdx, 3); ImGui::SameLine();
            ImGui::RadioButton("Orbit", &camControlIdx, 4);
            ImGui::PopID();

            ImGui::SliderAngle("Orbit Cam Angle", &orbitCamAngle);

            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();

            if (ImGui::Button("Reset"))
                Reset(world);

            ImGui::End();
        }
    }

    void Reset(World& world)
    {
        world.imgui->setEnabled(true);

        UpdateTextures(true);

        camControlIdx = 0;
        world.camera = fpsCam;
        world.camera->setPosition(glm::vec3(0.0f, 12.0f * Resources::unitSize, 64.0f * Resources::unitSize));
        world.camera->setDirection(glm::vec3(0.0f, 0.0f, -1.0f));
        world.camera->setFov(58.0f);
        orbitCamAngle = glm::pi<float>();

        ambientLight.enabled = true;
        mainLight.enabled = true;
        orbitLight.enabled = true;

        mainLight.shadowsEnabled = true;
        orbitLight.shadowsEnabled = true;
    }

protected:

    Node* localRoot = nullptr;
    Node* nameGroup = nullptr;
    NodeModel* stage = nullptr;

    Material groundMaterial;
    Texture groundTexture = Texture("assets/woodParquet.png");

    Material stageMaterial;
    Texture stageTexture = Texture("assets/cloth.jpg");

    Material boxMaterial;
    Texture boxTexture = Texture("assets/fragile.jpg");

    bool texturesEnabled = false;
    int camControlIdx = 0;

    LightData ambientLight;
    LightData mainLight;
    LightData orbitLight;

    Camera* frontCam = nullptr;
    Camera* backCam = nullptr;
    Camera* lightCam = nullptr;
    Camera* orbitCam = nullptr;
    Camera* fpsCam = nullptr;

    float orbitCamAngle = glm::pi<float>();
};
