#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aUV;

uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

uniform vec2 uvScale = vec2(1.0, 1.0);

out vec3 worldPos;
out vec3 vertexColor;
out vec3 worldNormal;
out vec2 texCoords;

void main()
{
    worldPos = vec3(modelMatrix * vec4(aPos, 1.0));
    gl_Position = projectionMatrix * viewMatrix * vec4(worldPos, 1.0);

    vertexColor = aColor;
    texCoords = aUV * uvScale;
    worldNormal = normalize(mat3(transpose(inverse(modelMatrix))) * aNormal); 
}
