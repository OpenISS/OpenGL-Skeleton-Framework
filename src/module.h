#pragma once
class World;

/**
 * A module can receive inputs and update/render, as well as access global world state. Designed to be extended and overriden.
 * 
 * Every major system, assignment feature, and test is implemented as a self-contained module.
 * Modules are managed by the World class.
 * 
 * @see World
 */
class Module
{
public:

    virtual void Startup(World& world) {};
    virtual void Shutdown(World& world) {};

    /// For simulation logic, deltaSeconds provided for framerate-independence
    virtual void Update(World& world, float deltaSeconds) {};

    /// For rendering logic
    virtual void Render(World& world) {};

    virtual void OnKeyPressed(World& world, int key, int mods) {};
    virtual void OnKeyReleased(World& world, int key, int mods) {};
    virtual void OnKey(World& world, int key, int action, int mods) {};

    virtual void OnMouseMoved(World& world, float x, float y) {};
    virtual void OnMousePressed(World& world, int button, int mods) {};
    virtual void OnMouseReleased(World& world, int button, int mods) {};
};
