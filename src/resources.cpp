#include "resources.h"

#include "texture.h"

const float Resources::unitSize = 0.25f;
Mesh Resources::unitCube;
Mesh Resources::quad;
Shader Resources::basicShader;
Shader Resources::basicTexturedShader;
Shader Resources::basicShadowedShader;
Shader Resources::shadowCastShader;
const glm::vec3 Resources::colorWhite = glm::vec3(1.0f, 1.0f, 1.0f);
Texture Resources::whiteTexture = Texture("assets/white.png", GL_RGBA);
std::vector<const Shader*> Resources::shaders;

void Resources::initialize()
{
    // Unit cube
    unitCube.setBuffers(
    {
        {glm::vec3(-0.5f, -0.5f, -0.5f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f)}, // [Back] Bot right
        {glm::vec3( 0.5f, -0.5f, -0.5f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)}, // [Back] Bot left
        {glm::vec3( 0.5f,  0.5f, -0.5f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f)}, // [Back] Top left
        {glm::vec3(-0.5f,  0.5f, -0.5f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)}, // [Back] Top right

        {glm::vec3(-0.5f, -0.5f,  0.5f), Resources::colorWhite, glm::vec3( 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // [Front] Bot left
        {glm::vec3( 0.5f, -0.5f,  0.5f), Resources::colorWhite, glm::vec3( 0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)}, // [Front] Bot right
        {glm::vec3( 0.5f,  0.5f,  0.5f), Resources::colorWhite, glm::vec3( 0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)}, // [Front] Top right
        {glm::vec3(-0.5f,  0.5f,  0.5f), Resources::colorWhite, glm::vec3( 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)}, // [Front] Top left

        {glm::vec3(-0.5f,  0.5f,  0.5f), Resources::colorWhite, glm::vec3( 0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // [Top] Bot left
        {glm::vec3( 0.5f,  0.5f,  0.5f), Resources::colorWhite, glm::vec3( 0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)}, // [Top] Bot right
        {glm::vec3( 0.5f,  0.5f, -0.5f), Resources::colorWhite, glm::vec3( 0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)}, // [Top] Top right
        {glm::vec3(-0.5f,  0.5f, -0.5f), Resources::colorWhite, glm::vec3( 0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)}, // [Top] Top left

        {glm::vec3(-0.5f, -0.5f, -0.5f), Resources::colorWhite, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // [Bot] Bot left
        {glm::vec3( 0.5f, -0.5f, -0.5f), Resources::colorWhite, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)}, // [Bot] Bot right
        {glm::vec3( 0.5f, -0.5f,  0.5f), Resources::colorWhite, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f)}, // [Bot] Top right
        {glm::vec3(-0.5f, -0.5f,  0.5f), Resources::colorWhite, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f)}, // [Bot] Top left

        {glm::vec3(-0.5f, -0.5f, -0.5f), Resources::colorWhite, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // [Left] Bot left
        {glm::vec3(-0.5f, -0.5f,  0.5f), Resources::colorWhite, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)}, // [Left] Bot right
        {glm::vec3(-0.5f,  0.5f,  0.5f), Resources::colorWhite, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)}, // [Left] Top right
        {glm::vec3(-0.5f,  0.5f, -0.5f), Resources::colorWhite, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)}, // [Left] Top left

        {glm::vec3( 0.5f, -0.5f,  0.5f), Resources::colorWhite, glm::vec3( 1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // [Left] Bot left
        {glm::vec3( 0.5f, -0.5f, -0.5f), Resources::colorWhite, glm::vec3( 1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)}, // [Left] Bot right
        {glm::vec3( 0.5f,  0.5f, -0.5f), Resources::colorWhite, glm::vec3( 1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)}, // [Left] Top right
        {glm::vec3( 0.5f,  0.5f,  0.5f), Resources::colorWhite, glm::vec3( 1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)}  // [Left] Top left
    },
    {
         1,  0,  3,  1,  3,  2, // Back
         4,  5,  6,  4,  6,  7, // Front
         8,  9, 10,  8, 10, 11, // Top
        12, 13, 14, 12, 14, 15, // Bot
        16, 17, 18, 16, 18, 19, // Left
        20, 21, 22, 20, 22, 23  // Right
    });

    // Quad
    quad.setBuffers(
    {
        {glm::vec3(-0.5f,  0.5f,  0.0f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)}, // Top left
        {glm::vec3( 0.5f, -0.5f,  0.0f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)}, // Bot right
        {glm::vec3( 0.5f,  0.5f,  0.0f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)}, // Top right

        {glm::vec3(-0.5f,  0.5f,  0.0f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)}, // Top right
        {glm::vec3(-0.5f, -0.5f,  0.0f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // Bot left
        {glm::vec3( 0.5f, -0.5f,  0.0f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)}  // Bot right
    });

    basicShader.load("shader");
    basicShader.setColor(Resources::colorWhite);
    shaders.push_back(&basicShader);

    basicTexturedShader.load("textured");
    basicTexturedShader.setColor(Resources::colorWhite);
    shaders.push_back(&basicTexturedShader);

    basicShadowedShader.load("shadowed");
    basicShadowedShader.receivesShadows = true;
    basicShadowedShader.setColor(Resources::colorWhite);
    basicShadowedShader.setCustomInt("shadowMap", 8);
    shaders.push_back(&basicShadowedShader);

    shadowCastShader.load("shadow_cast");
    shadowCastShader.needsCamera = false;
    shadowCastShader.castsShadows = true;
    shaders.push_back(&shadowCastShader);

    whiteTexture.loadTexture();
}

const std::vector<const Shader*>& Resources::getShaders()
{
    return shaders;
}
