#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <algorithm>
#include <vector>

/**
 * This is the most basic node type in the scene graph.
 * 
 * It only serves to group transforms.
 * Extend and override render() to represent other scene objects, like in NodeModel.
 * 
 * @see NodeModel
 * @see SceneGraph
 */
class Node
{
public:

    enum class ShearDirection { X, Y, Z };

    /// Recursively deletes all children as well
    ~Node()
    {
        for (auto child: children)
        {
            delete child;
        }
    }

    /// For read-only purposes, getTransform() is preferred over directly accessing transform because it returns a const reference.
    virtual const glm::mat4& getTransform() const
    {
        return transform;
    };

    /// Does nothing by default. Can be overriden by subclasses for their rendering logic.
    virtual void render(World& world, RenderPass pass, const glm::mat4& matrixStack) {};

    /// O(1)
    void addChild(Node& child)
    {
        children.push_back(&child);
    }

    /// O(n)
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

    /// Right (x) normalized vector of the transform
    glm::vec3 right() const
    {
        return glm::normalize(glm::vec3(transform[0]));
    }

    /// Right (y) normalized vector of the transform
    glm::vec3 up() const
    {
        return glm::normalize(glm::vec3(transform[1]));
    }

    /// Right (z) normalized vector of the transform
    glm::vec3 forward() const
    {
        return glm::normalize(glm::vec3(transform[2]));
    }

    /// Scales the transform equally in all dimensions
    void scale(float scalar = 1.0f)
    {
        transform = glm::scale(transform, glm::vec3(scalar));
    }

    void scale(float x, float y, float z)
    {
        transform = glm::scale(transform, glm::vec3(x, y, z));
    }

    void scale(const glm::vec3& scale)
    {
        transform = glm::scale(transform, scale);
    }

    /// Scales the transform equally in all dimensions, by 1 + step (0.2 => 1.2 and -0.2 => 0.8)
    void scaleStep(float step)
    {
        scale(1.0f + step);
    }

    /// Rotates the transform about an axis (axis doesn't need to be normalized)
    void rotate(float degrees, const glm::vec3& axis)
    {
        transform = glm::rotate(transform, glm::radians(degrees), axis);
    }

    void translate(const glm::vec3& v)
    {
        transform = glm::translate(transform, v);
    }

    /// Translates the transform in x and y dimensions
    void translate(const glm::vec2& v)
    {
        translate(glm::vec3(v, 0.0f));
    }

    void translate(float x = 0.0f, float y = 0.0f, float z = 0.0f)
    {
        translate(glm::vec3(x, y, z));
    }

    void shearX(float y = 0.0f, float z = 0.0f)
    {
        transform = glm::shearX3D(transform, y, z);
    }

    void shearY(float x = 0.0f, float z = 0.0f)
    {
        transform = glm::shearY3D(transform, x, z);
    }

    void shearZ(float x = 0.0f, float y = 0.0f)
    {
        transform = glm::shearZ3D(transform, x, y);
    }

    void shear(float x = 0.0f, float y = 0.0f, ShearDirection direction = ShearDirection::X) {
        if (direction == ShearDirection::X)
            shearX(x, y);
        else if (direction == ShearDirection::Y)
            shearY(x, y);
        else if (direction == ShearDirection::Z)
            shearZ(x, y);
    }

    void shear(glm::mat4& shear) {
        transform *= shear;
    }

    /// Transformation matrix, relative to the parent node
    glm::mat4 transform = glm::mat4(1.0f);

    /// When false, this node and all its children will not be rendered
    bool visible = true;

protected:

    std::vector<Node*> children;
};
