#include "camera.hpp"
#include "model.hpp"
#include "shader.hpp"
#include "stb_image.h"
#include "window.hpp"
#include "robotarm.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
camera ucamera;
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float lastX = 400, lastY = 300;
robot rbArm;
bool pressed[10] = {false};
/**
 * Call back function when resize window
 */
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

/**
 * Call back function when move mouse
 */
void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
  float xOffset = xpos - lastX;
  float yOffset = ypos - lastY;
  lastX = xpos;
  lastY = ypos;
  ucamera.processMouseMovement(xOffset, yOffset);
}

/**
 * Handle event on button which control robot arm
*/
void handleEventButton(enum AngleRotation idx, unsigned int direction, bool &press)
{
  if (direction == 1) {
    rbArm.angle[idx] += rbArm.getAngleStepDef();
  } else if (direction == 0) {
    rbArm.angle[idx] -= rbArm.getAngleStepDef();
  }
  rbArm.update_position();
  press = true;
}
/**
 * Call back for zoom
 */
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  ucamera.processMouseScoll((float)yoffset);
}
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    ucamera.processKeyBoard(FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    ucamera.processKeyBoard(BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    ucamera.processKeyBoard(LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    ucamera.processKeyBoard(RIGHT, deltaTime);
  // Rotate left shoulder joint with button left
  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && !pressed[0]) {
    handleEventButton(ANGLE_SHOULDER, 1, pressed[0]);
  } else if (glfwGetKey(window, GLFW_KEY_LEFT) != GLFW_PRESS)
  {
    pressed[0] = false;
  }
  // Rotate right shoulder joint with button right
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && !pressed[1])
  {
    handleEventButton(ANGLE_SHOULDER, 0, pressed[1]);
  } else if (glfwGetKey(window, GLFW_KEY_RIGHT) != GLFW_PRESS)
  {
    pressed[1] = false;
  }
  // Rotate up Bicep below joint with button up
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && !pressed[2])      // 0 direction to up
  {
    handleEventButton(ANGLE_BICEP_BELOW, 0, pressed[2]);
  } else if (glfwGetKey(window, GLFW_KEY_UP) != GLFW_PRESS)
  {
    pressed[2] = false;
  }
  // Rotate down Bicep below joint with button down
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && !pressed[3])    // 1 direction to down
  {
    handleEventButton(ANGLE_BICEP_BELOW, 1, pressed[3]);
  } else if (glfwGetKey(window, GLFW_KEY_DOWN) != GLFW_PRESS)
  {
    pressed[3] = false;
  }
  // Rotate up Bicep above joint with button KP 8
  if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS && !pressed[4])    // 1 direction to down
  {
    handleEventButton(ANGLE_BICEP_ABOVE, 0, pressed[4]);
  } else if (glfwGetKey(window, GLFW_KEY_KP_8) != GLFW_PRESS)
  {
    pressed[4] = false;
  }
  // Rotate down Bicep above joint with button KP 2
  if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS && !pressed[5])    // 1 direction to down
  {
    handleEventButton(ANGLE_BICEP_ABOVE, 1, pressed[5]);
  } else if (glfwGetKey(window, GLFW_KEY_KP_2) != GLFW_PRESS)
  {
    pressed[5] = false;
  }
  // Rotate up wrist with button KP 4
  if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS && !pressed[6])    // 1 direction to down
  {
    handleEventButton(ANGLE_WRIST, 0, pressed[6]);
  } else if (glfwGetKey(window, GLFW_KEY_KP_4) != GLFW_PRESS)
  {
    pressed[6] = false;
  }
  // Rotate down wrist with button KP 6
  if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS && !pressed[7])    // 1 direction to down
  {
    handleEventButton(ANGLE_WRIST, 1, pressed[7]);
  } else if (glfwGetKey(window, GLFW_KEY_KP_6) != GLFW_PRESS)
  {
    pressed[7] = false;
  }
  // Rotate left rail with button KP 1
  if (glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_PRESS && !pressed[8])    // 1 direction to down
  {
    handleEventButton(ANGLE_RAIL, 0, pressed[8]);
  } else if (glfwGetKey(window, GLFW_KEY_KP_1) != GLFW_PRESS)
  {
    pressed[8] = false;
  }
  // Rotate right rail with button KP 3
  if (glfwGetKey(window, GLFW_KEY_KP_3) == GLFW_PRESS && !pressed[9])    // 1 direction to down
  {
    handleEventButton(ANGLE_RAIL, 1, pressed[9]);
  } else if (glfwGetKey(window, GLFW_KEY_KP_3) != GLFW_PRESS)
  {
    pressed[9] = false;
  }
  if (glfwGetKey(window, GLFW_KEY_KP_7) == GLFW_PRESS)    // 1 direction to down
  {
    rbArm.angle[ANGLE_GRIPPER] = 0;
    rbArm.update_position();
  }
  if (glfwGetKey(window, GLFW_KEY_KP_9) == GLFW_PRESS)    // 1 direction to down
  {
    rbArm.angle[ANGLE_GRIPPER] = -1;
    rbArm.update_position();
  }
}

