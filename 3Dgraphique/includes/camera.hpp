#ifndef CAMERA_3D_HPP
#define CAMERA_3D_HPP
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum Camera_movement {
    FORWARD,
    BACKWARD,
    RIGHT,
    LEFT
};

// Default camera value
const float PITCH = 0.0f;
const float YAW = 90.0f;
const float FOV = 45.0f;
const float sensitivity = 0.1f;
const float speed = 2.5f;
class camera
{
private:
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 cameraRight;
    glm::vec3 worldUp;
    float Pitch;
    float Yaw;
    float Fov;
    float movementSensitivity;
    float movementSpeed;

    void updateCameraVector();
public:
    camera(glm::vec3 Pos = glm::vec3(0.0f, 0.0f, 3.0f), 
        glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f), 
        glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f), 
        float pitch = PITCH, float yaw = YAW, float fov = FOV) : movementSensitivity(sensitivity), movementSpeed(speed) 
        {
            cameraPos = Pos;
            cameraFront = Front;
            worldUp = Up;
            Pitch = pitch;
            Yaw = yaw;
            Fov = fov;
            updateCameraVector();
        };
    ~camera(){};
    // get matrix of view space
    glm::mat4 getViewSpace();
    // handle input from keyboard
    void processKeyBoard(Camera_movement direction, float deltaTime);
    // handle movement of mouse, update angle of user's view
    void processMouseMovement(float xOffset, float yOffset);
    // handle scroll of nouse, update the field of view => zoom
    void processMouseScoll(float yOffset);
    void setCameraPos(glm::vec3 cpos);
    void setWorldUp(glm::vec3 cup);
    void setPitch(float p);
    void setYaw(float y);
    void setFov(float f);
    float getPitch(void);
    float getYaw(void);
    float getFov(void);
};
#endif