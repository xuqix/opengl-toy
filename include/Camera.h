#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include "mathlib.h"

class Camera
{
public:
    typedef glm::Vec3 Vec3;
    typedef glm::Mat4 Mat4;

    enum class Type
    {
        NONE,
        ORTHO,
        PERSPECTIVE
    };

    Camera(Vec3 position = Vec3(0.0f, 0.0f, 0.0f), Vec3 up = Vec3(0.0f, 1.0f, 0.0f), float rotationX = 0.0f, float rotationY = 0.0f);

    ~Camera();

    void setOrtho(float zoomX, float zoomY, float nearPlane, float farPlane);

    void setPerspective(float fieldOfView, float aspect, float nearPlane, float farPlane);

    Type getType() const;

    void setCameraFront(const Vec3 &front);

    const Vec3& getRotation() const;

    void setRotation(const Vec3 &rotation);

    const Mat4& getViewMatrix() const;

    const Mat4& getProjectionMatrix() const;

    Mat4 getViewProjectionMatrix() const;

private:
    void updateCameraVectors();

    struct PrivateData;

    PrivateData *_data;
};

#endif
