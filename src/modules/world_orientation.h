#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../module.h"

/*
* WorldOrientation class
*
* Creating key commands orient around the world
* Rotates the world around the x and y axis 
*/
class WorldOrientation : public Module
{
public:

    /// On key release reset movement to 0;
    void OnKeyReleased(World& world, int key, int mods) override
    {
        if (key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT)
            movement.x = 0;
        if (key == GLFW_KEY_UP || key == GLFW_KEY_DOWN)
            movement.y = 0;
    }

    /// Key commands to move around axis 
    void OnKeyPressed(World& world, int key, int mods) override
    {
        if (key == GLFW_KEY_HOME || key == GLFW_KEY_R)
            reset = true;
        if (key == GLFW_KEY_LEFT)
            movement.x = -1;
        if (key == GLFW_KEY_RIGHT)
            movement.x = 1;
        if (key == GLFW_KEY_UP)
            movement.y = 1;
        if (key == GLFW_KEY_DOWN)
            movement.y = -1;
    }

    void Update(World& world, float deltaSeconds) override
    {
        if (reset)
        {
            world.sceneGraph->root.transform = glm::mat4(1.0f);
            reset = false;
        }

        if (movement != glm::vec2())
        {
            world.sceneGraph->root.transform = glm::rotate(world.sceneGraph->root.transform, glm::radians(anglesPerSecond * deltaSeconds * movement.x), glm::vec3(1.0f, 0.0f, 0.0f));
            world.sceneGraph->root.transform = glm::rotate(world.sceneGraph->root.transform, glm::radians(anglesPerSecond * deltaSeconds * movement.y), glm::vec3(0.0f, 1.0f, 0.0f));
        }
    }

protected:

    float anglesPerSecond = 60.0f;
    glm::vec2 movement = glm::vec2(0.0f);
    bool reset = false;
};
