#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "../light_data.h"
#include "../material.h"
#include "../module.h"
#include "../resources.h"
#include "../world.h"

class TestLitShader : public Module
{
public:

    MODULE_CONSTRUCTOR(TestLitShader)

    void Startup(World& world) override
    {
        world.lights.push_back(&light);

        light.type = LightData::Type::Point;
        light.position = glm::vec3(0.0f, 8.0f, 0.0f);
        light.direction = glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f));
        light.angle = 90.0f;
        light.linearAttenuation *= 0.25f;
        light.quadraticAttenuation *= 0.25f;
        light.shadowsRange = 15.0f;
        light.shadowsBias = 0.007f;

        unlitMaterial = Resources::unshadedWhiteMaterial;

        untexturedSpecularMaterial.diffuseIntensity = 0.0f;
        untexturedSpecularMaterial.shininess = 8.0f;

        crateTexture = Texture("assets/fragile.jpg");
        crateTexture.loadTexture();
        texturedMaterial.diffuseTexture = &crateTexture;

        setEnabled(enabled);
    }

    void setEnabled(bool enabled) override
    {
        this->enabled = enabled;
        light.enabled = enabled;
    }

    void Render(World& world, RenderPass pass) override
    {
        Module::Render(world, pass);

        std::vector<glm::mat4> cubes;
        cubes.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(-6.0f, 0.5f, -3.0f)));
        cubes.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0.5f, -3.0f)));
        cubes.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, -3.0f)));
        cubes.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(6.0f, 0.5f, -3.0f)));
        cubes.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(-6.0f, 0.5f, 0.0f)));
        cubes.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, 0.0f)));
        cubes.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(6.0f, 0.5f, 0.0f)));
        cubes.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(-6.0f, 0.5f, 3.0f)));
        cubes.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, 3.0f)));
        cubes.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(6.0f, 0.5f, 3.0f)));
        cubes.push_back(glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 3.0f, 0.0f)));

        std::vector<Material*> materials;
        materials.push_back(&unlitMaterial);
        materials.push_back(&untexturedSpecularMaterial);
        materials.push_back(&untexturedMaterial);
        materials.push_back(&untexturedMaterial);
        materials.push_back(&texturedMaterial);
        materials.push_back(&texturedMaterial);
        materials.push_back(&texturedMaterial);
        materials.push_back(&texturedMaterial);
        materials.push_back(&texturedMaterial);
        materials.push_back(&texturedMaterial);
        materials.push_back(&texturedMaterial);

        if (pass == RenderPass::Color)
        {
            Resources::litShader.activate();
        }
        else if (pass == RenderPass::Shadow)
        {
            Resources::shadowCastShader.activate();
        }

        for (size_t i = 0; i < cubes.size(); ++i)
        {
            glm::mat4& transform = cubes[i];
            Material& material = *materials[i];

            if (pass == RenderPass::Color)
            {
                Resources::litShader.setModelMatrix(transform);
                Resources::litShader.setMaterial(material);
                Resources::useTexture(material.diffuseTexture, TEXTURE_SLOT_DIFFUSE);
                Resources::useTexture(material.specularTexture, TEXTURE_SLOT_SPECULAR);
            }
            else if (pass == RenderPass::Shadow)
            {
                Resources::shadowCastShader.setModelMatrix(transform);
            }

            Resources::unitCube.draw();
        }
    }

protected:

    LightData light;

    Material unlitMaterial;
    Material untexturedMaterial;
    Material untexturedSpecularMaterial;
    Material texturedMaterial;

    Texture crateTexture;
};
