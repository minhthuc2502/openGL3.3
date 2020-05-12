#include "rendering/IRenderingEngine.hpp"

namespace GE
{
    IRenderer* GE::IRenderingEngine::GetRenderrer()
    {
        return mp_renderrer;
    }
}