int main() {
  // Initialize window
  window uwindow((char *)"bras3D");
  try {
    uwindow.initialize();
  } catch (std::runtime_error error) {
    std::cerr << "Exception: " << error.what() << std::endl;
  }
  // Build and compile shader program
  Shader pShader("../3Dgraphique/shaders/3.3.shader.vs",
                 "../3Dgraphique/shaders/3.3.shader.fs");

  // when load with stbi, flip inversly with axis y
  stbi_set_flip_vertically_on_load(true);
  // enable depth, opengl know which points need override the other pointes
  glEnable(GL_DEPTH_TEST);

  glfwSetCursorPosCallback(uwindow.mpwindow, mouse_callback);
  glfwSetScrollCallback(uwindow.mpwindow, scroll_callback);

  // Load models
  Model Base((char*)"../3Dgraphique/images/arm-test/base_bm.obj");
  Model Shoulder((char*)"../3Dgraphique/images/arm-test/shoulder_b.obj");
  Model Elbow((char*)"../3Dgraphique/images/arm-test/bicep_b.obj");
  Model ElbowUp((char*)"../3Dgraphique/images/arm-test/bicep001_b.obj");
  Model Wrist((char*)"../3Dgraphique/images/arm-test/wrist_b.obj");
  Model GRail((char*)"../3Dgraphique/images/arm-test/gRail_b.obj");
  Model GripperL((char*)"../3Dgraphique/images/arm-test/gripper_b.obj");
  Model GripperR((char*)"../3Dgraphique/images/arm-test/gripper001_b.obj");
  rbArm.ModelInitPos();
  while (!glfwWindowShouldClose(uwindow.mpwindow)) {
    // check if user press esc key (INPUT)
    processInput(uwindow.mpwindow);
    // Rendering command
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use shader
    pShader.use();

    // Set Transformations
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    pShader.setVec3("light.position", glm::vec3(70.0f, 50.0f, 30.0f));
    pShader.setVec3("light.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
    pShader.setVec3("light.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    glm::mat4 view;
    view = ucamera.getViewSpace();
    pShader.set4MatrixFloat("view", view);

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(ucamera.getFov()),
                                  800.0f / 600.0f, 0.1f, 100.0f);
    pShader.set4MatrixFloat("projection", projection);
    // Set model matrix and draw object
    pShader.set4MatrixFloat("model", rbArm.model[BASE]);
    Base.draw(pShader);
    pShader.set4MatrixFloat("model", rbArm.model[SHOULDER]);
    Shoulder.draw(pShader);
    pShader.set4MatrixFloat("model", rbArm.model[BICEP_BELOW]);
    Elbow.draw(pShader);
    pShader.set4MatrixFloat("model", rbArm.model[BICEP_ABOVE]);
    ElbowUp.draw(pShader);
    pShader.set4MatrixFloat("model", rbArm.model[WRIST]);
    Wrist.draw(pShader);
    pShader.set4MatrixFloat("model", rbArm.model[RAIL]);
    GRail.draw(pShader);
    pShader.set4MatrixFloat("model", rbArm.model[GRIPPERL]);
    GripperL.draw(pShader);
    pShader.set4MatrixFloat("model", rbArm.model[GRIPPERR]);
    GripperR.draw(pShader);
    // swap color buffer to render image on window
    glfwSwapBuffers(uwindow.mpwindow);
    // catch event
    glfwPollEvents();
  }
  // terminate window
  glfwTerminate();
  return 0;
}