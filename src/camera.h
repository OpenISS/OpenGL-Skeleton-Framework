#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
    glm::vec3 m_position{};		// camera position
    glm::vec3 m_direction{};	// direction the camera is looking at
    const glm::vec3 m_up{};	    // camera relative up position in the world
    float m_fov{};				// angle of the camera's field-of-view, in degrees
    float m_aspect{};		    // ratio between the width and height of the viewport
    float m_near{};			    // distance between the camera and the near image plane
    float m_far{};			    // distance between the camera and the far image plane

public:

    Camera(const float aspect,
                   const glm::vec3& position = glm::vec3(),
                   const glm::vec3& direction = glm::vec3(0.00001f, 0.0f, -1.0f),
                   const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
                   const float fov = 45.0f,
                   const float near = 0.01f,
                   const float far = 100.0f)
            : m_up(up), m_position(position)
    {
        setAspectRatio(aspect);
        setFov(fov);
        setFarPlane(far);
        setNearPlane(near);
        setDirection(direction);
    }

    glm::vec3 forward() const;
    glm::vec3 right() const;
    glm::vec3 up() const;

    glm::mat4 projection() const;
    glm::mat4 view() const;

    glm::vec3 getPosition() const { return m_position; }
    glm::vec3 getDirection() const { return m_direction; }

    float getFov() const { return m_fov; }
    float getAspectRatio() const { return m_aspect; }
    float getNearPlane() const { return m_near; }
    float getFarPlane() const { return m_far; }

    void setPosition(const glm::vec3&);
    void translate(const glm::vec3&);

    void setDirection(const glm::vec3&);
    void setDirection(float yaw, float pitch);
    void rotate(float yaw = 0.0f, float pitch = 0.0f);

    void setAspectRatio(float);
    void setFov(float);
    void setNearPlane(float);
    void setFarPlane(float);

};