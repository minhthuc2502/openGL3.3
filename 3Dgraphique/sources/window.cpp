#include "window.hpp"

void processFrameBufferSize(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void window::initialize()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // using open gl core proifle to opengl more effective and flexible but more difficult => need to use it
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    mpwindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if (mpwindow == NULL)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GFLW Window");
    }
    glfwMakeContextCurrent(mpwindow);
    /**
     * call glad to manage all function of OpenGL that we want to use before call function openGL
     * glfw provide glfwGetProcAddress to define correct function base on OS compile for
     * glad load adress of the OpenGL function pointers. 
     */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize glad");
    }
    /**
     * tell openGL size to render on window
    */
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(mpwindow, processFrameBufferSize);
    // Disable mouse's cursor
    glfwSetInputMode(mpwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    std::cout << "Window Initialized" << std::endl;
}

void window::terminate()
{
    glfwTerminate();
    if(title != NULL)
        free(title);
    std::cout << "Window Terminated" << std::endl;
}

float window::getWidth()
{
    return width;
}

float window::getHeight()
{
    return height;
}