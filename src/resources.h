#pragma once
#include "mesh.h"
#include "shader.h"

class Resources
{
public:

    static void initialize();

    static float unitSize;
    static Mesh unitCube;
    static Mesh quad;
    static Shader basicShader;
    static glm::vec3 colorWhite;
};
