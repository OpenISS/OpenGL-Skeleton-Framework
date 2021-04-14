#include "scene_graph.h"

#include "../resources.h"
#include "../shader.h"
#include "../world.h"

void SceneGraph::Render(World& world, RenderPass pass)
{
    Module::Render(world, pass);

    world.renderingMode->SetupPolygonMode(RenderMode::Triangle); // Reset polygon mode before & after
    glm::mat4 stack = glm::mat4(1.0f);
    walkNode(world, pass, root, stack);
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

void SceneGraph::walkNode(World& world, RenderPass pass, Node& node, glm::mat4 stack)
{
    if (node.visible)
    {
        // The stack object is a copy on the stack, can safely modify and pass forward
        stack *= node.getTransform();
        node.render(world, pass, stack);

        for (auto child : node)
        {
            walkNode(world, pass, *child, stack);
        }
    }
}
