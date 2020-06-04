#ifndef ROBOT_ARM_HPP
#define ROBOT_ARM_HPP

#include <vector>
#include <glm/glm.hpp>

// Index of each part's model matrix
enum ModelMatIndex {BASE, SHOULDER, BICEP_BELOW, BICEP_ABOVE, WRIST, RAIL, GRIPPERL, GRIPPERR};
enum AngleRotation {ANGLE_SHOULDER, ANGLE_BICEP_BELOW, ANGLE_BICEP_ABOVE, ANGLE_WRIST, ANGLE_RAIL, ANGLE_GRIPPER};

class robot
{
private:
    glm::vec3 positionShoulder;
    glm::vec3 positionBicepBelow;
    glm::vec3 positionBicepAbove;
    glm::vec3 positionWrist;
    glm::vec3 positionRail;
    glm::vec3 positionGripperR;
    glm::vec3 positionGripperL;
    float AngleStepDef;
public:
    float angle[6];                         // angle of rotation for 6 joints
    std::vector<glm::mat4> model;       // model matrix to rotate each part of arm with a angle 
    robot() {
        positionShoulder = glm::vec3(99.0, 113.76, -131.75);
        positionBicepBelow = glm::vec3(102.46, 186.94, -149.04);
        positionBicepAbove = glm::vec3(94.628, 202.13, -109.93);
        positionWrist = glm::vec3(80.021, 187.32, -37.007);
        positionRail = glm::vec3(73.346, 180.38, -3.684);
        positionGripperR = glm::vec3(44.635, 180.34, 6.1495);
        positionGripperL = glm::vec3(96.054, 180.33, 16.45);
        angle[6] = {0};
        AngleStepDef = 15.0f;
    }
    ~robot() {}
    void ModelInitPos();
    void shoulder_rot();
    void bicep_below_rot();
    void bicep_above_rot();
    void wrist_rot();
    void rail_rot();
    void wrist_mov();
    void update_position();
    float getAngleStepDef() {
        return AngleStepDef;
    }
    void setAngleStepDef(float a) {
        AngleStepDef = a;
    }
};

#endif  // ROBOT_ARM_HPP