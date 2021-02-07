#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../module.h"

enum class RenderMode
{
    Point,
    Line,
    Triangle
};

class RenderingMode : public Module
{
public:

    virtual void OnKey(World& world, int key, int action, int mods)
    {
        Module::OnKey(world, key, action, mods);

        if (action == GLFW_PRESS)
        {
            if (key == GLFW_KEY_P)
            {
                curMode = RenderMode::Point;
            }
            else if (key == GLFW_KEY_L)
            {
                curMode = RenderMode::Line;
            }
            else if (key == GLFW_KEY_T)
            {
                curMode = RenderMode::Triangle;
            }
        }
    }

    void SetupPolygonMode()
    {
        GLenum mode;
        if (curMode == RenderMode::Point)
        {
            mode = GL_POINT;
            glEnable(GL_PROGRAM_POINT_SIZE);
            glPointSize(4.0f);
        }
        else if (curMode == RenderMode::Line)
        {
            mode = GL_LINE;
        }
        else // RenderMode::Triangle
        {
            mode = GL_FILL;
        }
        glPolygonMode(GL_FRONT_AND_BACK, mode);
    }

protected:

    RenderMode curMode = RenderMode::Triangle;
};
