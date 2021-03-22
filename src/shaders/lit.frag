#version 330 core

in vec3 worldPos;
in vec3 vertexColor;
in vec3 worldNormal;
in vec2 texCoords;

uniform vec3 viewPosition = vec3(0.0, 0.0, 0.0);

uniform vec3 lightPosition = vec3(1.0, 1.0, 1.0);
uniform vec3 lightAmbient = vec3(1.0, 1.0, 1.0);
uniform vec3 lightDiffuse = vec3(1.0, 1.0, 1.0);
uniform vec3 lightSpecular = vec3(1.0, 1.0, 1.0);
uniform float lightConstantAttenuation = 1.0;
uniform float lightLinearAttenuation = 0.09;
uniform float lightQuadraticAttenuation = 0.032;

uniform vec3 ambientColor = vec3(1.0, 1.0, 1.0);
uniform vec3 diffuseColor = vec3(1.0, 1.0, 1.0);
uniform vec3 specularColor = vec3(1.0, 1.0, 1.0);
uniform float shininess = 32.0;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

out vec4 fragColor;

void main()
{
    vec3 normal = normalize(worldNormal);
    vec3 viewDir = normalize(viewPosition - worldPos);

    float gamma = 2.2;
    vec3 diffuseSample = pow(texture(diffuseTexture, texCoords).rgb, vec3(gamma)); // Gamma correction (to linear)
    vec3 specularSample = texture(specularTexture, texCoords).rgb;

    vec3 lightDir = normalize(lightPosition - worldPos);
    float diffuse = max(dot(normal, lightDir), 0.0);

    // Phong
    // vec3 reflectDir = reflect(-lightDir, normal);
    // float specular = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    // Blinn-Phong
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float specular = pow(max(dot(normal, halfwayDir), 0.0), shininess);

    float distance = length(lightPosition - worldPos);
    float attenuation = 1.0 / (lightConstantAttenuation + lightLinearAttenuation * distance + lightQuadraticAttenuation * (distance * distance));    

    vec3 ambientColor = ambientColor + lightAmbient * attenuation;
    vec3 diffuseColor = lightDiffuse * diffuse * diffuseSample * diffuseColor * attenuation;
    vec3 specularColor = lightSpecular * specular * specularSample * specularColor * attenuation;

    fragColor = vec4((ambientColor + diffuseColor + specularColor) * vertexColor, 1.0);

    // Gamma correction (to sRGB)
    fragColor.rgb = pow(fragColor.rgb, vec3(1.0 / gamma));
}
