#pragma once
#include <glm/gtx/quaternion.hpp>
#include "material.h"
#include "mesh.h"
#include "node.h"
#include "resources.h"
#include "shader.h"
#include "texture.h"

/**
 * Member of the scene graph, renders a spherical joint
 *
 * @see SceneGraph
 */
class NodeJoint : public NodeModel
{
public:

    NodeJoint(Material& material, Shader& shader, const glm::vec3& point, float radius = 1.f)
        : NodeJoint(Resources::sphere, material, shader, point, radius) {}

    NodeJoint(Mesh& mesh, Material& material, Shader& shader, const glm::vec3& point, float radius = 1.f)
        : NodeJoint(mesh, material, shader)
    {
        setPoint(point, radius);
    }

    NodeJoint(Material& material, Shader& shader)
        : NodeJoint(Resources::sphere, material, shader) {}

    NodeJoint(Mesh& mesh, Material& material, Shader& shader)
    {
        this->mesh = &mesh;
        this->material = &material;
        this->shader = &shader;
    }

    void setPoint(const glm::vec3& point, float radius)
    {
        this->radius = radius;
        setPoint(point);
    }

    void setPoint(const glm::vec3& point)
    {
        transform = glm::mat4(1.0f);
        translate(point);
        scale(radius / 2.0f);
    }
    
    glm::vec3 getPosition() const
    {
        return glm::vec3(transform[3][0], transform[3][1], transform[3][2]);
    }

protected:

    float radius = 1.0f;
};
