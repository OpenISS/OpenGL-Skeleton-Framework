#pragma once
#include <glm/glm.hpp>
#include "../module.h"
#include "../node.h"

class World;

/**
 * This is the hiearchical modelling system.
 * 
 * The hierarchy is composed of Node objects.
 * A node can have any amount of children.
 * A node's transform is propagated recursively onto all of its children.
 * 
 * Node subtypes can represent different scene objects (ex NodeModel).
 * 
 * @see Node
 * @see NodeModel
 */
class SceneGraph : public Module
{
public:

    void Render(World& world) override;
    void addChild(Node& child);
    void removeChild(Node& child);

    /// The starting point of the hiearachy
    Node root;

protected:

    /// Recursively walks a node's children to resolving their transforms and render them
    void walkNode(World& world, Node& node, glm::mat4 stack);
};
