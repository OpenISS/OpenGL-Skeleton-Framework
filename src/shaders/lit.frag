#version 330 core

struct Light
{
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float cutOff;
    float outerCutOff;
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
};

#define NR_LIGHTS 8
uniform Light lights[NR_LIGHTS];

in vec3 worldPos;
in vec4 lightSpacePos;
in vec3 vertexColor;
in vec3 worldNormal;
in vec2 texCoords;

uniform vec3 viewPosition = vec3(0.0, 0.0, 0.0);
uniform mat4 lightSpaceMatrix = mat4(1.0);
uniform float bias = 0.0;
uniform int shadowLightIndex = 0;

uniform vec3 ambientColor = vec3(1.0, 1.0, 1.0);
uniform vec3 diffuseColor = vec3(1.0, 1.0, 1.0);
uniform vec3 specularColor = vec3(1.0, 1.0, 1.0);
uniform float shininess = 32.0;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D shadowMap;

out vec4 fragColor;

vec3 calcLight(Light light, vec3 normal, vec3 viewDir, vec3 diffuseSample, vec3 specularSample)
{
    vec3 lightDir = normalize(light.position - worldPos);
    float diffuse = max(dot(normal, lightDir), 0.0);

    // Blinn-Phong
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float specular = pow(max(dot(normal, halfwayDir), 0.0), shininess);

    float distance = length(light.position - worldPos);
    float attenuation = 1.0 / (light.constantAttenuation + light.linearAttenuation * distance + light.quadraticAttenuation * (distance * distance));    

    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 ambientColor = ambientColor + light.ambient * diffuseSample * diffuseColor;
    vec3 diffuseColor = light.diffuse * diffuse * diffuseSample * diffuseColor * attenuation * intensity;
    vec3 specularColor = light.specular * specular * specularSample * specularColor * attenuation * intensity;

    return vec3(ambientColor + diffuseColor + specularColor);
}

void main()
{
    float gamma = 2.2;

    // Shadows
    float shadowAttenuation = 1.0;
    {
        // Perform perspective divide
        vec3 projCoords = lightSpacePos.xyz / lightSpacePos.w;
        // Transform to [0,1] range
        projCoords = projCoords * 0.5 + 0.5;
        // Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
        float closestDepth = texture(shadowMap, projCoords.xy).r;
        // Get depth of current fragment from light's perspective
        float currentDepth = projCoords.z;
        // Check whether current frag pos is in shadow
        // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

        // PCF
        float shadow = 0.0;
        vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
        for (int x = -1; x <= 1; ++x)
        {
            for (int y = -1; y <= 1; ++y)
            {
                float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
                shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;
            }
        }
        shadow /= 9.0;

        // Keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
        if (projCoords.z > 1.0)
            shadow = 0.0;

        shadowAttenuation = 1.0 - shadow;
    }

    // Lighting
    {
        vec3 normal = normalize(worldNormal);
        vec3 viewDir = normalize(viewPosition - worldPos);

        vec3 diffuseSample = pow(texture(diffuseTexture, texCoords).rgb, vec3(gamma)); // Gamma correction (to linear)
        vec3 specularSample = texture(specularTexture, texCoords).rgb;

        fragColor = vec4(0.0, 0.0, 0.0, 1.0);

        for (int i = 0; i < NR_LIGHTS; i++)
        {
            vec3 lightContribution = calcLight(lights[i], normal, viewDir, diffuseSample, specularSample);
            if (i == shadowLightIndex)
                lightContribution *= shadowAttenuation;
            fragColor.rgb += lightContribution;
        }

        fragColor.rgb *= vertexColor;
    }

    // Gamma correction (to sRGB)
    fragColor.rgb = pow(fragColor.rgb, vec3(1.0 / gamma));
}
