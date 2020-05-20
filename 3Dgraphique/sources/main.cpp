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
    /*float vertices[] = {    
            //Positions           //colors              // texture coords      
        0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 0.0f,    1.f,  1.0f,         // top right
        0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,    1.0f,  0.0f,         // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,    0.0f,  0.0f,         // bottom left
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,    0.0f,  1.0f          // top left 
    };*/
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    }; 
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    unsigned int texture1;
    unsigned int texture2;
    int width, height, nrChennels;
    window uwindow((char*)"bras3D");
    try{
        uwindow.initialize();
    }
    catch (std::runtime_error error)
    {
        std::cerr << "Exception: " << error.what() << std::endl;
    }
    catch(std::bad_alloc& error)
    {
        std::cerr << "Exception: " << error.what() << std::endl;
    }
    // Build and compile shader program
    Shader pShader("../3Dgraphique/shaders/3.3.shader.vs", "../3Dgraphique/shaders/3.3.shader.fs");

    std::cout << "Generate VBO" << std::endl;
    // Generate Vetex buffer to save data vertice on GPU
    glGenBuffers(1, &VBO);
    // Bind buffer to type GL_ARRAY_BUFFER: used for vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // save data vertices to GPU
    // GL_STATIC_DRAW: data set only one time, using for many times
    // GL_DYNAMIC_DRAW : data can change many times
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    /**
     * All step above need to redo whenever we want to draw a triangle
     * So we need to save all state of that to an object and whenever we want to draw a shape, just bind this object
     * So vertex array object (VAO) is the object which bound VBO and subsuquent vertex attibute alls
    */
    std::cout << "Generate VAO" << std::endl;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    /**
     * Element buffer object handle the problem when duplicate the vertices when draw image
     * Element can keep index of vertice so we avoid the phenomene of duplication
    */
    std::cout << "Generate EBO" << std::endl;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

    std::cout << "Configure vertex arttribute" << std::endl;
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
    //glEnableVertexAttribArray(2);

    // Generate Textures
    glGenTextures(1, &texture1);
    glGenTextures(1, &texture2);
    // set the Textture wrapping/filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load image generate texture
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    unsigned char *data = stbi_load("../3Dgraphique/images/container.jpg", &width, &height, &nrChennels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    stbi_set_flip_vertically_on_load(true);  
    data = stbi_load("../3Dgraphique/images/awesomeface.png", &width, &height, &nrChennels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);  // .png using GL_RGBA (A for transparency)
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); 

    // Indicate texture unit (location of texture) for the uniform in fragment shader. Example it says that the location of uniform Texture1 have location 1 is correspondant GL_TEXTURE1 ~ texture1
    pShader.use();
    pShader.setInt("Texture1", 1);
    pShader.setInt("Texture2", 2);
    glEnable(GL_DEPTH_TEST);
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    glfwSetCursorPosCallback(uwindow.mpwindow, mouse_callback);

    glfwSetScrollCallback(uwindow.mpwindow, scroll_callback);
    while (!glfwWindowShouldClose(uwindow.mpwindow))
    {
        // check if user press esc key (INPUT)
        processInput(uwindow.mpwindow);

        // Rendering command
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // draw object (triangle)
        pShader.use();
        
        // bind Texture
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture2);
        unsigned int transformLoc;

        /*
        float timevalue = glfwGetTime();
        float greenValue = sin(timevalue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "varyColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        */
        glBindVertexArray(VAO);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glm::mat4 view;
        view = ucamera.getViewSpace();
        transformLoc = glGetUniformLocation(pShader.getId(), "view");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(ucamera.getFov()), 800.0f/600.0f, 0.1f, 100.0f);
        transformLoc = glGetUniformLocation(pShader.getId(), "projection");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(projection));

        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            transformLoc = glGetUniformLocation(pShader.getId(), "model");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);
        // swap color buffer to render image on window
        glfwSwapBuffers(uwindow.mpwindow);
        // catch event
        glfwPollEvents();
    }
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}