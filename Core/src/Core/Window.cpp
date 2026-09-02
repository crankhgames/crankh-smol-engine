#include "Window.h"
#include <print>

namespace Core
{
    Window::Window(const WindowSpecification& specification):
        m_Specification{specification}
    {}

    Window::~Window(){
        SDL_DestroyRenderer(m_Renderer);
        SDL_DestroyWindow(m_Window);
    }


    void Window::init(){
        int fullscreenFlags = SDL_WINDOW_SHOWN;
        if (m_Specification.isFullScreen){
            fullscreenFlags = SDL_WINDOW_FULLSCREEN;
        }

        m_Window = SDL_CreateWindow(
            m_Specification.title.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            m_Specification.width,
            m_Specification.height,
            fullscreenFlags
        );


        if (!m_Window){
            //SDL_LogError(0, "Window not initialized properly...");
            std::println("Window not initialized properly...");
            return;
        }

        m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
        
        if (!m_Renderer){
            //SDL_LogError(0, "Renderer not initialized properly...");
            std::println("Renderer not initialized properly...");
            return;
        }


        
    }
}
