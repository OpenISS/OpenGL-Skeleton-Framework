#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../module.h"

enum class MouseInputMode
{
    Pan,
    Tilt,
    FreeCam,
    Zoom,
};

class FpsCamera : public Module
{
public:

    void OnKeyReleased(World& world, int key, int mods) override
    {
        if (key == GLFW_KEY_A || key == GLFW_KEY_D) {
            movement.x = 0;
        }
        if (key == GLFW_KEY_W || key == GLFW_KEY_S) {
            movement.y = 0;
        }
    }

    void OnKeyPressed(World& world, int key, int mods) override
    {
        if (key == GLFW_KEY_HOME || key == GLFW_KEY_R) {
            reset = true;
        }
        if (key == GLFW_KEY_A) {
            movement.x = -1;
        }
        if (key == GLFW_KEY_D) {
            movement.x = 1;
        }
        if (key == GLFW_KEY_W) {
            movement.y = 1;
        }
        if (key == GLFW_KEY_S) {
            movement.y = -1;
        }
    }

    void OnMouseReleased(World& world, int button, int mods) override
    {
        // return to freecam motion when none of the other modes are actives
        if (button == GLFW_MOUSE_BUTTON_LEFT ||
            button == GLFW_MOUSE_BUTTON_MIDDLE ||
            button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            mouseInputMode = MouseInputMode::FreeCam;
        }
    }

    void OnMousePressed(World& world, int button, int mods) override
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            mouseInputMode = MouseInputMode::Zoom;
        }
        if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
            mouseInputMode = MouseInputMode::Tilt;
        }
        if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            mouseInputMode = MouseInputMode::Pan;
        }
    }

    void OnMouseMoved(World& world, float x, float y) override
    {
        if (firstMoved) {
            lastMouse.x = x;
            lastMouse.y = y;
            firstMoved = false;
        }

        deltaMouse.x = lastMouse.x - x;
        deltaMouse.y = lastMouse.y - y;

        lastMouse.x = x;
        lastMouse.y = y;

        if (world.debug) {
            std::cout << "Cursor Pos: " << x << ", " << y << "\tCursor Change: " << deltaMouse.x << ", " << deltaMouse.y << std::endl;
        }
    }

    void Startup(World& world) override
    {
        world.camera = camera = new Camera(world.windowAspectRatio, position, direction, up);
    }

    void Render(World& world) override
    {
        glm::mat4 view = camera->view();
        glm::mat4 projection = camera->projection();
        Resources::basicShader.setViewProjectionMatrix(view, projection);
    }

    void Update(World& world, float deltaSeconds) override
    {
        if (reset) {
            camera->setPosition(position);
            camera->setDirection(direction);
            reset = false;
        }

        if (deltaMouse != glm::vec2()) {
            float yaw = deltaMouse.x * turnSpeed * deltaSeconds;
            float pitch = deltaMouse.y * turnSpeed * deltaSeconds;

            if (mouseInputMode == MouseInputMode::Zoom) {
                float fov = camera->getFov();
                camera->setFov(fov - pitch);

                if (world.debug) {
                    std::cout << "Update FOV: " << fov << " - " << pitch << std::endl;
                }
            } else {
                bool allowPan = mouseInputMode == MouseInputMode::Pan || mouseInputMode == MouseInputMode::FreeCam;
                bool allowTilt = mouseInputMode == MouseInputMode::Tilt || mouseInputMode == MouseInputMode::FreeCam;

                camera->rotate(yaw * static_cast<float>(allowPan), pitch * static_cast<float>(allowTilt));

                if (world.debug) {
                    std::cout << "Yaw, Pitch: " << yaw << ", " << pitch << std::endl;
                    std::cout << "Direction: " << camera->forward().x << ", " << camera->forward().y << ", " << camera->forward().z << std::endl;
                }
            }

            deltaMouse = glm::vec2();
        }

        if (movement != glm::vec2()) {
            glm::vec3 xAxis = camera->right() * movementSpeed * movement.x * deltaSeconds;
            glm::vec3 yAxis = camera->forward() * movementSpeed * movement.y * deltaSeconds;
            glm::vec3 deltaPos = xAxis + yAxis;

            camera->translate(deltaPos);

            if (world.debug) {
                std::cout << "Position Change: " << movement.x << ", " << movement.y << ", " << std::endl;
                std::cout << "Camera Moved By: " << deltaPos.x << ", " << deltaPos.y << ", " << deltaPos.z << std::endl;
            }
        }
    }

protected:
    Camera* camera;
    MouseInputMode mouseInputMode = MouseInputMode::FreeCam;
    glm::vec2 movement, deltaMouse, lastMouse;
    glm::vec3 position = glm::vec3(),
              direction = glm::vec3(0.00001f, 0.0f, -1.0f),
              up = glm::vec3(0.0f, 1.0f, 0.0f);
    float movementSpeed = 5.0f, turnSpeed = 0.1f;
    bool firstMoved = true, reset = false;
};
