#pragma once
#include <glm/glm.hpp>
#include "../module.h"
#include "../node.h"

class SceneGraph : public Module
{
public:

    virtual void Render(World& world)
    {
        Module::Render(world);

        glm::mat4 stack = glm::mat4(1.0f); // Identity matrix
        walkNode(world, root, stack);
    }

    Node root;

protected:

    void walkNode(World& world, Node& node, glm::mat4 stack)
    {
        stack *= node.getTransform();
        node.render(world, stack);

        auto it = node.beginChildren();
        auto end = node.endChildren();
        for (; it != end; ++it)
        {
            Node& child = **it;
            walkNode(world, child, stack);
        }
    }
};
