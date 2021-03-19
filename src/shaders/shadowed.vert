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