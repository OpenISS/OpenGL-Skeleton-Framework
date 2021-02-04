#pragma once
#include "mesh.h"
#include "shader.h"

class Resources
{
public:

    static void initialize();

    static Mesh unitCube;
    static Shader basicShader;
    static glm::vec3 colorWhite;
};
