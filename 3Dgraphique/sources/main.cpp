#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
    int success;
    char infolog[512];
    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    }; 

    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    
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
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

    std::cout << "Create Vertex Shader" << std::endl;
    // create a vertex shader
    // vertex shader used to transfert 3d coordiante to the coordinate in region visible
    // it also assemble the coordinate to the shape which we want
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // shader is wrote in another language. So we need to attach the vertexshader to the code in GLSL and compile it
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // Check if compile successfully
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infolog << std::endl;
    }
    std::cout << "Create Fragment Shader" << std::endl;
    // fragment shader is all about calculating the color output of pixels
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // Check if compile successfully
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
    }
    std::cout << "Create program Shader" << std::endl;
    // shader program to link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderProgram, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infolog << std::endl;
    }
    std::cout << "Configure vertex arttribute" << std::endl;
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); 
    std::cout << "Active program Shader" << std::endl;
    // active shader program
    glUseProgram(shaderProgram);
    // Delete shader after linking, not useful anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    while (!glfwWindowShouldClose(window))
    {
        // check if user press esc key (INPUT)
        processInput(window);

        // Rendering command
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // draw object (triangle)
        glUseProgram(shaderProgram);
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
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}