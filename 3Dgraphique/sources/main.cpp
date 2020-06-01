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
camera ucamera;
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float lastX = 400, lastY = 300;
unsigned int angle = 0;

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
  char path[] = "../3Dgraphique/images/arm-seperated/pincher_gl/pincher_gl/pincher_gl/base_bm.obj";
  Model Base(path);
  Model Shoulder((char*)"../3Dgraphique/images/arm-seperated/pincher_gl/pincher_gl/pincher_gl/shoulder_b.obj");
  Model Elbow((char*)"../3Dgraphique/images/arm-seperated/pincher_gl/pincher_gl/pincher_gl/bicep_b.obj");
  Model ElbowUp((char*)"../3Dgraphique/images/arm-seperated/pincher_gl/pincher_gl/pincher_gl/bicep001_b.obj");
  Model Wrist((char*)"../3Dgraphique/images/arm-seperated/pincher_gl/pincher_gl/pincher_gl/wrist_b.obj");
  Model GRail((char*)"../3Dgraphique/images/arm-seperated/pincher_gl/pincher_gl/pincher_gl/gRail_b.obj");
  Model GripperL((char*)"../3Dgraphique/images/arm-seperated/pincher_gl/pincher_gl/pincher_gl/gripper_b.obj");
  Model GripperR((char*)"../3Dgraphique/images/arm-seperated/pincher_gl/pincher_gl/pincher_gl/gripper001_b.obj");
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

    glm::mat4 model = glm::mat4(0.1f);
    
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
    model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0, 0.0, 1.0));
    model = glm::translate(model, glm::vec3(-60.0f, 30.0f, -30.0f));
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    pShader.set4MatrixFloat("model", model);

    // draw object
    Base.draw(pShader);
    Shoulder.draw(pShader);
    Elbow.draw(pShader);
    ElbowUp.draw(pShader);
    Wrist.draw(pShader);
    GRail.draw(pShader);
    GripperL.draw(pShader);
    GripperR.draw(pShader);
    // swap color buffer to render image on window
    glfwSwapBuffers(uwindow.mpwindow);
    // catch event
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}