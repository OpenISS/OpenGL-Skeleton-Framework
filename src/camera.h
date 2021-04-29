#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
 * Abstracts camera transform and projection math.
 * 
 * All camera operations assumed in world space.
 */
class Camera
{
public:

    Camera(
        const float aspect,
        const glm::vec3& position = glm::vec3(),
        const glm::vec3& direction = glm::vec3(0.00001f, 0.0f, -1.0f),
        const glm::vec3& upAxis = glm::vec3(0.0f, 1.0f, 0.0f),
        const float fov = 58.0f,
        const float near = 0.01f,
        const float far = 100.0f):
        position(position),
        upAxis(upAxis)
    {
        setAspectRatio(aspect);
        setFov(fov);
        setFarPlane(far);
        setNearPlane(near);
        setDirection(direction);
    }

    /// Camera facing direction in world space
    glm::vec3 forward() const;

    /// Camera right direction in world space
    glm::vec3 right() const;

    /**
     * The "up" axis of the camera in world space (as used in glm::lookAt()).
     * 
     * This is not the same as the camera up direction.
     * 
     * @see upAxis
     */
    glm::vec3 getUpAxis() const;

    /// Projection matrix
    glm::mat4 projection() const;

    /// View matrix
    glm::mat4 view() const;

    /// Camera position in world space
    glm::vec3 getPosition() const { return position; }

    /// Camera facing direction in world space
    glm::vec3 getDirection() const { return direction; }

    float getFov() const { return fov; }
    float getAspectRatio() const { return aspect; }
    float getNearPlane() const { return near; }
    float getFarPlane() const { return far; }

    /// Teleports the camera in world space
    void setPosition(const glm::vec3& position);

    /// Moves the camera in world space
    void translate(const glm::vec3& movement);

    /// Sets direction in world space, doesn't have to be normalized
    void setDirection(const glm::vec3& direction);

    /// Unimplemented
    void setDirection(float yaw, float pitch);

    /**
     * Rotates by modifying direction. Yaw and pitch are in radians.
     * 
     * Yaw rotates around getUpAxis(). Pitch rotates around right().
     */
    void rotate(float yaw = 0.0f, float pitch = 0.0f);

    /// Sets ratio between the width and height of the viewport, must be > 0
    void setAspectRatio(float);

    /// Sets angle of the camera's field-of-view, in degrees, must respect: 0 < fov < 180
    void setFov(float);

    /// Sets distance between the camera and the near image plane, must respect: 0 < near < far
    void setNearPlane(float);

    /// Sets distance between the camera and the far image plane, must respect: 0 < near < far
    void setFarPlane(float);

protected:

    /// Camera "up" axis in world space, for glm::lookAt(). Normally this is (0, 1, 0) and remains constant.
    const glm::vec3 upAxis;

    glm::vec3 position;
    glm::vec3 direction;
    float fov = 58.f;
    float aspect = 1.3337f;
    float near = 0.01f;
    float far = 100.f;
};
