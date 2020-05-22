#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>
#include "shader.hpp"
#include "stb_image.h"
#include "camera.hpp"
#include "window.hpp"
#include "model.hpp"
camera ucamera;
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float lastX = 400, lastY = 300;

/**
 * Call back function when resize window
*/
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/**
 * Call back function when move mouse
*/
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    float xOffset = xpos - lastX;
    float yOffset = ypos - lastY;
    lastX = xpos;
    lastY = ypos;
    ucamera.processMouseMovement(xOffset, yOffset);
}

/**
 * Call back for zoom
*/
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    ucamera.processMouseScoll((float)yoffset);
}
void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        ucamera.processKeyBoard(FORWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        ucamera.processKeyBoard(BACKWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        ucamera.processKeyBoard(LEFT, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        ucamera.processKeyBoard(RIGHT, deltaTime);
}

int main()
{
    // Initialize window
    window uwindow((char*)"bras3D");
    try{
        uwindow.initialize();
    }
    catch (std::runtime_error error)
    {
        std::cerr << "Exception: " << error.what() << std::endl;
    }
    // Build and compile shader program
    Shader pShader("../3Dgraphique/shaders/3.3.shader.vs", "../3Dgraphique/shaders/3.3.shader.fs");

    // when load with stbi, flip inversly with axis y
    stbi_set_flip_vertically_on_load(true);
    // enable depth, opengl know which points need override the other pointes
    glEnable(GL_DEPTH_TEST);
    
    glfwSetCursorPosCallback(uwindow.mpwindow, mouse_callback);
    glfwSetScrollCallback(uwindow.mpwindow, scroll_callback);

    // Load models
    char path[] = "../3Dgraphique/images/backpack/backpack.obj";
    Model guitarModel(path);

    while (!glfwWindowShouldClose(uwindow.mpwindow))
    {
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

        glm::mat4 view;
        view = ucamera.getViewSpace();
        pShader.set4MatrixFloat("view", view);

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(ucamera.getFov()), 800.0f/600.0f, 0.1f, 100.0f);
        pShader.set4MatrixFloat("projection", projection);

        glm::mat4 model = glm::mat4(0.1f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        pShader.set4MatrixFloat("model", model);

        // draw object
        guitarModel.draw(pShader);
        // swap color buffer to render image on window
        glfwSwapBuffers(uwindow.mpwindow);
        // catch event
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}