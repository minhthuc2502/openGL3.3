#ifndef C_GAME_ENGINE_HPP
#define C_GAME_ENGINE_HPP

#include "rendering/IRenderingEngine.hpp"
namespace GE
{
struct CGameEngineCreateInfo
{
    SRenderingEngineCreateInfo* p_rendering_engine_create_info;
};

class CGameEngine
{
    public:
        ~CGameEngine();
        void Initialized(const CGameEngineCreateInfo& game_engine_create_info);
        void Release();
        void Run();
    private:
        bool m_initialized = false;
        IRenderingEngine* mp_rendering_engine = nullptr;
};
}
#endif