#pragma once
#include "../thirdparty/imgui/imgui.h"
#include "../modules/imgui_integration.h"
#include "../module.h"
#include "../world.h"

class ModuleManagerUI : public Module
{
public:

    MODULE_CONSTRUCTOR(ModuleManagerUI)

    void Render(World& world, RenderPass pass) override
    {
        if (world.imgui->getEnabled() && pass == RenderPass::Color)
        {
            ImGui::Begin("Modules", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

            ImGui::Text("Close/Open UI with 'M' key.");

            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();

            if (ImGui::BeginTable("modules", 2, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersInner))
            {
                for (size_t row = 0; row < world.modules.size(); row++)
                {
                    Module* module = world.modules[row];

                    // Skip this module, don't want user to be able to lock himself out of this menu
                    if (dynamic_cast<ModuleManagerUI*>(module) != nullptr)
                        continue;

                    ImGui::PushID(static_cast<int>(row));

                    ImGui::TableNextRow();

                    ImGui::TableNextColumn();
                    ImGui::Text("%s", module->getName().c_str());

                    ImGui::TableNextColumn();
                    bool bEnabled = module->getEnabled();
                    if (ImGui::Checkbox("Enabled", &bEnabled))
                        module->setEnabled(bEnabled);

                    ImGui::PopID();
                }
                ImGui::EndTable();
            }

            ImGui::End();
        }
    }

protected:

};
