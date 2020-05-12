#include <iostream>
#include <stdexcept>
#include "CGameEngine.hpp"

int main(int argc, char** argv)
{
    GE::SWindowCreateInfo window_create_info {};
    window_create_info.window_width = 1280;
    window_create_info.window_height = 720;
    window_create_info.p_window_title = "Turorial_01";

    GE::SRendererCreateInfo renderer_create_info {};
    renderer_create_info.p_window_create_info = &window_create_info;
    renderer_create_info.s_renderer_type = GE::ERendererType::openGL33;
    
    GE::SRenderingEngineCreateInfo renderer_engine_create_info {} ;
    renderer_engine_create_info.p_renderer_info = &renderer_create_info;
    renderer_engine_create_info.e_rendering_engine_type = GE::ERenderingEngineType::Rasterization;

    GE::CGameEngineCreateInfo cgame_engine_create_info {};
    cgame_engine_create_info.p_rendering_engine_create_info = &renderer_engine_create_info;

    GE::CGameEngine game_engine;
    try
    {
        game_engine.Initialized(cgame_engine_create_info);
        game_engine.Run();
    }
    catch(std::runtime_error& error)
    {
        std::cerr << "Exception: " << error.what() << std::endl;
    }
    catch(std::bad_alloc& error)
    {
        std::cerr << "Exception: " << error.what() << std::endl;
    }
    //game_engine.Release();
    return 0;
}