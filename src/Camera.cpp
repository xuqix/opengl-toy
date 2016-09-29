#include "Camera.h"

#include <vector>

#include "GL.h"

struct Camera::PrivateData
{
    Camera::Type type;

    Vec3 position;
    Vec3 front;
    Vec3 up;
    Vec3 worldUp;
    Vec3 rotation;
    Vec3 right;

    Mat4 viewMatrix;
    Mat4 projectionMatrix;
};

Camera::Camera(Vec3 position, Vec3 up, float rotationX, float rotationY):_data(new PrivateData())
{
    _data->type = Type::NONE;
    _data->position = position;
    _data->worldUp = up;
    _data->rotation = Vec3(rotationX, rotationY, 0.0f);
    _data->front = Vec3(0, 0, -1.0f);
    updateCameraVectors();
}

Camera::~Camera()
{
    delete _data;
}

void Camera::setOrtho(float zoomX, float zoomY, float nearPlane, float farPlane)
{
    _data->type = Camera::Type::ORTHO;
    _data->projectionMatrix = glm::ortho(0.0f, zoomX, 0.0f, zoomY, nearPlane, farPlane);
}

void Camera::setOrtho(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
    _data->type = Camera::Type::ORTHO;
    _data->projectionMatrix = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
}

void Camera::setPerspective(float fieldOfView, float aspect, float nearPlane, float farPlane)
{
    _data->type = Camera::Type::PERSPECTIVE;
    _data->projectionMatrix = glm::perspective(fieldOfView, aspect, nearPlane, farPlane);
}

Camera::Type Camera::getType() const
{
    return _data->type;
}

void Camera::setCameraFront(const Vec3 &front)
{
    _data->front = front;
    updateCameraVectors();
}

const Camera::Vec3& Camera::getCameraFront() const
{
    return _data->front;
}

const Camera::Vec3& Camera::getRotation() const
{
    return _data->rotation;
}

void Camera::setRotation(const Vec3 &rotation)
{
    _data->rotation = rotation;
    updateCameraVectors();
}

const Camera::Mat4& Camera::getViewMatrix() const
{
    return _data->viewMatrix;
}

const Camera::Mat4& Camera::getProjectionMatrix() const
{
    return _data->projectionMatrix;
}

Camera::Mat4 Camera::getViewProjectionMatrix() const
{
    return _data->projectionMatrix * _data->viewMatrix;
}

void Camera::updateCameraVectors()
{
    Vec3 front;
    front.x = cos(glm::radians(_data->rotation.y-90.0f)) * cos(glm::radians(_data->rotation.x));
    front.y = sin(glm::radians(_data->rotation.x));
    front.z = sin(glm::radians(_data->rotation.y-90.0f)) * cos(glm::radians(_data->rotation.x));
    _data->front = glm::normalize(front);

    _data->right = glm::normalize(glm::cross(_data->front, _data->worldUp));
    _data->up    = glm::normalize(glm::cross(_data->right, _data->front));
    _data->viewMatrix = glm::lookAt(_data->position, _data->position + _data->front, _data->up);
}

