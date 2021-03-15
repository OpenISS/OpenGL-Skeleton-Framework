#pragma once
#include <glm/glm.hpp>
#include "../light_data.h"
#include "../module.h"
#include "../resources.h"
#include "../world.h"

class TestShadows : public Module
{
public:

    MODULE_CONSTRUCTOR(TestShadows)

    void Startup(World& world) override
    {
        placeholderLight.type = LightData::Type::Point;
        placeholderLight.angle = glm::pi<float>() / 4.0f;
        placeholderLight.position = glm::vec3(0.0f, 10.0f, 0.0f);
        placeholderLight.direction = glm::normalize(glm::vec3(-0.33f, -1.0f, 0.33f));
    }

    void Update(World& world, float deltaSeconds) override
    {
        world.shadows->setLight(placeholderLight);
    }

protected:

    LightData placeholderLight;
};
