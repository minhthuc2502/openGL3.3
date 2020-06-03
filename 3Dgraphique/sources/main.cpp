#include "camera.hpp"
#include "model.hpp"
#include "shader.hpp"
#include "stb_image.h"
#include "window.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>
camera ucamera;
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float lastX = 400, lastY = 300;
float angle[6] = {0};
std::vector<glm::mat4> model (8);

void ModelInitPos(std::vector<glm::mat4> &m)
{
  std::vector<glm::mat4>::size_type sz = m.size();
  for (unsigned int i = 0; i < sz; i++)
  {
    m[i] = glm::mat4(0.1f);
    //m[i] = glm::rotate(m[i], glm::radians(-45.0f), glm::vec3(0.0, 0.0, 1.0));
    //m[i] = glm::translate(m[i], glm::vec3(-60.0f, 30.0f, -30.0f));
    m[i] = glm::scale(m[i], glm::vec3(0.2f, 0.2f, 0.2f));
  }
  m[1] = glm::translate(m[1], glm::vec3(99.0, 113.76, -131.75));
  m[2] = glm::translate(m[2], glm::vec3(102.46, 186.94, -149.04));
  m[3] = glm::translate(m[3], glm::vec3(94.628, 202.13, -109.93));
  m[4] = glm::translate(m[4], glm::vec3(80.021, 187.32, -37.007));
  m[5] = glm::translate(m[5], glm::vec3(73.346, 180.38, -3.684));
  m[6] = glm::translate(m[6], glm::vec3(44.635, 180.34, 6.1495));
  m[7] = glm::translate(m[7], glm::vec3(96.054, 180.33, 16.45));
}

void shoulder_rot(std::vector<glm::mat4> &m, float a = 0)
{
  std::vector<glm::mat4>::size_type sz = m.size();
  m[2] = glm::translate(m[2], glm::vec3(-3.46, -73.18, 17.29));
  m[3] = glm::translate(m[3], glm::vec3(4.372, -88.37, -21.82));
  m[4] = glm::translate(m[4], glm::vec3(18.979, -73.56, -94.743));
  m[5] = glm::translate(m[5], glm::vec3(25.654, -66.62, -128.066));
  m[6] = glm::translate(m[6], glm::vec3(54.365, -66.58, -137.8995));
  m[7] = glm::translate(m[7], glm::vec3(2.946, -66.57, -148.2));
  for (unsigned int i = 1; i < sz; i++)
  {
    m[i] = glm::rotate(m[i], glm::radians(a), glm::vec3(0.0, 1.0, 0.0));
  }
  m[2] = glm::translate(m[2], glm::vec3(3.46, 73.18, -17.29));
  m[3] = glm::translate(m[3], glm::vec3(-4.372, 88.37, 21.82));
  m[4] = glm::translate(m[4], glm::vec3(-18.979, 73.56, 94.743));
  m[5] = glm::translate(m[5], glm::vec3(-25.654, 66.62, 128.066));
  m[6] = glm::translate(m[6], glm::vec3(-54.365, 66.58, 137.8995));
  m[7] = glm::translate(m[7], glm::vec3(-2.946, 66.57, 148.2));
}

void bicep_below_rot(std::vector<glm::mat4> &m, float a = 0)
{
  std::vector<glm::mat4>::size_type sz = m.size();
  m[2] = glm::translate(m[2], glm::vec3(-24.056, -58.03, 13.18));
  m[3] = glm::translate(m[3], glm::vec3(4.372, -73.22, -25.93));
  m[4] = glm::translate(m[4], glm::vec3(18.979, -58.41, -98.853));
  m[5] = glm::translate(m[5], glm::vec3(25.654, -51.47, -132.176));
  m[6] = glm::translate(m[6], glm::vec3(54.365, -51.43, -142.0095));
  m[7] = glm::translate(m[7], glm::vec3(2.946, -51.42, -152.31));
  for (unsigned int i = 2; i < sz; i++) {
    m[i] = glm::rotate(m[i], glm::radians(a), glm::vec3(0.98052, 0.0, 0.1964));
  }
  m[2] = glm::translate(m[2], glm::vec3(24.056, 58.03, -13.18));
  m[3] = glm::translate(m[3], glm::vec3(-4.372, 73.22, 25.93));
  m[4] = glm::translate(m[4], glm::vec3(-18.979, 58.41, 98.853));
  m[5] = glm::translate(m[5], glm::vec3(-25.654, 51.47, 132.176));
  m[6] = glm::translate(m[6], glm::vec3(-54.365, 51.43, 142.0095));
  m[7] = glm::translate(m[7], glm::vec3(-2.946, 51.42, 152.31));
}

