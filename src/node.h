#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <vector>

class Node
{
public:

    ~Node() {
        for (auto child: children) {
            delete child;
        }
    }

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

    glm::vec3 up() {
        return glm::normalize(transform * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
    }

    glm::vec3 right() {
        return glm::normalize(transform * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
    }

    glm::vec3 forward() {
        return glm::normalize(transform * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
    }

    void scale(float scalar = 1.0f) {
        transform = glm::scale(transform, glm::vec3(scalar));
    }

    void scaleStep(float step, bool up = true) {
        if (up) {
            scale(1.0f + step);
        } else {
            scale(1.0f - step);
        }
    }

    void rotate(float degrees, glm::vec3 axis) {
        transform = glm::rotate(transform, glm::radians(degrees), axis);
    }

    void translate(glm::vec3 v) {
        transform = glm::translate(transform, v);
    }

    void translate(glm::vec2 v) {
        translate(glm::vec3(v, 0.f));
    }

    void translate(float x = 0.f, float y = 0.f) {
        translate(glm::vec3(x, y, 0.f));
    }

    glm::mat4 transform = glm::mat4(1.0);

protected:

    std::vector<Node*> children;
};
