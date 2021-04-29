#pragma once
#include <GL/glew.h>
#include "../light_data.h"
#include "../module.h"
#include "../resources.h"
#include "../shader.h"

// TODO:
// * Bias + normals algorithm to better fix shadow acne
class Shadows : public Module
{
public:

    MODULE_CONSTRUCTOR(Shadows)

    void Startup(World& world) override
    {
        // Create and setup FBO + depth texture

        glGenTextures(1, &shadowMapsArray);
        glBindTexture(GL_TEXTURE_2D_ARRAY, shadowMapsArray);

        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT, width, height, MAX_ACTIVE_LIGHTS, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, 0);

        // Clamp to max depth outside shadow map
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

        for (int i = 0; i < MAX_ACTIVE_LIGHTS; ++i)
        {
            glGenFramebuffers(1, &depthMapFBO[i]);
            glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO[i]);
            glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMapsArray, 0, i);
        }

        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Shutdown(World& world) override
    {
        for (int i = 0; i < MAX_ACTIVE_LIGHTS; ++i)
        {
            glDeleteFramebuffers(1, &depthMapFBO[i]);
        }
        glDeleteTextures(1, &shadowMapsArray);
    }

    void PreRender()
    {
        if (cullFrontFaces)
        {
            glCullFace(GL_FRONT);
            glEnable(GL_CULL_FACE);
        }
        else
        {
            glCullFace(GL_BACK);
            glDisable(GL_CULL_FACE);
        }
    }

    void clearShadowmap(int lightIndex)
    {
        glViewport(0, 0, width, height);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO[lightIndex]);
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void computeShadowsMatrix(World& world, LightData& light)
    {
        // glm::lookAt breaks if direction and up vector are too similar
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        if (glm::abs(glm::dot(up, light.direction)) >= 0.95f)
            up = glm::vec3(1.0f, 0.0f, 0.0f);

        glm::mat4 lightSpaceMatrix;
        if (light.type == LightData::Type::Directional)
        {
            glm::mat4 lightProjection = glm::ortho(-light.shadowsRange / 2.0f, light.shadowsRange / 2.0f, -light.shadowsRange / 2.0f, light.shadowsRange / 2.0f, 1.0f, light.shadowsRange); // Cube with side = size
            glm::mat4 lightView = glm::lookAt(light.direction * -light.shadowsRange * 0.75f, glm::vec3(0.0f), up);
            lightSpaceMatrix = lightProjection * lightView;
        }
        else
        {
            glm::mat4 lightProjection = glm::perspective(glm::radians(light.angle), (float)width/(float)height, 1.0f, light.shadowsRange);
            glm::mat4 lightView = glm::lookAt(light.position, light.position + light.direction, up);
            lightSpaceMatrix = lightProjection * lightView;
        }

        light.shadowsMatrix = lightSpaceMatrix;

        for (auto shader : Resources::getShaders())
        {
            if (shader->castsShadows)
            {
                shader->activate();
                shader->setLightSpaceMatrix(lightSpaceMatrix);
            }
        }
    }

    void bindShadowMaps()
    {
        glActiveTexture(GL_TEXTURE0 + TEXTURE_SLOT_SHADOWMAPS);
        glBindTexture(GL_TEXTURE_2D_ARRAY, shadowMapsArray);
    }

    bool cullFrontFaces = false; // Can fix peter panning

protected:

    int width = 2048;
    int height = 2048;

    unsigned int depthMapFBO[MAX_ACTIVE_LIGHTS];
    unsigned int shadowMapsArray;
};
