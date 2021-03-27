#version 330 core

in vec3 vertexColor;

uniform vec3 ambientColor = vec3(1.0, 1.0, 1.0);

out vec4 fragColor;

void main()
{
    fragColor = vec4(vertexColor * ambientColor, 1.0);
}
