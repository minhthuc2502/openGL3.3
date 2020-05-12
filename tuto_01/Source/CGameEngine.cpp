#include "CGameEngine.hpp"
#include "rendering/Rasterization/RasterizationEngine.hpp"
#include <stdexcept>
#include <iostream>
namespace GE
{
    GE::CGameEngine::~CGameEngine()
    {
        Release();
    }

    void GE::CGameEngine::Initialized(const CGameEngineCreateInfo& game_engine_create_info)
    {
        if(m_initialized)
            Release();
        switch(game_engine_create_info.p_rendering_engine_create_info->e_rendering_engine_type)
        {
            case Rasterization:
                mp_rendering_engine = new RaspterizationEngine();
                break;
            case RayTracingCPU:
                throw std::runtime_error("CPU Ray tracing engine not implemented");
            case RayTracingGPU:
                throw std::runtime_error("GPU Ray tracing engine not implemented");
        }
        if(!mp_rendering_engine)
        {
            throw std::bad_alloc();
        }
        mp_rendering_engine->Initialize(*game_engine_create_info.p_rendering_engine_create_info);
        std::cout << "Game engine initialized" << std::endl;
        m_initialized = true;
    }

    void GE::CGameEngine::Release()
    {
        if(m_initialized)
        {
            m_initialized = false;
            mp_rendering_engine->Release();
            delete mp_rendering_engine;
            mp_rendering_engine = nullptr;
            std::cout << "Game engine released" << std::endl;
        }
    }

    void GE::CGameEngine::Run()
    {
        if(!m_initialized)
            throw std::runtime_error("Game engine not initialized");

        GLFWwindow* p_window = mp_rendering_engine->GetRenderrer()->GetWindow()->GetHandler();

        // Timers
        double lag = 0.0;
        double previous = glfwGetTime();
        double SECONDS_PER_UPDATE = 1.0 / 60.0;

        while(!glfwWindowShouldClose(p_window) && glfwGetKey(p_window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
        {
            double current = glfwGetTime();
            double elapsed = current - previous;
            previous = current;
            lag += elapsed;
            glfwPollEvents();
            while(lag >= SECONDS_PER_UPDATE)
            {
                lag -= SECONDS_PER_UPDATE;
            }
            mp_rendering_engine->Render(static_cast<float>((float) lag/SECONDS_PER_UPDATE));
        }
    }
}