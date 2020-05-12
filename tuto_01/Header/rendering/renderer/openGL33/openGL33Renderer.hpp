#ifndef GAME_ENGINE_OPEN_GL_33_RENDERER_HPP
#define GAME_ENGINE_OPEN_GL_33_RENDERER_HPP

#include "rendering/renderer/IRenderer.hpp"
#include "rendering/renderer/openGL33/openGL33Window.hpp"
namespace GE
{
class openGL33Renderer: public IRenderer
{
    public:
        ~openGL33Renderer() override;
        void Initialize(SRendererCreateInfo& renderer_create_info) final;
        void Release()  final;
    private:
        OpenGL33Window m_window;
};
}
#endif