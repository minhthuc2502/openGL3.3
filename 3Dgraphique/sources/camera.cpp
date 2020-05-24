#include "camera.hpp"

void camera::updateCameraVector()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    direction.y = sin(glm::radians(Pitch));
    direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    cameraFront = glm::normalize(direction);
    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}

glm::mat4 camera::getViewSpace()
{
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void camera::processKeyBoard(Camera_movement direction, float deltaTime)
{
    const float cameraSpeed = movementSpeed * deltaTime;
    if(direction == FORWARD)
        cameraPos += cameraSpeed * cameraFront;
    if(direction == BACKWARD)
        cameraPos -= cameraSpeed * cameraFront;
    if(direction == RIGHT)
        cameraPos += cameraRight * cameraSpeed;
    if(direction == LEFT)
        cameraPos -= cameraRight * cameraSpeed; 
}

void camera::processMouseMovement(float xOffset, float yOffset)
{
    xOffset *= movementSensitivity;
    yOffset *= movementSensitivity;
    Yaw -= xOffset;
    Pitch += yOffset;

    if(Pitch > 89.0f)
        Pitch = 89.0f;
    if(Pitch < -89.0f)
        Pitch = -89.0f;
    updateCameraVector();
}

void camera::processMouseScoll(float yOffset)
{
    Fov -= yOffset;
    if(Fov < 1.0f)
        Fov = 1.0f;
    if(Fov > FOV)
        Fov = FOV;
}

void camera::setCameraPos(glm::vec3 cpos)
{
    cameraPos = cpos;
}

void camera::setWorldUp(glm::vec3 cup)
{
    worldUp = cup;
}

void camera::setPitch(float p)
{
    Pitch = p;
}

void camera::setYaw(float y)
{
    Yaw = y;
}

void camera::setFov(float f)
{
    Fov = f;
}

float camera::getPitch(void)
{
    return Pitch;
}

float camera::getYaw(void)
{
    return Yaw;
}

float camera::getFov(void)
{
    return Fov;
}

glm::vec3 camera::getCameraPos(void)
{
    return cameraPos;
}
