#ifndef GAME_ENGINE_I_RENDERER_HPP
#define GAME_ENGINE_I_RENDERER_HPP

#include "rendering/renderer/IWindow.hpp"

namespace GE
{
enum ERendererType
{
    openGL33,
    openGL45,
    Vulkan
};

struct SRendererCreateInfo
{
    ERendererType s_renderer_type;
    SWindowCreateInfo* p_window_create_info;
};
class IRenderer
{
    public: 
        virtual ~IRenderer() = default;
        virtual void Initialize(SRendererCreateInfo& renderer_create_info) = 0;
        virtual void Release()    = 0;

        IWindow* GetWindow();
    protected:
        bool m_initialized = false;
        IWindow* mp_window = nullptr;
};
}
#endif