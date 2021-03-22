#version 330 core

in vec3 worldPos;
in vec4 lightSpacePos;
in vec3 vertexColor;
in vec3 worldNormal;
in vec2 texCoords;

uniform vec3 viewPosition = vec3(0.0, 0.0, 0.0);
uniform mat4 lightSpaceMatrix = mat4(1.0);
uniform float bias = 0.0;

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
uniform sampler2D shadowMap;

out vec4 fragColor;

void main()
{
    float gamma = 2.2;

    // Lighting
    {
        vec3 normal = normalize(worldNormal);
        vec3 viewDir = normalize(viewPosition - worldPos);

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
    }

    // Shadows
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

        fragColor *= (1.0 - shadow);
    }

    // Gamma correction (to sRGB)
    fragColor.rgb = pow(fragColor.rgb, vec3(1.0 / gamma));
}
