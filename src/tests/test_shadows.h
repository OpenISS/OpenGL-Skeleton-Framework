#pragma once
#include <glm/glm.hpp>
#include <vector>
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

    void Render(World& world, RenderPass pass) override
    {
        Module::Render(world, pass);

        std::vector<glm::mat4> cubes;
        cubes.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 4.0f, -6.0f)));
        cubes.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -6.0f)));
        cubes.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, -4.0f, -6.0f)));

        if (pass == RenderPass::Color)
        {
            Resources::basicShadowedShader.activate();
            Resources::basicShadowedShader.setColor(Resources::colorWhite);
        }
        else if (pass == RenderPass::Shadow)
        {
            Resources::shadowCastShader.activate();
        }

        for (glm::mat4& transform : cubes)
        {
            if (pass == RenderPass::Color)
                Resources::basicShadowedShader.setModelMatrix(transform);
            else if (pass == RenderPass::Shadow)
                Resources::shadowCastShader.setModelMatrix(transform);
            Resources::unitCube.draw();
        }
    }

protected:

    LightData placeholderLight;
};
