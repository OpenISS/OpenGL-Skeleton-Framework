#version 330 core

in vec3 vertexColor;
in vec4 posLightSpace;

uniform sampler2D shadowMap;
uniform vec3 ambientColor = vec3(1.0, 1.0, 1.0);
uniform mat4 lightSpaceMatrix = mat4(1.0);
uniform float bias = 0.0;

out vec4 fragColor;

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

    fragColor = vec4(vertexColor * ambientColor, 1.0);
    fragColor *= (1.0 - shadow);
}
