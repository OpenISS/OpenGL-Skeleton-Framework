#pragma once
#include <vector>
#include "mesh.h"
#include "shader.h"
#include "material.h"
#include "texture.h"

/**
 * Commonly used constants and resources.
 */
class Resources
{
public:

    static void initialize();

    /// Returns the list of all shaders used in the application, can be used to set uniforms globally for example
    static const std::vector<const Shader*>& getShaders();

    static void useTexture(Texture* texture, int slot = 0);

    /// Scales all meshes and layouts used in assignments
    static const float unitSize;

    /// A simple unit cube (indexed mesh), size 1 in all dimensions (ex: -0.5 to 0.5 in x axis)
    static Mesh unitCube;

    /// A simple quad (not indexed mesh), size 1 in xy dimensions (ex: -0.5 to 0.5 in x axis)
    static Mesh quad;

    /// Simple unlit shader, supports vertex color and uniform tint color + model, view, projection matrices
    static Shader basicShader;

    static Shader basicTexturedShader;

    static Shader basicShadowedShader;

    static Shader litShader;

    static Shader shadowCastShader;

    static const glm::vec3 colorWhite;

    static Texture whiteTexture;

    static Material unshadedWhiteMaterial;

protected:

    static std::vector<const Shader*> shaders;
};
