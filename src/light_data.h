#pragma once
#include <glm/glm.hpp>


// Lighting constants

// Make sure to keep this constant up to date in .glsl files
#define MAX_ACTIVE_LIGHTS 8

#define TEXTURE_SLOT_DIFFUSE 0

#define TEXTURE_SLOT_SPECULAR 1

#define TEXTURE_SLOT_SHADOWMAPS 8


// Inspired by https://learnopengl.com/Lighting/Light-casters
class LightData
{
public:

    enum class Type
    {
        Directional,    // Sun
        Point,          // Candle
        Spot            // Flashlight
    };

    bool enabled = true;

    bool shadowsEnabled = true;
    float shadowsRange = 15.0f;
    float shadowsBias = 0.007f; // Can fix shadow acne
    glm::mat4 shadowsMatrix = glm::mat4(1.0f);

    Type type = Type::Point;

    glm::vec3 ambientColor = glm::vec3(1.0f);
    glm::vec3 diffuseColor = glm::vec3(1.0f);
    glm::vec3 specularColor = glm::vec3(1.0f);

    float ambientIntensity = 0.0f;
    float diffuseIntensity = 1.0f;
    float specularIntensity = 1.0f;

    float constantAttenuation = 1.0f;
    float linearAttenuation = 0.09f;
    float quadraticAttenuation = 0.032f;

    glm::vec3 position = glm::vec3(0.0f);               // For point and spot lights
    glm::vec3 direction = glm::vec3(1.0f, 0.0f, 0.0f);  // For directional and spot lights
    float angle = 90.0f;                                // For spot light, in degrees
};
