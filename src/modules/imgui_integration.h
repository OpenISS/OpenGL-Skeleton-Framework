#pragma once
#include "../thirdparty/imgui/imgui.h"
#include "../module.h"

class ImGuiIntegration : public Module
{
public:

    void Startup(World& world) override;

    void Shutdown(World& world) override;

    void PreRender(World& world);

    void PostRender(World& world);

    bool wantCaptureMouse();
    bool wantCaptureKeyboard();

    bool enabled = false;
};
