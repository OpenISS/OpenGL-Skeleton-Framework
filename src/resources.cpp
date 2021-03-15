#include "resources.h"

const float Resources::unitSize = 0.25f;
Mesh Resources::unitCube;
Mesh Resources::quad;
Shader Resources::basicShader;
Shader Resources::basicShadowedShader;
Shader Resources::shadowCastShader;
const glm::vec3 Resources::colorWhite = glm::vec3(1.0f, 1.0f, 1.0f);
std::vector<const Shader*> Resources::shaders;

void Resources::initialize()
{
    // Unit cube
    unitCube.setBuffers(
    {
        {glm::vec3(-0.5f, -0.5f, -0.5f), Resources::colorWhite}, // Bot left  (back)
        {glm::vec3( 0.5f, -0.5f, -0.5f), Resources::colorWhite}, // Bot right (back)
        {glm::vec3( 0.5f,  0.5f, -0.5f), Resources::colorWhite}, // Top right (back)
        {glm::vec3(-0.5f,  0.5f, -0.5f), Resources::colorWhite}, // Top left  (back)
        {glm::vec3(-0.5f, -0.5f,  0.5f), Resources::colorWhite}, // Bot left  (front)
        {glm::vec3( 0.5f, -0.5f,  0.5f), Resources::colorWhite}, // Bot right (front)
        {glm::vec3( 0.5f,  0.5f,  0.5f), Resources::colorWhite}, // Top right (front)
        {glm::vec3(-0.5f,  0.5f,  0.5f), Resources::colorWhite}  // Top left  (front)
    },
    {
        1, 0, 3, 1, 3, 2,
        5, 1, 2, 5, 2, 6,
        4, 5, 6, 4, 6, 7,
        0, 4, 7, 0, 7, 3,
        2, 3, 7, 2, 7, 6,
        5, 4, 0, 5, 0, 1
    });

    // Quad
    quad.setBuffers(
    {
        {glm::vec3(-0.5f,  0.5f,  0.0f), Resources::colorWhite}, // Top left
        {glm::vec3( 0.5f, -0.5f,  0.0f), Resources::colorWhite}, // Bot right
        {glm::vec3( 0.5f,  0.5f,  0.0f), Resources::colorWhite}, // Top right

        {glm::vec3(-0.5f,  0.5f,  0.0f), Resources::colorWhite}, // Top right
        {glm::vec3(-0.5f, -0.5f,  0.0f), Resources::colorWhite}, // Bot left
        {glm::vec3( 0.5f, -0.5f,  0.0f), Resources::colorWhite}  // Bot right
    });

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
    shaders.push_back(&basicShader);

    // Basic shadowed shader
    const char* basicShadowedVertexSrc =  R""""(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);
uniform mat4 lightSpaceMatrix = mat4(1.0);
out vec3 vertexColor;
out vec4 posLightSpace;
void main()
{
    vec3 worldPos = vec3(modelMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0));
    gl_Position = projectionMatrix * viewMatrix * vec4(worldPos.x, worldPos.y, worldPos.z, 1.0);

    vertexColor = aColor;
    posLightSpace = lightSpaceMatrix * vec4(worldPos.x, worldPos.y, worldPos.z, 1.0);
}
)"""";

    const char* basicShadowedFragmentSrc = R""""(
#version 330 core
in vec3 vertexColor;
in vec4 posLightSpace;
uniform sampler2D shadowMap;
uniform vec3 color = vec3(1.0, 1.0, 1.0);
uniform mat4 lightSpaceMatrix = mat4(1.0);
out vec4 FragColor;
void main()
{
    // Perform perspective divide
    vec3 projCoords = posLightSpace.xyz / posLightSpace.w;
    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // Get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // Check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;
    if (projCoords.z > 1.0)
        shadow = 0.0;

    FragColor = vec4(vertexColor.r * color.r, vertexColor.g * color.g, vertexColor.b * color.b, 1.0f);
    FragColor *= (1.0 - shadow);
}
)"""";

    basicShadowedShader.create(basicShadowedVertexSrc, basicShadowedFragmentSrc);
    basicShadowedShader.receivesShadows = true;
    basicShadowedShader.setColor(Resources::colorWhite);
    basicShadowedShader.setCustomInt("shadowMap", 8);
    shaders.push_back(&basicShadowedShader);

    // Shadowmap shader
    const char* shadowCastVertexSrc = R"""(
#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 lightSpaceMatrix = mat4(1.0);
uniform mat4 modelMatrix = mat4(1.0);
void main()
{
    gl_Position = lightSpaceMatrix * modelMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)""";

const char* shadowCastFragmentSrc = R"""(
#version 330 core
void main()
{
    // gl_FragDepth = gl_FragCoord.z;
}
)""";

    shadowCastShader.create(shadowCastVertexSrc, shadowCastFragmentSrc);
    shadowCastShader.needsCamera = false;
    shadowCastShader.castsShadows = true;
    shaders.push_back(&shadowCastShader);
}

const std::vector<const Shader*>& Resources::getShaders()
{
    return shaders;
}
