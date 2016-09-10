#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include "mathlib.h"

class Camera
{
public:
    typedef glm::vec3 vec3;
    typedef glm::mat4 mat4;

    enum class Type
    {
        NONE,
        ORTHO,
        PERSPECTIVE
    };

    Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), float rotationX = 0.0f, float rotationY = 0.0f);

    ~Camera();

    void setOrtho(float zoomX, float zoomY, float nearPlane, float farPlane);

    void setPerspective(float fieldOfView, float aspect, float nearPlane, float farPlane);

    Type getType() const;

    void setCameraFront(const vec3 &front);

    const vec3& getRotation() const;

    void setRotation(const vec3 &rotation);

    const mat4& getViewMatrix() const;

    const mat4& getProjectionMatrix() const;

    mat4 getViewProjectionMatrix() const;

private:
    void updateCameraVectors();

    struct PrivateData;

    PrivateData *_data;
};

#endif
