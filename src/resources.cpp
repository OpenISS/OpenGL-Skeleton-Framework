#include "resources.h"

float Resources::unitSize = 0.25f;
Mesh Resources::unitCube;
Mesh Resources::quad;
Shader Resources::basicShader;
glm::vec3 Resources::colorWhite = glm::vec3(1.0f, 1.0f, 1.0f);

void Resources::initialize()
{
    // Unit cube
    unitCube.vertices = {
        {glm::vec3(-0.5f, -0.5f, -0.5f), Resources::colorWhite}, // bot left  (back)
        {glm::vec3( 0.5f, -0.5f, -0.5f), Resources::colorWhite}, // bot right (back)
        {glm::vec3( 0.5f,  0.5f, -0.5f), Resources::colorWhite}, // top right (back)
        {glm::vec3(-0.5f,  0.5f, -0.5f), Resources::colorWhite}, // top left  (back)
        {glm::vec3(-0.5f, -0.5f,  0.5f), Resources::colorWhite}, // bot left  (front)
        {glm::vec3( 0.5f, -0.5f,  0.5f), Resources::colorWhite}, // bot right (front)
        {glm::vec3( 0.5f,  0.5f,  0.5f), Resources::colorWhite}, // top right (front)
        {glm::vec3(-0.5f,  0.5f,  0.5f), Resources::colorWhite}  // top left  (front)
    };
    unitCube.indices = {
        1, 0, 3, 1, 3, 2,
        5, 1, 2, 5, 2, 6,
        4, 5, 6, 4, 6, 7,
        0, 4, 7, 0, 7, 3,
        2, 3, 7, 2, 7, 6,
        5, 4, 0, 5, 0, 1
    };
    unitCube.setDrawingMode(DrawMode::INDEXED);
    unitCube.createGPUBuffers();

    // Quad
    quad.vertices = {
        {glm::vec3(-0.5f,  0.5f,  0.0f), Resources::colorWhite}, // top left
        {glm::vec3( 0.5f, -0.5f,  0.0f), Resources::colorWhite}, // bot right
        {glm::vec3( 0.5f,  0.5f,  0.0f), Resources::colorWhite}, // top right

        {glm::vec3(-0.5f,  0.5f,  0.0f), Resources::colorWhite}, // top right
        {glm::vec3(-0.5f, -0.5f,  0.0f), Resources::colorWhite}, // bot left
        {glm::vec3( 0.5f, -0.5f,  0.0f), Resources::colorWhite}  // bot right
    };

    quad.setDrawingMode(DrawMode::VERTEX);
    quad.createGPUBuffers();

    // Basic shader
    const char* vertexSrc =  R""""(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);
out vec3 vertexColor;
void main()
{
    vertexColor = aColor;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)"""";

    const char* fragmentSrc = R""""(
#version 330 core
in vec3 vertexColor;
uniform vec3 color = vec3(1.0, 1.0, 1.0);
out vec4 FragColor;
void main()
{
    FragColor = vec4(vertexColor.r * color.r, vertexColor.g * color.g, vertexColor.b * color.b, 1.0f);
}
)"""";

    basicShader.create(vertexSrc, fragmentSrc);
    basicShader.setColor(Resources::colorWhite);
}
