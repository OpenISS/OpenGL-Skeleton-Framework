#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../module.h"

/// OpenGL polygon mode for rendering
enum class RenderMode
{
    Point,
    Line,
    Triangle
};

/**
 * Sets OpenGL polygon mode.
 * 
 * @see RenderMode
 */
class RenderingMode : public Module
{
public:

    void SetupPolygonMode(RenderMode polygonMode)
    {
        curMode = polygonMode;
        SetupPolygonMode();
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
