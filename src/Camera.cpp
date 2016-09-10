#include "Camera.h"

#include <vector>

#include "GL.h"

struct Camera::PrivateData
{
    Camera::Type type;

    vec3 position;
    vec3 front;
    vec3 up;
    vec3 worldUp;
    vec3 rotation;
    vec3 right;

    mat4 viewMatrix;
    mat4 projectionMatrix;
};

Camera::Camera(vec3 position, vec3 up, float rotationX, float rotationY):_data(new PrivateData())
{
    _data->type = Type::NONE;
    _data->position = position;
    _data->worldUp = up;
    _data->rotation = vec3(rotationX, rotationY, 0.0f);
    _data->front = vec3(0, 0, -1.0f);
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

void Camera::setPerspective(float fieldOfView, float aspect, float nearPlane, float farPlane)
{
    _data->type = Camera::Type::PERSPECTIVE;
    _data->projectionMatrix = glm::perspective(fieldOfView, aspect, nearPlane, farPlane);
}

Camera::Type Camera::getType() const
{
    return _data->type;
}

void Camera::setCameraFront(const vec3 &front)
{
    _data->front = front;
}

const Camera::vec3& Camera::getRotation() const
{
    return _data->rotation;
}

void Camera::setRotation(const vec3 &rotation)
{
    _data->rotation = rotation;
}

const Camera::mat4& Camera::getViewMatrix() const
{
    return _data->viewMatrix;
}

const Camera::mat4& Camera::getProjectionMatrix() const
{
    return _data->projectionMatrix;
}

Camera::mat4 Camera::getViewProjectionMatrix() const
{
    return _data->projectionMatrix * _data->viewMatrix;
}

void Camera::updateCameraVectors()
{
    vec3 front;
    front.x = cos(glm::radians(_data->rotation.y)) * cos(glm::radians(_data->rotation.x));
    front.y = sin(glm::radians(_data->rotation.x));
    front.z = sin(glm::radians(_data->rotation.y)) * cos(glm::radians(_data->rotation.x));
    _data->front = glm::normalize(front);

    _data->right = glm::normalize(glm::cross(_data->front, _data->worldUp));
    _data->up    = glm::normalize(glm::cross(_data->right, _data->front));
    _data->viewMatrix = glm::lookAt(_data->position, _data->position + _data->front, _data->up);
}

