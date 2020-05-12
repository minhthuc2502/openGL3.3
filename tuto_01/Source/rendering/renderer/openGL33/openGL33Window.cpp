#include "rendering/renderer/openGL33/openGL33Window.hpp"
#include <iostream>
using namespace std;
namespace GE
{
    void errorCallback(int error, const char* description)
    {
        cerr << "Error: " << description << endl;
    }

    GE::OpenGL33Window::~OpenGL33Window()
    {
        release(); 
    }

    void GE::OpenGL33Window::initialize(const GE::SWindowCreateInfo& window_create_info)
    {
        if(m_initialized)
        {
            release();
        }

        cout << "Initializing openGL 3.3 window" << endl;
        if(!glfwInit())
        {
            throw runtime_error("Failed to initialize GLFW");
        }
        glfwSetErrorCallback(errorCallback);
        // active antialiasing mode
        glfwWindowHint(GLFW_SAMPLES, 4);
        // version of opengl
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        // 
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        mp_window = glfwCreateWindow(
                                window_create_info.window_width,
                                window_create_info.window_height,
                                window_create_info.p_window_title,
                                nullptr,nullptr);
        if(!mp_window)
        {
            glfwTerminate();
            throw runtime_error("Failed to initialize the window");
        }

        glfwMakeContextCurrent(mp_window);

        glewExperimental = GL_TRUE;
        if(glewInit() != GLEW_OK)
        {
            glfwTerminate();
            throw runtime_error("Failed to initialize glew");
        }
        glfwSetInputMode(mp_window, GLFW_STICKY_KEYS, GLFW_TRUE);
        m_initialized = true;
        cout << "openGL 3.3 window initialized" << endl;
    }

    void GE::OpenGL33Window::release()
    {
        if(m_initialized)
        {
            glfwTerminate();
            mp_window = nullptr;
            m_initialized = false;
            cout << "Window openGL 3.3 released" << endl;
        }
    }
}