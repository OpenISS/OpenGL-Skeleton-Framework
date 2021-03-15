#pragma once
#include "../thirdparty/imgui/imgui.h"
#include "../modules/imgui_integration.h"
#include "../module.h"
#include "../world.h"

class TestImGuiIntegration : public Module
{
public:

    MODULE_CONSTRUCTOR(TestImGuiIntegration)

    void Render(World& world, RenderPass pass) override
    {
        if (world.imgui->getEnabled() && pass == RenderPass::Color)
            ImGui::ShowDemoWindow();
    }
};
