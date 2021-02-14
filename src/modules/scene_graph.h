#pragma once
#include <glm/glm.hpp>
#include "../module.h"
#include "../node.h"

class World;

class SceneGraph : public Module
{
public:

    virtual void Render(World& world);
    void addChild(Node& child);
    void removeChild(Node& child);

    Node root;

protected:

    void walkNode(World& world, Node& node, glm::mat4 stack);
};
