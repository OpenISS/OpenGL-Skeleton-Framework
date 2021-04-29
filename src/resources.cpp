#include "resources.h"

const float Resources::unitSize = 0.25f;
Mesh Resources::unitCube;
Mesh Resources::inverseCube;
Mesh Resources::quad;
Mesh Resources::cylinder;
Mesh Resources::cone;
Mesh Resources::halfCylinder;
Mesh Resources::sphere;
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

    // Inverse cube
    inverseCube.setBuffers(
    {
        {glm::vec3(-0.5f, -0.5f, -0.5f), Resources::colorWhite, glm::vec3( 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // [Back] Bot right
        {glm::vec3( 0.5f, -0.5f, -0.5f), Resources::colorWhite, glm::vec3( 0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)}, // [Back] Bot left
        {glm::vec3( 0.5f,  0.5f, -0.5f), Resources::colorWhite, glm::vec3( 0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)}, // [Back] Top left
        {glm::vec3(-0.5f,  0.5f, -0.5f), Resources::colorWhite, glm::vec3( 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)}, // [Back] Top right

        {glm::vec3(-0.5f, -0.5f,  0.5f), Resources::colorWhite, glm::vec3( 0.0f, 0.0f,-1.0f), glm::vec2(1.0f, 0.0f)}, // [Front] Bot left
        {glm::vec3( 0.5f, -0.5f,  0.5f), Resources::colorWhite, glm::vec3( 0.0f, 0.0f,-1.0f), glm::vec2(0.0f, 0.0f)}, // [Front] Bot right
        {glm::vec3( 0.5f,  0.5f,  0.5f), Resources::colorWhite, glm::vec3( 0.0f, 0.0f,-1.0f), glm::vec2(0.0f, 1.0f)}, // [Front] Top right
        {glm::vec3(-0.5f,  0.5f,  0.5f), Resources::colorWhite, glm::vec3( 0.0f, 0.0f,-1.0f), glm::vec2(1.0f, 1.0f)}, // [Front] Top left

        {glm::vec3(-0.5f,  0.5f,  0.5f), Resources::colorWhite, glm::vec3( 0.0f,-1.0f, 0.0f), glm::vec2(1.0f, 0.0f)}, // [Top] Bot left
        {glm::vec3( 0.5f,  0.5f,  0.5f), Resources::colorWhite, glm::vec3( 0.0f,-1.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // [Top] Bot right
        {glm::vec3( 0.5f,  0.5f, -0.5f), Resources::colorWhite, glm::vec3( 0.0f,-1.0f, 0.0f), glm::vec2(0.0f, 1.0f)}, // [Top] Top right
        {glm::vec3(-0.5f,  0.5f, -0.5f), Resources::colorWhite, glm::vec3( 0.0f,-1.0f, 0.0f), glm::vec2(1.0f, 1.0f)}, // [Top] Top left

        {glm::vec3(-0.5f, -0.5f, -0.5f), Resources::colorWhite, glm::vec3( 0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)}, // [Bot] Bot left
        {glm::vec3( 0.5f, -0.5f, -0.5f), Resources::colorWhite, glm::vec3( 0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // [Bot] Bot right
        {glm::vec3( 0.5f, -0.5f,  0.5f), Resources::colorWhite, glm::vec3( 0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)}, // [Bot] Top right
        {glm::vec3(-0.5f, -0.5f,  0.5f), Resources::colorWhite, glm::vec3( 0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)}, // [Bot] Top left

        {glm::vec3(-0.5f, -0.5f, -0.5f), Resources::colorWhite, glm::vec3( 1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)}, // [Left] Bot left
        {glm::vec3(-0.5f, -0.5f,  0.5f), Resources::colorWhite, glm::vec3( 1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // [Left] Bot right
        {glm::vec3(-0.5f,  0.5f,  0.5f), Resources::colorWhite, glm::vec3( 1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)}, // [Left] Top right
        {glm::vec3(-0.5f,  0.5f, -0.5f), Resources::colorWhite, glm::vec3( 1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)}, // [Left] Top left

        {glm::vec3( 0.5f, -0.5f,  0.5f), Resources::colorWhite, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)}, // [Left] Bot left
        {glm::vec3( 0.5f, -0.5f, -0.5f), Resources::colorWhite, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // [Left] Bot right
        {glm::vec3( 0.5f,  0.5f, -0.5f), Resources::colorWhite, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)}, // [Left] Top right
        {glm::vec3( 0.5f,  0.5f,  0.5f), Resources::colorWhite, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)}  // [Left] Top left
    },
    {
         0,  1,  3,  3,  1,  2, // Back
         5,  4,  6,  6,  4,  7, // Front
         9,  8, 10,  10, 8, 11, // Top
        13, 12, 14, 14, 12, 15, // Bot
        17, 16, 18, 18, 16, 19, // Left
        21, 20, 22, 22, 20, 23  // Right
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
        float angle0 = glm::radians(0.0f) + glm::pi<float>() * 2.0f * (float) (i - 1) / static_cast<float>(circlePoints); // From 0 to 360 degrees
        float angle1 = glm::radians(0.0f) + glm::pi<float>() * 2.0f * (float) i / static_cast<float>(circlePoints);
        float circleX0 = glm::cos(angle0) * 0.5f; // Multiplication by 0.5 for a radius of 0.5 instead of 1.0
        float circleY0 = glm::sin(angle0) * 0.5f;
        float circleX1 = glm::cos(angle1) * 0.5f;
        float circleY1 = glm::sin(angle1) * 0.5f;

        glm::vec2 uvCap0 = glm::vec2(circleX0 + 0.5f, circleY0 + 0.5f);
        glm::vec2 uvCap1 = glm::vec2(circleX1 + 0.5f, circleY1 + 0.5f);
        glm::vec3 normTube0 = glm::normalize(glm::vec3(0.0f, circleY0, circleX0));
        glm::vec3 normTube1 = glm::normalize(glm::vec3(0.0f, circleY1, circleX1));
        float progress0 = (i - 1) / static_cast<float>(circlePoints);
        float progress1 = i / static_cast<float>(circlePoints);

        // Left cap pizza slice
        cylinder.vertices.push_back({glm::vec3(-0.5f, circleY0, circleX0), Resources::colorWhite, glm::vec3(-1.0f, 0.0f, 0.0f), uvCap0});
        cylinder.vertices.push_back({glm::vec3(-0.5f, circleY1, circleX1), Resources::colorWhite, glm::vec3(-1.0f, 0.0f, 0.0f), uvCap1});
        cylinder.vertices.push_back({glm::vec3(-0.5f, 0.0f, 0.0f), Resources::colorWhite, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.5f, 0.5f)});

        // Right cap pizza slice
        cylinder.vertices.push_back({glm::vec3(0.5f, circleY0, circleX0), Resources::colorWhite, glm::vec3(1.0f, 0.0f, 0.0f), uvCap0});
        cylinder.vertices.push_back({glm::vec3(0.5f, 0.0f, 0.0f), Resources::colorWhite, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.5f, 0.5f)});
        cylinder.vertices.push_back({glm::vec3(0.5f, circleY1, circleX1), Resources::colorWhite, glm::vec3(1.0f, 0.0f, 0.0f), uvCap1});

        // Tube quad
        cylinder.vertices.push_back({glm::vec3(-0.5f, circleY0, circleX0), Resources::colorWhite, normTube0, glm::vec2(0.0f, progress0)});
        cylinder.vertices.push_back({glm::vec3(0.5f, circleY0, circleX0), Resources::colorWhite, normTube0, glm::vec2(1.0f, progress0)});
        cylinder.vertices.push_back({glm::vec3(-0.5f, circleY1, circleX1), Resources::colorWhite, normTube1, glm::vec2(0.0f, progress1)});
        cylinder.vertices.push_back({glm::vec3(-0.5f, circleY1, circleX1), Resources::colorWhite, normTube1, glm::vec2(0.0f, progress1)});
        cylinder.vertices.push_back({glm::vec3(0.5f, circleY0, circleX0), Resources::colorWhite, normTube0, glm::vec2(1.0f, progress0)});
        cylinder.vertices.push_back({glm::vec3(0.5f, circleY1, circleX1), Resources::colorWhite, normTube1, glm::vec2(1.0f, progress1)});
    }

    cylinder.setDrawingMode(DrawMode::VERTEX);
    cylinder.setPolygonMode(GL_TRIANGLES);
    cylinder.uploadBuffersToGPU();

    // Cone
    // Generation algo is original - based on cone
    int circlePointsCone = 32; // Resolution of end-cap circles
    for (int i = 1; i <= circlePointsCone; i++)
    {
        float angle0 = glm::radians(0.0f) + glm::pi<float>() * 2.0f * (float) (i - 1) / static_cast<float>(circlePointsCone); // From 0 to 360 degrees
        float angle1 = glm::radians(0.0f) + glm::pi<float>() * 2.0f * (float) i / static_cast<float>(circlePointsCone);
        float circleX0 = glm::cos(angle0) * 0.5f; // Multiplication by 0.5 for a radius of 0.5 instead of 1.0
        float circleY0 = glm::sin(angle0) * 0.5f;
        float circleX1 = glm::cos(angle1) * 0.5f;
        float circleY1 = glm::sin(angle1) * 0.5f;

        glm::vec2 uvCap0 = glm::vec2(circleX0 + 0.5f, circleY0 + 0.5f);
        glm::vec2 uvCap1 = glm::vec2(circleX1 + 0.5f, circleY1 + 0.5f);
        glm::vec3 normTube0 = glm::normalize(glm::vec3(0.0f, circleY0, circleX0));
        glm::vec3 normTube1 = glm::normalize(glm::vec3(0.0f, circleY1, circleX1));
        float progress0 = (i - 1) / static_cast<float>(circlePointsCone);
        float progress1 = i / static_cast<float>(circlePointsCone);

        // Slope adjustment for normal
        float slopeAngle = -glm::atan(0.5f) + glm::radians(90.0f);
        float slopeXFactor = glm::cos(slopeAngle);
        float slopeYFactor = glm::sin(slopeAngle);
        normTube0 = glm::vec3(slopeXFactor, normTube0.y * slopeYFactor, normTube0.z * slopeYFactor);
        normTube1 = glm::vec3(slopeXFactor, normTube1.y * slopeYFactor, normTube1.z * slopeYFactor);

        // Left cap pizza slice
        cone.vertices.push_back({glm::vec3(-0.5f, circleY0, circleX0), Resources::colorWhite, glm::vec3(-1.0f, 0.0f, 0.0f), uvCap0});
        cone.vertices.push_back({glm::vec3(-0.5f, circleY1, circleX1), Resources::colorWhite, glm::vec3(-1.0f, 0.0f, 0.0f), uvCap1});
        cone.vertices.push_back({glm::vec3(-0.5f, 0.0f, 0.0f), Resources::colorWhite, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.5f, 0.5f)});

        // Tube quad
        cone.vertices.push_back({glm::vec3(-0.5f, circleY0, circleX0), Resources::colorWhite, normTube0, uvCap0});
        cone.vertices.push_back({glm::vec3(0.5f, 0.0f, 0.0f), Resources::colorWhite, normTube0, glm::vec2(0.5f, 0.5f)});
        cone.vertices.push_back({glm::vec3(-0.5f, circleY1, circleX1), Resources::colorWhite, normTube1, uvCap1});
    }

    cone.setDrawingMode(DrawMode::VERTEX);
    cone.setPolygonMode(GL_TRIANGLES);
    cone.uploadBuffersToGPU();

    // Half-cylinder
    // Generation algo is original - based on cylinder
    int circlePointsHalfCylinder = 32; // Resolution of end-cap circles
    for (int i = 1; i <= circlePointsHalfCylinder; i++)
    {
        float angle0 = glm::radians(90.0f) + glm::pi<float>() * (float) (i - 1) / static_cast<float>(circlePointsHalfCylinder); // From 90 to 270 degrees
        float angle1 = glm::radians(90.0f) + glm::pi<float>() * (float) i / static_cast<float>(circlePointsHalfCylinder);
        float circleX0 = glm::cos(angle0) * 0.5f; // Multiplication by 0.5 for a radius of 0.5 instead of 1.0
        float circleY0 = glm::sin(angle0) * 0.5f;
        float circleX1 = glm::cos(angle1) * 0.5f;
        float circleY1 = glm::sin(angle1) * 0.5f;

        glm::vec2 uvCap0 = glm::vec2(-circleX0, circleY0 + 0.5f);
        glm::vec2 uvCap1 = glm::vec2(-circleX1, circleY1 + 0.5f);
        glm::vec3 normTube0 = glm::normalize(glm::vec3(0.0f, circleY0, circleX0));
        glm::vec3 normTube1 = glm::normalize(glm::vec3(0.0f, circleY1, circleX1));
        float progress0 = (i - 1) / static_cast<float>(circlePointsHalfCylinder);
        float progress1 = i / static_cast<float>(circlePointsHalfCylinder);

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
        halfCylinder.vertices.push_back({glm::vec3(0.5f, circleY0, circleX0), Resources::colorWhite, normTube0, glm::vec2(1.0f, progress0)});
        halfCylinder.vertices.push_back({glm::vec3(-0.5f, circleY1, circleX1), Resources::colorWhite, normTube1, glm::vec2(0.0f, progress1)});
        halfCylinder.vertices.push_back({glm::vec3(-0.5f, circleY1, circleX1), Resources::colorWhite, normTube1, glm::vec2(0.0f, progress1)});
        halfCylinder.vertices.push_back({glm::vec3(0.5f, circleY0, circleX0), Resources::colorWhite, normTube0, glm::vec2(1.0f, progress0)});
        halfCylinder.vertices.push_back({glm::vec3(0.5f, circleY1, circleX1), Resources::colorWhite, normTube1, glm::vec2(1.0f, progress1)});
    }
    // Quad
    halfCylinder.vertices.push_back({glm::vec3(-0.5f,  0.5f,  0.0f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)}); // Top left
    halfCylinder.vertices.push_back({glm::vec3( 0.5f, -0.5f,  0.0f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)}); // Bot right
    halfCylinder.vertices.push_back({glm::vec3( 0.5f,  0.5f,  0.0f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)}); // Top right
    halfCylinder.vertices.push_back({glm::vec3(-0.5f,  0.5f,  0.0f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)}); // Top left
    halfCylinder.vertices.push_back({glm::vec3(-0.5f, -0.5f,  0.0f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)}); // Bot left
    halfCylinder.vertices.push_back({glm::vec3( 0.5f, -0.5f,  0.0f), Resources::colorWhite, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)}); // Bot right

    halfCylinder.setDrawingMode(DrawMode::VERTEX);
    halfCylinder.setPolygonMode(GL_TRIANGLES);
    halfCylinder.uploadBuffersToGPU();

    // Sphere
    // Generation algo inspired by https://gist.github.com/zwzmzd/0195733fa1210346b00d - classic UV sphere
    const int lats = 64;
    const int longs = 64;
    for (int i = 1; i <= lats; i++)
    {
        float lat0 = glm::pi<float>() * (-0.5f + (float) (i - 1) / lats); // From -90 degrees to +90 degrees
        float z0  = sin(lat0) * 0.5f; // Multiplication by 0.5 for a radius of 0.5 instead of 1.0
        float zr0 =  cos(lat0) * 0.5f;

        float lat1 = glm::pi<float>() * (-0.5f + (float) i / lats);
        float z1 = sin(lat1) * 0.5f;
        float zr1 = cos(lat1) * 0.5f;

        for (int j = 1; j <= longs; j++)
        {
            float lng0 = 2.0f * glm::pi<float>() * (float) (j - 1) / longs; // From 0 to 360 degrees
            float x0 = cos(lng0);
            float y0 = sin(lng0);

            float lng1 = 2.0f * glm::pi<float>() * (float) j / longs;
            float x1 = cos(lng1);
            float y1 = sin(lng1);

            float progressX0 = 1.0f - (j - 1) / static_cast<float>(longs);
            float progressX1 = 1.0f - j / static_cast<float>(longs);
            float progressY0 = (i - 1) / static_cast<float>(lats);
            float progressY1 = i / static_cast<float>(lats);

            // A quad face of the UV sphere
            sphere.vertices.push_back({glm::vec3(x0 * zr0, z0, y0 * zr0), Resources::colorWhite, glm::normalize(glm::vec3(x0 * zr0, z0, y0 * zr0)), glm::vec2(progressX0, progressY0)});
            sphere.vertices.push_back({glm::vec3(x0 * zr1, z1, y0 * zr1), Resources::colorWhite, glm::normalize(glm::vec3(x0 * zr1, z1, y0 * zr1)), glm::vec2(progressX0, progressY1)});
            sphere.vertices.push_back({glm::vec3(x1 * zr0, z0, y1 * zr0), Resources::colorWhite, glm::normalize(glm::vec3(x1 * zr0, z0, y1 * zr0)), glm::vec2(progressX1, progressY0)});
            sphere.vertices.push_back({glm::vec3(x0 * zr1, z1, y0 * zr1), Resources::colorWhite, glm::normalize(glm::vec3(x0 * zr1, z1, y0 * zr1)), glm::vec2(progressX0, progressY1)});
            sphere.vertices.push_back({glm::vec3(x1 * zr1, z1, y1 * zr1), Resources::colorWhite, glm::normalize(glm::vec3(x1 * zr1, z1, y1 * zr1)), glm::vec2(progressX1, progressY1)});
            sphere.vertices.push_back({glm::vec3(x1 * zr0, z0, y1 * zr0), Resources::colorWhite, glm::normalize(glm::vec3(x1 * zr0, z0, y1 * zr0)), glm::vec2(progressX1, progressY0)});
        }
    }

    sphere.setDrawingMode(DrawMode::VERTEX);
    sphere.setPolygonMode(GL_TRIANGLES);
    sphere.uploadBuffersToGPU();

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
    basicShadowedShader.setCustomInt("shadowMapsArray", TEXTURE_SLOT_SHADOWMAPS);
    shaders.push_back(&basicShadowedShader);

    litShader.load("lit");
    litShader.activate();
    litShader.needsLight = true;
    litShader.receivesShadows = true;
    litShader.setColor(Resources::colorWhite);
    litShader.setCustomInt("diffuseTexture", TEXTURE_SLOT_DIFFUSE);
    litShader.setCustomInt("specularTexture", TEXTURE_SLOT_SPECULAR);
    litShader.setCustomInt("shadowMapsArray", TEXTURE_SLOT_SHADOWMAPS);
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
