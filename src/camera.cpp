#include "camera.h"

#include <stdexcept>
#include <iostream>

//================================== Camera Vectors ==================================//

glm::vec3 Camera::forward() const {
    return getDirection();
}

// right direction of camera
glm::vec3 Camera::right() const {
    return glm::cross(Camera::forward(), Camera::up());
}

// up direction of camera
glm::vec3 Camera::up() const {
    return Camera::m_up;
}

//================================ Camera Matrices ================================//

// projection matrix
glm::mat4 Camera::projection() const {
    return glm::perspective(m_fov, m_aspect, m_near, m_far);
}

// view matrix
glm::mat4 Camera::view() const {
    return glm::lookAt(m_position, m_position + m_direction, m_up);
}

//============================= Cam Position Updates =============================//

void Camera::setPosition(const glm::vec3& position) {
    m_position = position;
}

void Camera::translate(const glm::vec3& movement) {
    m_position += movement;
}

//============================ Cam Direction Updates ============================//

void Camera::setDirection(const glm::vec3& direction) {
    if (direction == glm::vec3())
        throw std::range_error("direction vector cannot be zeroed");
    m_direction = glm::normalize(direction);
}

void Camera::setDirection(const float yaw, const float pitch) {
    // not sure how to set dir using just angles...
}

void Camera::rotate(const float yaw, const float pitch) {
    // rotate by yaw angle around up
    glm::mat4 horizontal = glm::rotate(glm::mat4(1.0f), yaw, up());
    // rotate by pitch angle around right
    glm::mat4 vertical   = glm::rotate(glm::mat4(1.0f), pitch, right());
    // multiply together the change matrix with the original
    setDirection( horizontal * vertical * glm::vec4(m_direction, 0.0f));
}

//============================ Basic Attrib Setters ============================//

void Camera::setAspectRatio(const float aspect) {
    if (aspect <= 0.f)
        throw std::range_error("aspect ratio must be + and not 0");
    m_aspect = aspect;
}

void Camera::setFov(const float fov) {
    if (fov <= 0.f && fov >= 180.f)
        throw std::range_error("fov must be between 0 and 180 degrees");
    m_fov = glm::radians(fov);
}

void Camera::setNearPlane(const float near) {
    if (near <= 0.f)
        throw std::range_error("near plane must be + and not 0");
    if (near >= m_far)
        throw std::range_error("near plane can't exceed far plane");
    m_near = near;
}

void Camera::setFarPlane(const float far) {
    if (far <= 0.f)
        throw std::range_error("far plane must be + and not 0");
    if (far <= m_near)
        throw std::range_error("far plane can't be closer than near plane");
    this->m_far = far;
}