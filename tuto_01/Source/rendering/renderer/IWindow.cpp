#include "rendering/renderer/IWindow.hpp"

GLFWwindow* GE::IWindow::GetHandler()
{
    return mp_window;
}
