#ifndef GAME_ENGINE_OPEN_GL_33_WINDOW_HPP
#define GAME_ENGINE_OPEN_GL_33_WINDOW_HPP

#include "rendering/renderer/IWindow.hpp"

namespace GE
{
class OpenGL33Window: public IWindow{
public:
    ~OpenGL33Window() override;
    void initialize(const SWindowCreateInfo& window_create_info) final;
    void release() final;
};
}
#endif