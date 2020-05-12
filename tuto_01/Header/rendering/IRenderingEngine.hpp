#ifndef GAME_ENGINE_I_RENDERING_ENGINE_HPP
#define GAME_ENGINE_I_RENDERING_ENGINE_HPP

#include "rendering/renderer/IRenderer.hpp"

namespace GE
{

enum ERenderingEngineType
{
    Rasterization,
    RayTracingCPU,
    RayTracingGPU
};

struct SRenderingEngineCreateInfo
{
    ERenderingEngineType e_rendering_engine_type;
    SRendererCreateInfo* p_renderer_info;
};

class IRenderingEngine
{
    public:
        virtual ~IRenderingEngine() = default;
        virtual void Initialize(SRenderingEngineCreateInfo& rendering_engine_create_info) = 0;
        virtual void Release() = 0;
        virtual void Render(float lag) = 0;
        IRenderer* GetRenderrer();
    protected:
        bool m_intialized = false;
        IRenderer* mp_renderrer = nullptr;
};
}
#endif