#pragma once
#include "../thirdparty/imgui/imgui.h"
#include "../module.h"

class ImGuiIntegration : public Module
{
public:

    MODULE_CONSTRUCTOR(ImGuiIntegration)

    void Startup(World& world) override;

    void Shutdown(World& world) override;

    void PreRender(World& world);

    void PostRender(World& world);

    bool wantCaptureMouse();
    bool wantCaptureKeyboard();
};
