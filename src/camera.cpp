#include "camera.h"

#include <stdexcept>
#include <iostream>

//================================== Camera Vectors ==================================//

glm::vec3 Camera::forward() const
{
    return getDirection();
}

glm::vec3 Camera::right() const
{
    return glm::cross(forward(), getUpAxis());
}

glm::vec3 Camera::getUpAxis() const
{
    return upAxis;
}

//================================ Camera Matrices ================================//

glm::mat4 Camera::projection() const
{
    return glm::perspective(glm::radians(fov), aspect, near, far);
}

glm::mat4 Camera::view() const
{
    return glm::lookAt(position, position + direction, upAxis);
}

//============================= Cam Position Updates =============================//

void Camera::setPosition(const glm::vec3& position)
{
    this->position = position;
}

void Camera::translate(const glm::vec3& movement)
{
    position += movement;
}

//============================ Cam Direction Updates ============================//

void Camera::setDirection(const glm::vec3& direction)
{
    if (direction == glm::vec3())
        this->direction = direction;
    else
        this->direction = glm::normalize(direction);
}

void Camera::setDirection(const float yaw, const float pitch)
{
    rotate(yaw, pitch);
}

void Camera::rotate(const float yaw, const float pitch)
{
    // Rotate by yaw angle around up
    glm::mat4 horizontal = glm::rotate(glm::mat4(1.0f), yaw, getUpAxis());
    // Rotate by pitch angle around right
    glm::mat4 vertical   = glm::rotate(glm::mat4(1.0f), pitch, right());
    // Multiply together the change matrix with the original
    setDirection( horizontal * vertical * glm::vec4(direction, 0.0f));
}

//============================ Basic Attrib Setters ============================//

void Camera::setAspectRatio(const float aspect)
{
    if (aspect <= 0.0f)
        throw std::range_error("aspect ratio must be + and not 0");
    this->aspect = aspect;
}

void Camera::setFov(const float fov)
{
    if (fov <= 0.0f && fov >= 180.0f)
        throw std::range_error("fov must be between 0 and 180 degrees");
    this->fov = fov;
}

void Camera::setNearPlane(const float near)
{
    if (near <= 0.0f)
        throw std::range_error("near plane must be + and not 0");
    if (near >= far)
        throw std::range_error("near plane can't exceed far plane");
    this->near = near;
}

void Camera::setFarPlane(const float far)
{
    if (far <= 0.0f)
        throw std::range_error("far plane must be + and not 0");
    if (far <= near)
        throw std::range_error("far plane can't be closer than near plane");
    this->far = far;
}
