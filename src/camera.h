#pragma once

#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
    glm::vec3 m_position;		// camera position
    glm::vec3 m_direction;	    // direction the camera is looking at
    const glm::vec3 m_up;	    // camera relative up position in the world
    float m_fov;				// angle of the camera's field-of-view, in degrees
    float m_aspect;		        // ratio between the width and height of the viewport
    float m_near;			    // distance between the camera and the near image plane
    float m_far;			    // distance between the camera and the far image plane

public:

    Camera(const float aspect,
           const glm::vec3& position = glm::vec3(),
           const glm::vec3& direction = glm::vec3(0.00001f, 0.0f, -1.0f),
           const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
           const float fov = 45.0f,
           const float near = 0.01f,
           const float far = 100.0f)
            : m_position(position), m_up(up)
    {
        setAspectRatio(aspect);
        setFov(fov);
        setFarPlane(far);
        setNearPlane(near);
        setDirection(direction);
    }

    //======================== Output Vectors / Matrices ========================//

    glm::vec3 forward() const {
        return getDirection();
    }

    // right direction of camera
    glm::vec3 right() const {
        return glm::cross(m_direction, m_up);
    }

    // up direction of camera
    glm::vec3 up() const {
        return m_up;
    }

    // projection matrix
    glm::mat4 projection() const {
        return glm::perspective(m_fov, m_aspect, m_near, m_far);
    }

    // view matrix
    glm::mat4 view() const {
        return glm::lookAt(m_position, m_position + m_direction, m_up);
    }

    //======================== Getters / Setters ========================//


    glm::vec3 getPosition() const {
        return m_position;
    }

    void setPosition(const glm::vec3& position) {
        m_position = position;
    }

    void translate(const glm::vec3& movement) {
        m_position += movement;
    }

    glm::vec3 getDirection() const {
        return m_direction;
    }

    void setDirection(const glm::vec3& direction) {
        if (direction == glm::vec3())
            throw std::range_error("direction vector cannot be zeroed");
        m_direction = glm::normalize(direction);
    }

    void setDirection(const float yaw, const float pitch, bool debug = false) {
        // Lab Code not great
        /*float beta = yaw, clamp = 89.0f,
              alpha = glm::radians(std::max(-clamp, std::min(clamp, verticalAngle)));

        if (yaw > 360) {
            beta = glm::radians(horizontalAngle - 360);
        } else if (yaw < -360) {
            beta = glm::radians(horizontalAngle + 360);
        }
        m_direction = glm::vec3(cosf(alpha)*cosf(beta), sinf(alpha), -cosf(alpha)*sinf(beta));
        std::cout << "Angles horz/vert: " << beta << ", " << alpha << std::endl;

        */

        // internet code top kek
        m_direction = glm::vec3(
                glm::rotate(glm::rotate(glm::mat4(1.0f),  // identity matrix around horizontal angle and up
                                        yaw,
                                        m_up),
                            pitch, // result of horizontal rotation around vertical and right vectors
                            right()
                ) * glm::vec4(m_direction, 0.0f) // multiply against original direction
        );

        if (debug) {
            std::cout << "Yaw, Pitch: " << yaw << ", " << pitch << std::endl;
            std::cout << "Direction: " << m_direction.x << ", " << m_direction.y << ", " << m_direction.z << std::endl;
        }
    }

    float getAspectRatio() const {
        return m_aspect;
    }

    void setAspectRatio(const float aspect) {
        if (aspect <= 0.f)
            throw std::range_error("aspect ratio must be + and not 0");
        m_aspect = aspect;
    }

    float getFov() const {
        return m_fov;
    }

    void setFov(const float fov) {
        if (fov <= 0.f && fov >= 180.f)
            throw std::range_error("fov must be between 0 and 180 degrees");
        m_fov = glm::radians(fov);
    }

    float getNearPlane() const {
        return m_near;
    }

    void setNearPlane(const float near) {
        if (near <= 0.f)
            throw std::range_error("near plane must be + and not 0");
        if (near >= m_far)
            throw std::range_error("near plane can't exceed far plane");
        m_near = near;
    }
    
    float getFarPlane() const {
        return m_far;
    }

    void setFarPlane(const float far) {
        if (far <= 0.f)
            throw std::range_error("far plane must be + and not 0");
        if (far <= m_near)
            throw std::range_error("far plane can't be closer than near plane");
        this->m_far = far;
    }

};