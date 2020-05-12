#include "rendering/renderer/IRenderer.hpp"

namespace GE
{

IWindow* IRenderer::GetWindow()
{
    return mp_window;
}
} // namespace GE
