#pragma once
#include "module.h"
#include "world.h"

class TestUnitCube : public Module
{
    virtual void Render(World& world)
    {
        Module::Render(world);

        world.basicShader.activate();
        world.unitCube.draw();
    }
};
