#ifndef GAME_ENGINE_I_WINDOW_HPP
#define GAME_ENGINE_I_WINDOW_HPP
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace GE
{
struct SWindowCreateInfo
{
    int window_width;
    int window_height;
    const char* p_window_title;
};
 
class IWindow
{
    public:
        virtual ~IWindow() = default;
        virtual void initialize(const SWindowCreateInfo& window_create_info) = 0;
        virtual void release() = 0;
        GLFWwindow* GetHandler();
    protected:
        bool m_initialized = false;
        GLFWwindow* mp_window = nullptr;
};
}
#endif