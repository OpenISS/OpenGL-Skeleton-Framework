#include "scene_graph.h"

#include "../world.h"

void SceneGraph::Render(World& world)
{
    Module::Render(world);

    world.renderingMode->SetupPolygonMode(RenderMode::Triangle); // Reset polygon mode before & after
    glm::mat4 stack = glm::mat4(1.0f);
    walkNode(world, root, stack);
    world.renderingMode->SetupPolygonMode(RenderMode::Triangle);
}

void SceneGraph::addChild(Node& child)
{
    root.addChild(child);
}

void SceneGraph::removeChild(Node& child)
{
    root.removeChild(child);
}

void SceneGraph::walkNode(World& world, Node& node, glm::mat4 stack)
{
    // The stack object is a copy on the stack, can safely modify and pass forward
    stack *= node.getTransform();
    node.render(world, stack);

    for (auto child : node)
    {
        walkNode(world, *child, stack);
    }
}
