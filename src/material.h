#pragma once
#include <glm/glm.hpp>
#include "texture.h"

class Material
{
public:

    glm::vec3 ambientColor = glm::vec3(1.0f);
    glm::vec3 diffuseColor = glm::vec3(1.0f);
    glm::vec3 specularColor = glm::vec3(1.0f);

    float ambientIntensity = 0.0f;
    float diffuseIntensity = 1.0f;
    float specularIntensity = 1.0f;

    float shininess = 32.0f;

    Texture* diffuseTexture = nullptr;
    Texture* specularTexture = nullptr;
};
