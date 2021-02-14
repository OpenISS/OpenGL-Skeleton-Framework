#include "scene_graph.h"

#include "../world.h"

void SceneGraph::Render(World& world)
{
    Module::Render(world);

    world.renderingMode->SetupPolygonMode(RenderMode::Triangle);
    glm::mat4 stack = glm::mat4(1.0f); // Identity matrix
    walkNode(world, root, stack);
    world.renderingMode->SetupPolygonMode(RenderMode::Triangle);
}

void SceneGraph::addChild(Node& child)
{
    root.addChild(child);
}

void SceneGraph::walkNode(World& world, Node& node, glm::mat4 stack)
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
