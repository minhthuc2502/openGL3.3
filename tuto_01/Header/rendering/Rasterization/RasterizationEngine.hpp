#ifndef GAME_ENGINE_RASTERIZATION_ENGINE_HPP
#define GAME_ENGINE_RASTERIZATION_ENGINE_HPP

#include "rendering/IRenderingEngine.hpp"

namespace GE
{
class RaspterizationEngine : public IRenderingEngine
{
    public:
        ~RaspterizationEngine()  override;
        void Initialize(SRenderingEngineCreateInfo& rendering_engine_create_info) final;
        void Release() final;
        void Render(float lag) final;
};
}

#endif