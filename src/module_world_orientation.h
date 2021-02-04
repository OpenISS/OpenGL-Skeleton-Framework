#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "module.h"


class ModuleWorldOrientation : public Module
{
public:

    virtual void OnKey(World& world, int key, int action, int mods)
    {
        Module::OnKey(world, key, action, mods);

        if (action == GLFW_REPEAT)
        {
            if (key == GLFW_KEY_LEFT)
            {
                movement.x = 1.0;
            }
            else if (key == GLFW_KEY_RIGHT)
            {
                movement.x = -1.0;      
            }
            else if (key == GLFW_KEY_UP)
            {
                movement.y = 1.0;
            }
            else if (key == GLFW_KEY_DOWN)
            {
                movement.y = -1.0;
            }
        }
    }

    virtual void Update(World& world, float deltaSeconds)
    {
        Module::Update(world, deltaSeconds);

        world.sceneGraph->root.transform = glm::rotate(world.sceneGraph->root.transform, glm::radians(anglesPerSecond * deltaSeconds * movement.x), glm::vec3(1.0f, 0.0f, 0.0f));
        world.sceneGraph->root.transform = glm::rotate(world.sceneGraph->root.transform, glm::radians(anglesPerSecond * deltaSeconds * movement.y), glm::vec3(0.0f, 1.0f, 0.0f));

        movement = glm::vec2(0.0f, 0.0f);
    }

protected:
    float anglesPerSecond = 60.0f;
    glm::vec2 movement; 
    
};

