#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <vector>

class Node
{
public:

    ~Node()
    {
        for (auto child: children)
        {
            delete child;
        }
    }

    virtual const glm::mat4& getTransform() const
    {
        return transform;
    };

    virtual void render(World& world, const glm::mat4& matrixStack) {};

    void addChild(Node& child)
    {
        children.push_back(&child);
    }

    void removeChild(Node& child)
    {
        auto found = std::find(children.begin(), children.end(), &child);
        if (found != children.end())
            children.erase(found);
    }

    size_t numChildren() const
    {
        return children.size();
    }

    Node* getChild(int index)
    {
        return children.at(index);
    }

    Node* getChild(int index) const
    {
        return children.at(index);
    }

    std::vector<Node*>::iterator begin()
    {
        return children.begin();
    }
    std::vector<Node*>::const_iterator begin() const
    {
        return children.begin();
    }

    std::vector<Node*>::iterator end()
    {
        return children.end();
    }
    std::vector<Node*>::const_iterator end() const
    {
        return children.end();
    }

    glm::vec3 right() const
    {
        return glm::normalize(glm::vec3(transform[0]));
    }

    glm::vec3 up() const
    {
        return glm::normalize(glm::vec3(transform[1]));
    }

    glm::vec3 forward() const
    {
        return glm::normalize(glm::vec3(transform[2]));
    }

    void scale(float scalar = 1.0f)
    {
        transform = glm::scale(transform, glm::vec3(scalar));
    }

    void scaleStep(float step)
    {
        scale(1.0f + step);
    }

    void rotate(float degrees, const glm::vec3& axis)
    {
        transform = glm::rotate(transform, glm::radians(degrees), axis);
    }

    void translate(const glm::vec3& v)
    {
        transform = glm::translate(transform, v);
    }

    void translate(const glm::vec2& v)
    {
        translate(glm::vec3(v, 0.0f));
    }

    void translate(float x = 0.0f, float y = 0.0f)
    {
        translate(glm::vec3(x, y, 0.0f));
    }

    glm::mat4 transform = glm::mat4(1.0f);

protected:

    std::vector<Node*> children;
};
