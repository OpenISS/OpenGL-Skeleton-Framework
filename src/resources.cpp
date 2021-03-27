#include "resources.h"

const float Resources::unitSize = 0.25f;
Mesh Resources::unitCube;
Mesh Resources::quad;
Mesh Resources::halfCylinder;
Shader Resources::basicShader;
Shader Resources::basicTexturedShader;
Shader Resources::basicShadowedShader;
Shader Resources::litShader;
Shader Resources::shadowCastShader;
const glm::vec3 Resources::colorWhite = glm::vec3(1.0f, 1.0f, 1.0f);
Texture Resources::whiteTexture = Texture("assets/white.png");
Material Resources::unshadedWhiteMaterial;
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

        {glm::vec3(-0.5f,  0.5f,  0.0f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)}, // Top left
        {glm::vec3(-0.5f, -0.5f,  0.0f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // Bot left
        {glm::vec3( 0.5f, -0.5f,  0.0f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)}  // Bot right
    });

    // Cylinder
    // Generation algo is original - one angular slice at a time
    int circlePoints = 32; // Resolution of end-cap circles
    for (int i = 1; i <= circlePoints; i++)
    {
        float angle0 = glm::radians(90.0f) + glm::pi<float>() * (float) (i - 1) / static_cast<float>(circlePoints); // From 90 to 270 degrees
        float angle1 = glm::radians(90.0f) + glm::pi<float>() * (float) i / static_cast<float>(circlePoints);
        float circleX0 = glm::cos(angle0) * 0.5f; // Multiplication by 0.5 for a radius of 0.5 instead of 1.0
        float circleY0 = glm::sin(angle0) * 0.5f;
        float circleX1 = glm::cos(angle1) * 0.5f;
        float circleY1 = glm::sin(angle1) * 0.5f;

        glm::vec2 uvCap0 = glm::vec2(-circleX0, circleY0 + 0.5f);
        glm::vec2 uvCap1 = glm::vec2(-circleX1, circleY1 + 0.5f);
        glm::vec3 normTube0 = glm::normalize(glm::vec3(0.0f, circleY0, circleX0));
        glm::vec3 normTube1 = glm::normalize(glm::vec3(0.0f, circleY1, circleX1));
        float progress0 = (i - 1) / static_cast<float>(circlePoints);
        float progress1 = i / static_cast<float>(circlePoints);

        // Left cap pizza slice
        halfCylinder.vertices.push_back({glm::vec3(-0.5f, circleY0, circleX0), Resources::colorWhite, glm::vec3(-1.0f, 0.0f, 0.0f), uvCap0});
        halfCylinder.vertices.push_back({glm::vec3(-0.5f, circleY1, circleX1), Resources::colorWhite, glm::vec3(-1.0f, 0.0f, 0.0f), uvCap1});
        halfCylinder.vertices.push_back({glm::vec3(-0.5f, 0.0f, 0.0f), Resources::colorWhite, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.5f)});

        // Right cap pizza slice
        halfCylinder.vertices.push_back({glm::vec3(0.5f, circleY0, circleX0), Resources::colorWhite, glm::vec3(1.0f, 0.0f, 0.0f), uvCap0});
        halfCylinder.vertices.push_back({glm::vec3(0.5f, 0.0f, 0.0f), Resources::colorWhite, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.5f)});
        halfCylinder.vertices.push_back({glm::vec3(0.5f, circleY1, circleX1), Resources::colorWhite, glm::vec3(1.0f, 0.0f, 0.0f), uvCap1});

        // Tube quad
        halfCylinder.vertices.push_back({glm::vec3(-0.5f, circleY0, circleX0), Resources::colorWhite, normTube0, glm::vec2(0.0f, progress0)});
        halfCylinder.vertices.push_back({glm::vec3(0.5f, circleY0, circleX0), Resources::colorWhite, normTube0, glm::vec2(0.25f, progress0)});
        halfCylinder.vertices.push_back({glm::vec3(-0.5f, circleY1, circleX1), Resources::colorWhite, normTube1, glm::vec2(0.0f, progress1)});
        halfCylinder.vertices.push_back({glm::vec3(-0.5f, circleY1, circleX1), Resources::colorWhite, normTube1, glm::vec2(0.0f, progress1)});
        halfCylinder.vertices.push_back({glm::vec3(0.5f, circleY0, circleX0), Resources::colorWhite, normTube0, glm::vec2(0.25f, progress0)});
        halfCylinder.vertices.push_back({glm::vec3(0.5f, circleY1, circleX1), Resources::colorWhite, normTube1, glm::vec2(0.25f, progress1)});
    }
    // Quad
    halfCylinder.vertices.push_back({glm::vec3(-0.5f,  0.5f,  0.0f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)}); // Top left
    halfCylinder.vertices.push_back({glm::vec3( 0.5f, -0.5f,  0.0f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.25f, 0.0f)}); // Bot right
    halfCylinder.vertices.push_back({glm::vec3( 0.5f,  0.5f,  0.0f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.25f, 1.0f)}); // Top right
    halfCylinder.vertices.push_back({glm::vec3(-0.5f,  0.5f,  0.0f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)}); // Top left
    halfCylinder.vertices.push_back({glm::vec3(-0.5f, -0.5f,  0.0f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)}); // Bot left
    halfCylinder.vertices.push_back({glm::vec3( 0.5f, -0.5f,  0.0f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.25f, 0.0f)}); // Bot right

    halfCylinder.setDrawingMode(DrawMode::VERTEX);
    halfCylinder.setPolygonMode(GL_TRIANGLES);
    halfCylinder.uploadBuffersToGPU();

    basicShader.load("color");
    basicShader.activate();
    basicShader.setColor(Resources::colorWhite);
    shaders.push_back(&basicShader);

    basicTexturedShader.load("textured");
    basicTexturedShader.activate();
    basicTexturedShader.setColor(Resources::colorWhite);
    shaders.push_back(&basicTexturedShader);

    basicShadowedShader.load("shadowed");
    basicShadowedShader.activate();
    basicShadowedShader.receivesShadows = true;
    basicShadowedShader.setColor(Resources::colorWhite);
    basicShadowedShader.setCustomInt("shadowMap", 8);
    shaders.push_back(&basicShadowedShader);

    litShader.load("lit");
    litShader.activate();
    litShader.needsLight = true;
    litShader.receivesShadows = true;
    litShader.setColor(Resources::colorWhite);
    litShader.setCustomInt("diffuseTexture", 0);
    litShader.setCustomInt("specularTexture", 1);
    litShader.setCustomInt("shadowMap", 8);
    shaders.push_back(&litShader);

    shadowCastShader.load("shadow_cast");
    shadowCastShader.activate();
    shadowCastShader.needsCamera = false;
    shadowCastShader.castsShadows = true;
    shaders.push_back(&shadowCastShader);

    whiteTexture.loadTexture();

    unshadedWhiteMaterial.ambientIntensity = 1.0f;
    unshadedWhiteMaterial.diffuseIntensity = 0.0f;
    unshadedWhiteMaterial.specularIntensity = 0.0f;
}

const std::vector<const Shader*>& Resources::getShaders()
{
    return shaders;
}

void Resources::useTexture(Texture* texture, int slot)
{
    if (texture == nullptr)
        whiteTexture.useTexture(slot);
    else
        texture->useTexture(slot);
}
