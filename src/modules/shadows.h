#pragma once
#include <GL/glew.h>
#include "../light_data.h"
#include "../module.h"
#include "../resources.h"
#include "../shader.h"

// TODO:
// * Bias to fix shadow acne
// * Spot light support
class Shadows : public Module
{
public:

    MODULE_CONSTRUCTOR(Shadows)

    void Startup(World& world) override
    {
        // Create and setup FBO + depth texture

        glGenFramebuffers(1, &depthMapFBO);
        glGenTextures(1, &depthMap);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // Clamp to max depth outside shadow map
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);  

        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Shutdown(World& world) override
    {
        glDeleteFramebuffers(1, &depthMapFBO);
        glDeleteTextures(1, &depthMap);
    }

    void PreRender(World& world)
    {
        if (light == nullptr)
            return;

        glViewport(0, 0, width, height);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);

        // Enable front-face culling to fix peter panning
        glCullFace(GL_FRONT);
        glEnable(GL_CULL_FACE);

        glActiveTexture(GL_TEXTURE8);
        glBindTexture(GL_TEXTURE_2D, depthMap);

        // Directional only at the moment, TODO spotlight
        glm::mat4 lightProjection = glm::ortho(-size, size, -size, size, 1.0f, size * 2.0f); // Cube with side = size
        glm::mat4 lightView = glm::lookAt(light->direction * -size, glm::vec3(0.0f), glm::vec3( 0.0f, 1.0f, 0.0f));
        glm::mat4 lightSpaceMatrix = lightProjection * lightView;

        for (auto shader : Resources::getShaders())
        {
            if (shader->castsShadows || shader->receivesShadows)
            {
                shader->activate();
                shader->setLightSpaceMatrix(lightSpaceMatrix);
            }
        }
    }

    void setLight(const LightData& light)
    {
        this->light = &light;
    }

protected:

    const LightData* light = nullptr;
    int width = 1024;
    int height = 1024;
    float size = 15.0f;

    unsigned int depthMapFBO;
    unsigned int depthMap;
};
