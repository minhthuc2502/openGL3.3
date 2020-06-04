#include "robotarm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
void robot::ModelInitPos() {
    model.resize(8);
    std::cout << "get size " << model.size() << std::endl;
    std::cout << "model init" << std::endl;
    //std::vector<glm::mat4>::size_type sz = model.size();
    //std::cout << "get size " << sz << std::endl;
    for (unsigned int i = 0; i < 8; i++)
    {
        std::cout << "count " << i << std::endl;
        model[i] = glm::mat4(0.1f);
        std::cout << "init mat" << std::endl;
        model[i] = glm::scale(model[i], glm::vec3(0.2f, 0.2f, 0.2f));
        std::cout << "scale mat" << std::endl;
    }
    std::cout << "loop for all model" << std::endl;
    // Set position initiale
    model[SHOULDER] = glm::translate(model[SHOULDER], positionShoulder);
    model[BICEP_BELOW] = glm::translate(model[BICEP_BELOW], positionBicepBelow);
    model[BICEP_ABOVE] = glm::translate(model[BICEP_ABOVE], positionBicepAbove);
    model[WRIST] = glm::translate(model[WRIST], positionWrist);
    model[RAIL] = glm::translate(model[RAIL], positionRail);
    model[GRIPPERL] = glm::translate(model[GRIPPERL], positionGripperR);
    model[GRIPPERR] = glm::translate(model[GRIPPERR], positionGripperL);
    std::cout << "finish" << std::endl;
}

void robot::shoulder_rot()
{
  // pivot point for the joint of shoulder
  glm::vec3 ppivot = glm::vec3(99.0, 113.76, -131.75);
  std::vector<glm::mat4>::size_type sz = model.size();
  // Move other parts of arm to point pivot
  model[BICEP_BELOW] = glm::translate(model[BICEP_BELOW], ppivot - positionBicepBelow);
  model[BICEP_ABOVE] = glm::translate(model[BICEP_ABOVE], ppivot - positionBicepAbove);
  model[WRIST] = glm::translate(model[WRIST], ppivot - positionWrist);
  model[RAIL] = glm::translate(model[RAIL], ppivot - positionRail);
  model[GRIPPERL] = glm::translate(model[GRIPPERL], ppivot - positionGripperR);
  model[GRIPPERR] = glm::translate(model[GRIPPERR], ppivot - positionGripperL);
  // Rotate a angle a
  for (unsigned int i = 1; i < sz; i++)
  {
    model[i] = glm::rotate(model[i], glm::radians(angle[ANGLE_SHOULDER]), glm::vec3(0.0, 1.0, 0.0));
  }
  // Move other parts to the position initial
  model[BICEP_BELOW] = glm::translate(model[BICEP_BELOW], positionBicepBelow - ppivot);
  model[BICEP_ABOVE] = glm::translate(model[BICEP_ABOVE], positionBicepAbove - ppivot);
  model[WRIST] = glm::translate(model[WRIST], positionWrist - ppivot);
  model[RAIL] = glm::translate(model[RAIL], positionRail - ppivot);
  model[GRIPPERL] = glm::translate(model[GRIPPERL], positionGripperR - ppivot);
  model[GRIPPERR] = glm::translate(model[GRIPPERR], positionGripperL - ppivot);
}

void robot::bicep_below_rot()
{
  // pivot point for the joint of bicep below
  glm::vec3 ppivot = glm::vec3(78.404, 128.91, -135.86);
  std::vector<glm::mat4>::size_type sz = model.size();
  // Move other parts of arm to point pivot
  model[BICEP_BELOW] = glm::translate(model[BICEP_BELOW], ppivot - positionBicepBelow);
  model[BICEP_ABOVE] = glm::translate(model[BICEP_ABOVE], ppivot - positionBicepAbove);
  model[WRIST] = glm::translate(model[WRIST], ppivot - positionWrist);
  model[RAIL] = glm::translate(model[RAIL], ppivot - positionRail);
  model[GRIPPERL] = glm::translate(model[GRIPPERL], ppivot - positionGripperR);
  model[GRIPPERR] = glm::translate(model[GRIPPERR], ppivot - positionGripperL);
  for (unsigned int i = 2; i < sz; i++) {
    model[i] = glm::rotate(model[i], glm::radians(angle[ANGLE_BICEP_BELOW]), glm::vec3(0.98052, 0.0, 0.1964));
  }
  // Move other parts to the position initial
  model[BICEP_BELOW] = glm::translate(model[BICEP_BELOW], positionBicepBelow - ppivot);
  model[BICEP_ABOVE] = glm::translate(model[BICEP_ABOVE], positionBicepAbove - ppivot);
  model[WRIST] = glm::translate(model[WRIST], positionWrist - ppivot);
  model[RAIL] = glm::translate(model[RAIL], positionRail - ppivot);
  model[GRIPPERL] = glm::translate(model[GRIPPERL], positionGripperR - ppivot);
  model[GRIPPERR] = glm::translate(model[GRIPPERR], positionGripperL - ppivot);
}

