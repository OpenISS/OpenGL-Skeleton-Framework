#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../module.h"

enum class MouseInputMode
{
    /// Camera can only rotate horizontally
    Pan,

    /// Camera can only rotate vertically
    Tilt,

    /// Camera can rotate on both axis
    FreeCam,

    /// Camera does not rotate at all, while zoom is being changed through the FOV
    Zoom,
};

/**
 * Implements classic FPS game camera movement and rotation.
 * 
 * @see Camera
 */
class FPSCamera : public Module
{
public:

    MODULE_CONSTRUCTOR(FPSCamera)

    void OnKeyReleased(World& world, int key, int mods) override
    {
        if (key == GLFW_KEY_A || key == GLFW_KEY_D)
            movement.x = 0;
        if (key == GLFW_KEY_W || key == GLFW_KEY_S)
            movement.y = 0;
    }

    void OnKeyPressed(World& world, int key, int mods) override
    {
        if (key == GLFW_KEY_HOME || key == GLFW_KEY_R)
            reset = true;
        if (key == GLFW_KEY_A)
            movement.x = -1;
        if (key == GLFW_KEY_D)
            movement.x = 1;
        if (key == GLFW_KEY_W)
            movement.y = 1;
        if (key == GLFW_KEY_S)
            movement.y = -1;
    }

    void OnMouseReleased(World& world, int button, int mods) override
    {
        // Return to freecam motion when none of the other modes are actives
        if (button == GLFW_MOUSE_BUTTON_LEFT ||
            button == GLFW_MOUSE_BUTTON_MIDDLE ||
            button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            mouseInputMode = MouseInputMode::FreeCam;
        }
    }

    void OnMousePressed(World& world, int button, int mods) override
    {
        // Select appropriate Mouse Mode based on what button was clicked
        if (button == GLFW_MOUSE_BUTTON_LEFT)
            mouseInputMode = MouseInputMode::Zoom;
        if (button == GLFW_MOUSE_BUTTON_MIDDLE)
            mouseInputMode = MouseInputMode::Tilt;
        if (button == GLFW_MOUSE_BUTTON_RIGHT)
            mouseInputMode = MouseInputMode::Pan;
    }

    void OnMouseMovedDelta(World& world, float deltaX, float deltaY) override
    {
        deltaMouse.x = deltaX;
        deltaMouse.y = deltaY;
    }

    void Startup(World& world) override
    {
        world.camera = camera = new Camera(world.windowAspectRatio, position, direction, up);
    }

    void Update(World& world, float deltaSeconds) override
    {
        if (reset)
        {
            camera->setPosition(position);
            camera->setDirection(direction);
            reset = false;
        }

        if (deltaMouse != glm::vec2() && !world.imgui->getEnabled())
        {
            // set angle changes since last frame
            float yaw = -deltaMouse.x * turnSpeed * deltaSeconds;
            float pitch = -deltaMouse.y * turnSpeed * deltaSeconds;

            if (mouseInputMode == MouseInputMode::Zoom)
            {
                float fov = camera->getFov();
                float newFov = glm::clamp(fov - pitch * 10.0f, 2.0f, 178.0f);
                camera->setFov(newFov);

                if (world.debug)
                    std::cout << "Update FOV: " << fov << " - " << pitch << std::endl;
            }
            else
            {
                // To support Freecam mode, we track whether pan / tilt actions are enabled and only send the angle if they are
                bool allowPan = mouseInputMode == MouseInputMode::Pan || mouseInputMode == MouseInputMode::FreeCam;
                bool allowTilt = mouseInputMode == MouseInputMode::Tilt || mouseInputMode == MouseInputMode::FreeCam;

                camera->rotate(yaw * static_cast<float>(allowPan), pitch * static_cast<float>(allowTilt));

                if (world.debug)
                {
                    std::cout << "Yaw, Pitch: " << yaw << ", " << pitch << std::endl;
                    std::cout << "Direction: " << camera->forward().x << ", " << camera->forward().y << ", " << camera->forward().z << std::endl;
                }
            }
        }
        // Reset the change of mouse coordinates
        deltaMouse = glm::vec2();

        if (movement != glm::vec2())
        {
            // smooth camera movement using input from keyboard and delta time
            glm::vec3 xAxis = camera->right() * movementSpeed * movement.x * deltaSeconds;
            glm::vec3 yAxis = camera->forward() * movementSpeed * movement.y * deltaSeconds;
            glm::vec3 deltaPos = xAxis + yAxis;

            camera->translate(deltaPos);

            if (world.debug)
            {
                std::cout << "Position Change: " << movement.x << ", " << movement.y << ", " << std::endl;
                std::cout << "Camera Moved By: " << deltaPos.x << ", " << deltaPos.y << ", " << deltaPos.z << std::endl;
            }
        }
    }

protected:

    Camera* camera = nullptr;
    MouseInputMode mouseInputMode = MouseInputMode::FreeCam;
    glm::vec2 movement = glm::vec2(0.0f), deltaMouse = glm::vec2(0.0f);
    glm::vec3 position = glm::vec3(0.0f),
              direction = glm::vec3(0.00001f, 0.0f, -1.0f),
              up = glm::vec3(0.0f, 1.0f, 0.0f);
    float movementSpeed = 10.0f, turnSpeed = 0.1f;
    bool reset = false;
};
