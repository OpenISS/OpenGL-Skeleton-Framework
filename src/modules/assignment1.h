#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../color.h"
#include "../module.h"
#include "../node_character.h"
#include "../node_model.h"
#include "../resources.h"
#include "../world.h"

class Assignment1: public Module
{
public:

    void Startup(World& world) override
    {
        Module::Startup(world);

        const float scale = Resources::unitSize * 3.0f;
        const float interval_degrees = 10.0f;
        const float radius = Resources::unitSize * 64.0f;

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

        world.sceneGraph->addChild(*andrew);
        world.sceneGraph->addChild(*mark);
        world.sceneGraph->addChild(*nicholas);
        world.sceneGraph->addChild(*paul);
        world.sceneGraph->addChild(*fifth);

        placeCharacters(*andrew,   interval_degrees, radius);
        placeCharacters(*mark,     interval_degrees, radius);
        placeCharacters(*nicholas, interval_degrees, radius);
        placeCharacters(*paul,     interval_degrees, radius);
        placeCharacters(*fifth,    interval_degrees, radius);

        andrew->transform   = glm::translate(glm::mat4(1.0f), getPosOnCircle(45.0f,  radius)) * glm::rotate(glm::mat4(1.0f), glm::radians(45.0f - 90.0f),  glm::vec3(0.0f, 1.0f, 0.0f));
        mark->transform     = glm::translate(glm::mat4(1.0f), getPosOnCircle(315.0f, radius)) * glm::rotate(glm::mat4(1.0f), glm::radians(315.0f + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        nicholas->transform = glm::translate(glm::mat4(1.0f), getPosOnCircle(135.0f, radius)) * glm::rotate(glm::mat4(1.0f), glm::radians(135.0f + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        paul->transform     = glm::translate(glm::mat4(1.0f), getPosOnCircle(225.0f, radius)) * glm::rotate(glm::mat4(1.0f), glm::radians(225.0f - 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        fifth->transform    = glm::mat4(1.0f) * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    void setCharacters(Node& root, const std::string& word, float scale) const
    {
        for (const char& c : word)
        {
            root.addChild(*new NodeCharacter(c, Resources::basicShader, scale));
        }
    }

    void placeCharacters(Node& root, float interval_degrees, float radius) const
    {
        float theta = interval_degrees * -(static_cast<float>(root.numChildren() - 1) / 2.0f); 

        auto it = root.beginChildren();
        auto end = root.endChildren();
        for (; it != end; ++it)
        {
            Node& child = **it;
            child.transform =
                glm::translate(glm::mat4(1.0f), getPosOnCircle(theta, radius) - glm::vec3(radius, 0.0f, 0.0f)) *
                glm::rotate(glm::mat4(1.0f), glm::radians(-theta - 90.f), glm::vec3(0.0f, 1.0f, 0.0f));
            theta += interval_degrees;
        }
    }

    glm::vec3 getPosOnCircle(float degrees, float radius) const
    {
        float radians = glm::radians(degrees);
        return glm::vec3(glm::cos(radians) * radius, 0.0f, glm::sin(radians) * radius);
    }

    void Shutdown(World& world) override
    {
        selected = nullptr;
        world.sceneGraph->removeChild(*andrew);
        world.sceneGraph->removeChild(*mark);
        world.sceneGraph->removeChild(*nicholas);
        world.sceneGraph->removeChild(*paul);
        world.sceneGraph->removeChild(*fifth);
        delete andrew;
        delete mark;
        delete nicholas;
        delete paul;
        delete fifth;
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
        }

        // Polygon mode
        if (selected != nullptr && (key == GLFW_KEY_P || key == GLFW_KEY_L || key == GLFW_KEY_T))
        {
            RenderMode polygonMode;
            if (key == GLFW_KEY_P)
                polygonMode = RenderMode::Point;
            else if (key == GLFW_KEY_L)
                polygonMode = RenderMode::Line;
            else
                polygonMode = RenderMode::Triangle;

            auto it = selected->beginChildren();
            auto end = selected->endChildren();
            for (; it != end; ++it)
            {
                Node& child = **it;
                NodeCharacter* character = dynamic_cast<NodeCharacter*>(&child);
                if (character != nullptr)
                    character->renderMode = polygonMode;
            }
        }
    }

protected:

    bool scaleUp = false, scaleDown = false, rotate = false, caps = false;
    glm::vec2 modelMovement = glm::vec2(0.0f);
    Node* selected = nullptr;

    Node *andrew = nullptr, *mark = nullptr, *nicholas = nullptr, *paul = nullptr, *fifth = nullptr;
};
