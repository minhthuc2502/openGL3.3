#include "rendering/Rasterization/RasterizationEngine.hpp"
#include "rendering/renderer/openGL33/openGL33Renderer.hpp"
#include <iostream>
using namespace std;
namespace GE
{
    GE::RaspterizationEngine::~RaspterizationEngine()
    {
        Release();
    }

    void GE::RaspterizationEngine::Initialize(SRenderingEngineCreateInfo& rendering_engine_create_info)
    {
        if(m_intialized)
            Release();
        switch(rendering_engine_create_info.p_renderer_info->s_renderer_type)
        {
            case openGL33:
                mp_renderrer = new openGL33Renderer();
                break;
            case openGL45:
                throw runtime_error("OpenGL 4.5 renderer not implemented");
            case Vulkan:
                throw runtime_error("Vulkan renderer not implemented");
        }
        if(!mp_renderrer)
            throw bad_alloc();
        
        m_intialized = true;
        mp_renderrer->Initialize(*rendering_engine_create_info.p_renderer_info);

        cout<< "Rasterization initialized." << endl; 
    }

    void GE::RaspterizationEngine::Release()
    {
        if(m_intialized)
        {
            mp_renderrer->Release();
            delete mp_renderrer;
            mp_renderrer = nullptr;
            m_intialized = false;
            cout<< "Rasterization released." << endl; 
        }
    }
    
    void GE::RaspterizationEngine::Render(float lag)
    {
        glfwSwapBuffers(mp_renderrer->GetWindow()->GetHandler());
    }
}