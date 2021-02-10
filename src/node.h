#pragma once
#include <glm/glm.hpp>
#include <algorithm>
#include <vector>

class Node
{
public:

    virtual glm::mat4 getTransform()
    {
        return transform;
    };

    virtual void render(World& world, glm::mat4& matrixStack) {};

    void addChild(Node& child)
    {
        children.push_back(&child);
    }

    Node* getChild(int index) {
        return children.at(index);
    }

    void removeChild(Node& child)
    {
        auto found = std::find(children.begin(), children.end(), &child);
        if (found != children.end())
            children.erase(found);
    }

    std::vector<Node*>::iterator beginChildren()
    {
        return children.begin();
    }
    std::vector<Node*>::const_iterator beginChildren() const
    {
        return children.begin();
    }

    std::vector<Node*>::iterator endChildren()
    {
        return children.end();
    }
    std::vector<Node*>::const_iterator endChildren() const
    {
        return children.end();
    }

    glm::mat4 transform = glm::mat4(1.0);

protected:

    std::vector<Node*> children;
};
