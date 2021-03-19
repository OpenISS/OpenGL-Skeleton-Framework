#version 330 core
in vec3 vertexColor;
uniform vec3 color = vec3(1.0, 1.0, 1.0);
out vec4 FragColor;
void main()
{
    FragColor = vec4(vertexColor.r * color.r, vertexColor.g * color.g, vertexColor.b * color.b, 1.0f);
}