void bicep_above_rot(std::vector<glm::mat4> &m, float a = 0)
{
  std::vector<glm::mat4>::size_type sz = m.size();
  m[3] = glm::translate(m[3], glm::vec3(0.0, 28.83, -56.45));
  m[4] = glm::translate(m[4], glm::vec3(0.0, 43.64, -129.373));
  m[5] = glm::translate(m[5], glm::vec3(0.0, 50.58, -162.696));
  m[6] = glm::translate(m[6], glm::vec3(0.0, 50.62, -172.5295));
  m[7] = glm::translate(m[7], glm::vec3(0.0, 50.63, -182.83));
  for (unsigned int i = 3; i < sz; i++) {
      m[i] = glm::rotate(m[i], glm::radians(a), glm::vec3(0.98052, 0.0, 0.1964));
  }
  m[3] = glm::translate(m[3], glm::vec3(0.0, -28.83, 56.45));
  m[4] = glm::translate(m[4], glm::vec3(0.0, -43.64, 129.373));
  m[5] = glm::translate(m[5], glm::vec3(0.0, -50.58, 162.696));
  m[6] = glm::translate(m[6], glm::vec3(0.0, -50.62, 172.5295));
  m[7] = glm::translate(m[7], glm::vec3(0.0, -50.63, 182.83));
}

void wrist_rot(std::vector<glm::mat4> &m, float a = 0)
{
  std::vector<glm::mat4>::size_type sz = m.size();
  m[4] = glm::translate(m[4], glm::vec3(0.0, -6.98, -37.28));
  m[5] = glm::translate(m[5], glm::vec3(0.0, -0.04, -70.603));
  m[6] = glm::translate(m[6], glm::vec3(0.0, 0.0, -80.4365));
  m[7] = glm::translate(m[7], glm::vec3(0.0, 0.01, -90.737));
  for (unsigned int i = 4; i < sz; i++) {
      m[i] = glm::rotate(m[i], glm::radians(a), glm::vec3(0.98052, 0.0, 0.1964));
  }
  m[4] = glm::translate(m[4], glm::vec3(0.0, 6.98, 37.28));
  m[5] = glm::translate(m[5], glm::vec3(0.0, 0.04, 70.603));
  m[6] = glm::translate(m[6], glm::vec3(0.0, 0.0, 80.4365));
  m[7] = glm::translate(m[7], glm::vec3(0.0, -0.01, 90.737));
}

void rail_rot(std::vector<glm::mat4> &m, float a = 0)
{
  std::vector<glm::mat4>::size_type sz = m.size();
  m[5] = glm::translate(m[5], glm::vec3(-0.432, -0.04, 2.1584));
  m[6] = glm::translate(m[6], glm::vec3(28.279, 0.0, -7.6751));
  m[7] = glm::translate(m[7], glm::vec3(-23.14, 0.01, -17.9756));
  for (unsigned int i = 5; i < sz; i++) {
      m[i] = glm::rotate(m[i], glm::radians(a), glm::vec3(-0.1964, 0.0, 0.98052));
  }
  m[5] = glm::translate(m[5], glm::vec3(0.432, 0.04, -2.1584));
  m[6] = glm::translate(m[6], glm::vec3(-28.279, 0.0, 7.6751));
  m[7] = glm::translate(m[7], glm::vec3(23.14, -0.01, 17.9756));
}

void wrist_mov(std::vector<glm::mat4> &m, float a = 0)
{
  if (a == -1) {
    m[6] = glm::translate(m[6], glm::vec3(14, 0.0, 0.0));
    m[7] = glm::translate(m[7], glm::vec3(-14, 0.0, 0.0));
  }
}

