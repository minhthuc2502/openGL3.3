#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "shader.hpp"
#include "stb_image.h"
/**
 * Call back function when resize window
*/
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    float vertices[] = {    
            //Positions           //colors              // texture coords      
        0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 0.0f,    0.55f,  0.55f,         // top right
        0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,    0.55f,  0.45f,         // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,    0.45f,  0.45f,         // bottom left
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,    0.45f,  0.55f          // top left 
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
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // using open gl core proifle to opengl more effective and flexible but more difficult => need to use it
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(800,600,"Bras3DGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GFLW Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    /**
     * call glad to manage all function of OpenGL that we want to use before call function openGL
     * glfw provide glfwGetProcAddress to define correct function base on OS compile for
     * glad load adress of the OpenGL function pointers. 
     */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize glad" << std::endl;
        return -1;
    }
    /**
     * tell openGL size to render on window
    */
    glViewport(0, 0, 800, 600);

    // declare a callback function to handle of view when user resize the window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(2);

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
    while (!glfwWindowShouldClose(window))
    {
        // check if user press esc key (INPUT)
        processInput(window);

        // Rendering command
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // draw object (triangle)
        pShader.use();
        
        // bind Texture
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture2);
        /*
        float timevalue = glfwGetTime();
        float greenValue = sin(timevalue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "varyColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        */
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        // swap color buffer to render image on window
        glfwSwapBuffers(window);
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