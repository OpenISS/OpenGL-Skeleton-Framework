#pragma once
#include "../thirdparty/imgui/imgui.h"
#include "../modules/imgui_integration.h"
#include "../module.h"
#include "../world.h"

class TestImGuiIntegration : public Module
{
public:

    void Startup(World& world) override
    {
        world.imgui->enabled = true;
    }

    void Render(World& world) override
    {
        if (world.imgui->enabled)
            ImGui::ShowDemoWindow();
    }
};
