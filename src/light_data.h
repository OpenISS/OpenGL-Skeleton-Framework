#pragma once
#include <glm/glm.hpp>

// Imspired by https://learnopengl.com/Lighting/Light-casters
class LightData
{
public:

    enum class Type
    {
        Directional,    // Sun
        Point,          // Candle
        Spot            // Flashlight
    }

    Type type = Type::Point;

    glm::vec3 ambientColor = glm::vec3(0.0f);
    glm::vec3 diffuseColor = glm::vec3(1.0f);
    glm::vec3 specularColor = glm::vec3(1.0f);

    float constantAttenuation = 1.0f;
    float linearAttenuation = 0.09;
    float quadraticAttenuation = 0.032;

    glm::vec3 position = glm::vec3(0.0f);               // For point and spot lights
    glm::vec3 direction = glm::vec3(1.0f, 0.0f, 0.0f);  // For directional and spot lights
    float angle = glm::pi / 4.0f;                       // For spot light, in radians, 45 degrees by default
}
