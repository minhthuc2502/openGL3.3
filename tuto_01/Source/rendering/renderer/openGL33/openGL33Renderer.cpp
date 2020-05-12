#include "rendering/renderer/openGL33/openGL33Renderer.hpp"
#include <iostream>
namespace GE
{
    GE::openGL33Renderer::~openGL33Renderer()
    {
        Release();
    }

    void GE::openGL33Renderer::Initialize(SRendererCreateInfo& renderer_create_info)
    {
        if(m_initialized)
            Release();
        
        m_initialized = true;
        m_window.initialize(*renderer_create_info.p_window_create_info);
        mp_window = &m_window;
        
        std::cout << "OpenGL 3.3 renderer initialized" << std::endl;
    }

    void GE::openGL33Renderer::Release()
    {
        if(m_initialized)
        {
            m_window.release();
            mp_window = nullptr;
            m_initialized = false;
            std::cout << "OpenGL 3.3 renderer released" << std::endl;
        }
    }
}