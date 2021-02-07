#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "module.h"

class ModuleFpsCamera : public Module
{
public:

    void OnKeyReleased(World& world, int key, int mods) override
    {
        if (key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT || key == GLFW_KEY_A || key == GLFW_KEY_D) {
            movement.x = 0;
        }
        if (key == GLFW_KEY_UP || key == GLFW_KEY_DOWN || key == GLFW_KEY_W || key == GLFW_KEY_S) {
            movement.y = 0;
        }
    }

    void OnKeyPressed(World& world, int key, int mods) override
    {
        if (key == GLFW_KEY_HOME || GLFW_KEY_R) {
            reset = true;
        }
        if (key == GLFW_KEY_LEFT || key == GLFW_KEY_A) {
            movement.x = -1;
        }
        if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) {
            movement.x = 1;
        }
        if (key == GLFW_KEY_UP || key == GLFW_KEY_W) {
            movement.y = 1;
        }
        if (key == GLFW_KEY_DOWN || key == GLFW_KEY_S) {
            movement.y = -1;
        }
    }

    void OnMouseReleased(World& world, int button, int mods) override
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            // can zoom
        }
        if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
            allowTilt = false;
        }
        if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            allowPan = false;
        }
    }

    void OnMousePressed(World& world, int button, int mods) override
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            // can zoom
        }
        if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
            allowTilt = true;
        }
        if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            allowPan = true;
        }
    }

    void OnMouseMoved(World& world, double x, double y) override
    {
        if (firstMoved) {
            lastMouse.x = x;
            lastMouse.y = y;
            firstMoved = false;
        }

        mouse.x = lastMouse.x - x;
        mouse.y = lastMouse.y - y;

        lastMouse.x = x;
        lastMouse.y = y;

        if (world.debug) {
            std::cout << "Cursor Pos: " << x << ", " << y << "\tCursor Change: " << mouse.x << ", " << mouse.y << std::endl;
        }
    }

    void Update(World& world, float deltaSeconds) override
    {
        Module::Update(world, deltaSeconds);
        if (reset) {
            world.camera->setDirection(glm::vec3(0.00001f, 0.0f, -1.0f));
            reset = false;
        }

        if (mouse != glm::vec2()) {
            world.camera->setDirection(mouse.x * mouseSensitivity * deltaSeconds,
                                       mouse.y * mouseSensitivity * deltaSeconds,
                                       world.debug);
            mouse = glm::vec2();
        }

        if (movement != glm::vec2()) {
            glm::vec3 xAxis = world.camera->right() * movementSpeed * movement.x * deltaSeconds;
            glm::vec3 yAxis = world.camera->forward() * movementSpeed * movement.y * deltaSeconds;
            world.camera->translate(xAxis);
            world.camera->translate(yAxis);

            if (world.debug) {
                std::cout << "xAxis Change: " << xAxis.x << ", " << xAxis.y << ", " << xAxis.z << std::endl;
                std::cout << "yAxis Change: " << yAxis.x << ", " << yAxis.y << ", " << yAxis.z << std::endl;
            }
        }
    }

protected:
    float movementSpeed = 5.0f, mouseSensitivity = 0.1f;
    glm::vec2 movement, mouse, lastMouse;
    bool firstMoved = true, reset = false, allowPan = false, allowTilt = false;
    
};