void update_position(std::vector<glm::mat4> &m)
{
  ModelInitPos(m);
  shoulder_rot(m, angle[0]);
  bicep_below_rot(m, angle[1]);
  bicep_above_rot(m, angle[2]);
  wrist_rot(m, angle[3]);
  rail_rot(m, angle[4]);
  wrist_mov(m, angle[5]);
}

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
  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
    angle[0] += 2.0f;
    update_position(model);
  }
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
  {
    angle[0] -= 2.0f;
    update_position(model);
  }
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)      // 0 direction to up
  {
    angle[1] -= 2.0f;
    update_position(model);
  }
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)    // 1 direction to down
  {
    angle[1] += 2.0f;
    update_position(model);
  }
  if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS)    // 1 direction to down
  {
    angle[2] -= 2.0f;
    update_position(model);
  }
  if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS)    // 1 direction to down
  {
    angle[2] += 2.0f;
    update_position(model);
  }
  if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)    // 1 direction to down
  {
    angle[3] -= 2.0f;
    update_position(model);
  }
  if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)    // 1 direction to down
  {
    angle[3] += 2.0f;
    update_position(model);
  }
  if (glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_PRESS)    // 1 direction to down
  {
    angle[4] -= 2.0f;
    update_position(model);
  }
  if (glfwGetKey(window, GLFW_KEY_KP_3) == GLFW_PRESS)    // 1 direction to down
  {
    angle[4] += 2.0f;
    update_position(model);
  }
  if (glfwGetKey(window, GLFW_KEY_KP_7) == GLFW_PRESS)    // 1 direction to down
  {
    angle[5] = 0;
    update_position(model);
  }
  if (glfwGetKey(window, GLFW_KEY_KP_9) == GLFW_PRESS)    // 1 direction to down
  {
    angle[5] = -1;
    update_position(model);
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
  char path[] = "../3Dgraphique/images/arm-test/base_bm.obj";
  Model Base(path);
  Model Shoulder((char*)"../3Dgraphique/images/arm-test/shoulder_b.obj");
  Model Elbow((char*)"../3Dgraphique/images/arm-test/bicep_b.obj");
  Model ElbowUp((char*)"../3Dgraphique/images/arm-test/bicep001_b.obj");
  Model Wrist((char*)"../3Dgraphique/images/arm-test/wrist_b.obj");
  Model GRail((char*)"../3Dgraphique/images/arm-test/gRail_b.obj");
  Model GripperL((char*)"../3Dgraphique/images/arm-test/gripper_b.obj");
  Model GripperR((char*)"../3Dgraphique/images/arm-test/gripper001_b.obj");
  ModelInitPos(model);
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

    pShader.setVec3("light.position", glm::vec3(-70.0f, 50.0f, -30.0f));
    pShader.setVec3("light.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
    pShader.setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
    pShader.setVec3("light.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    glm::mat4 view;
    view = ucamera.getViewSpace();
    pShader.set4MatrixFloat("view", view);

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(ucamera.getFov()),
                                  800.0f / 600.0f, 0.1f, 100.0f);
    pShader.set4MatrixFloat("projection", projection);
    // draw object
    pShader.set4MatrixFloat("model", model[0]);
    Base.draw(pShader);
    pShader.set4MatrixFloat("model", model[1]);
    Shoulder.draw(pShader);
    pShader.set4MatrixFloat("model", model[2]);
    Elbow.draw(pShader);
    pShader.set4MatrixFloat("model", model[3]);
    ElbowUp.draw(pShader);
    pShader.set4MatrixFloat("model", model[4]);
    Wrist.draw(pShader);
    pShader.set4MatrixFloat("model", model[5]);
    GRail.draw(pShader);
    pShader.set4MatrixFloat("model", model[6]);
    GripperL.draw(pShader);
    pShader.set4MatrixFloat("model", model[7]);
    GripperR.draw(pShader);
    // swap color buffer to render image on window
    glfwSwapBuffers(uwindow.mpwindow);
    // catch event
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}