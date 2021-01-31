#pragma once

class Module
{
public:

    virtual void Startup() {};
    virtual void Shutdown() {};

    virtual void Update(float deltaSeconds) {};
    virtual void Render() {};

    virtual void OnKey(int key, int action, int mods) {};
};
