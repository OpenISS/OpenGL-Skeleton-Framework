#include "resources.h"

Mesh Resources::unitCube;
Shader Resources::basicShader;
glm::vec3 Resources::colorWhite = glm::vec3(1.0f, 1.0f, 1.0f);

void Resources::initialize()
{
    // Unit cube
    unitCube.vertices = {
        {glm::vec3(-0.5f, -0.5f, -0.5f), Resources::colorWhite}, 
        {glm::vec3( 0.5f, -0.5f, -0.5f), Resources::colorWhite}, 
        {glm::vec3( 0.5f,  0.5f, -0.5f), Resources::colorWhite}, 
        {glm::vec3(-0.5f,  0.5f, -0.5f), Resources::colorWhite},
        {glm::vec3(-0.5f, -0.5f,  0.5f), Resources::colorWhite}, 
        {glm::vec3( 0.5f, -0.5f,  0.5f), Resources::colorWhite}, 
        {glm::vec3( 0.5f,  0.5f,  0.5f), Resources::colorWhite}, 
        {glm::vec3(-0.5f,  0.5f,  0.5f), Resources::colorWhite}
    };
    unitCube.indices = {
        0, 1, 3, 3, 1, 2,
        1, 5, 2, 2, 5, 6,
        5, 4, 6, 6, 4, 7,
        4, 0, 7, 7, 0, 3,
        3, 2, 7, 7, 2, 6,
        4, 5, 0, 0, 5, 1
    };
    unitCube.setDrawingMode(DrawMode::INDEXED);
    unitCube.createGPUBuffers();

    // Basic shader
    const char* vertexSrc =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;"
        "layout (location = 1) in vec3 aColor;"
        "uniform mat4 modelMatrix = mat4(1.0);"
        "uniform mat4 viewMatrix = mat4(1.0);"
        "uniform mat4 projectionMatrix = mat4(1.0);"
        "out vec3 vertexColor;"
        "void main()"
        "{"
        "   vertexColor = aColor;"
        "   gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);"
        "}";

    const char* fragmentSrc =
        "#version 330 core\n"
        "in vec3 vertexColor;"
        "uniform vec3 color = vec3(1.0, 1.0, 1.0);"
        "out vec4 FragColor;"
        "void main()"
        "{"
        "   FragColor = vec4(vertexColor.r * color.r, vertexColor.g * color.g, vertexColor.b * color.b, 1.0f);"
        "}";
    basicShader.create(vertexSrc, fragmentSrc);
    basicShader.setColor(Resources::colorWhite);
}