void robot::bicep_above_rot()
{
  // pivot point for the joint of bicep below
  glm::vec3 ppivot = glm::vec3(0.0, 230.96, -166.38);
  std::vector<glm::mat4>::size_type sz = model.size();
  model[BICEP_ABOVE] = glm::translate(model[BICEP_ABOVE], ppivot - positionBicepAbove);
  model[WRIST] = glm::translate(model[WRIST], ppivot - positionWrist);
  model[RAIL] = glm::translate(model[RAIL], ppivot - positionRail);
  model[GRIPPERL] = glm::translate(model[GRIPPERL], ppivot - positionGripperR);
  model[GRIPPERR] = glm::translate(model[GRIPPERR], ppivot - positionGripperL);
  for (unsigned int i = 3; i < sz; i++) {
      model[i] = glm::rotate(model[i], glm::radians(angle[ANGLE_BICEP_ABOVE]), glm::vec3(0.98052, 0.0, 0.1964));
  }
  model[BICEP_ABOVE] = glm::translate(model[BICEP_ABOVE], positionBicepAbove - ppivot);
  model[WRIST] = glm::translate(model[WRIST], positionWrist - ppivot);
  model[RAIL] = glm::translate(model[RAIL], positionRail - ppivot);
  model[GRIPPERL] = glm::translate(model[GRIPPERL], positionGripperR - ppivot);
  model[GRIPPERR] = glm::translate(model[GRIPPERR], positionGripperL - ppivot);
}

void robot::wrist_rot()
{
  // pivot point for the joint of bicep below
  glm::vec3 ppivot = glm::vec3(0.0, 180.34, -74.287);
  std::vector<glm::mat4>::size_type sz = model.size();
  model[WRIST] = glm::translate(model[WRIST], ppivot - positionWrist);
  model[RAIL] = glm::translate(model[RAIL], ppivot - positionRail);
  model[GRIPPERL] = glm::translate(model[GRIPPERL], ppivot - positionGripperR);
  model[GRIPPERR] = glm::translate(model[GRIPPERR], ppivot - positionGripperL);
  for (unsigned int i = 4; i < sz; i++) {
      model[i] = glm::rotate(model[i], glm::radians(angle[ANGLE_GRIPPER]), glm::vec3(0.98052, 0.0, 0.1964));
  }
  model[WRIST] = glm::translate(model[WRIST], positionWrist - ppivot);
  model[RAIL] = glm::translate(model[RAIL], positionRail - ppivot);
  model[GRIPPERL] = glm::translate(model[GRIPPERL], positionGripperR - ppivot);
  model[GRIPPERR] = glm::translate(model[GRIPPERR], positionGripperL - ppivot);
}

void robot::rail_rot()
{
  // pivot point for the joint of bicep below
  glm::vec3 ppivot = glm::vec3(72.914, 180.34, 1.5256);
  std::vector<glm::mat4>::size_type sz = model.size();
  model[RAIL] = glm::translate(model[RAIL], ppivot - positionRail);
  model[GRIPPERL] = glm::translate(model[GRIPPERL], ppivot - positionGripperR);
  model[GRIPPERR] = glm::translate(model[GRIPPERR], ppivot - positionGripperL);
  for (unsigned int i = 5; i < sz; i++) {
      model[i] = glm::rotate(model[i], glm::radians(angle[ANGLE_RAIL]), glm::vec3(-0.1964, 0.0, 0.98052));
  }
  model[RAIL] = glm::translate(model[RAIL], positionRail - ppivot);
  model[GRIPPERL] = glm::translate(model[GRIPPERL], positionGripperR - ppivot);
  model[GRIPPERR] = glm::translate(model[GRIPPERR], positionGripperL - ppivot);
}

void robot::wrist_mov()
{
  float cld =  14.0;
  if (angle[ANGLE_WRIST] == -1) {
    model[GRIPPERL] = glm::translate(model[6], glm::vec3(cld, 0.0, cld * 0.1964));
    model[GRIPPERR] = glm::translate(model[7], glm::vec3(-cld, 0.0, -cld * 0.1964));
  }
}

void robot::update_position()
{
  ModelInitPos();
  shoulder_rot();
  bicep_below_rot();
  bicep_above_rot();
  wrist_rot();
  rail_rot();
  wrist_mov();
}


