#include "App.h"

#include <iostream>
#include <print>
#include <bitset>
#include "Renderer/Renderer.h"
#include "SDL2/SDL_ttf.h"


namespace Core{

    static Application* s_Application {nullptr};

    Application::Application(const ApplicationSpecification& specification):
        m_Specification{specification}
    {
        s_Application = this;

        SDL_Init(SDL_INIT_EVERYTHING);
        TTF_Init();

        m_Window = std::make_unique<Window>(specification.windowSpecification);
        m_Window->init();
    }

    Application::~Application(){
        s_Application = nullptr;
        TTF_Quit();
        SDL_Quit();
    }

    void Application::run(){
        
        Renderer::loadAllTextures("assets/sprites/idle/");
        Renderer::loadAllTextures("assets/sprites/jump/");
        Renderer::loadAllTextures("assets/sprites/run/");
        Renderer::loadAllTextures("assets/sprites/tilemap/");

        m_IsRunning = true;

        for (auto& layer : m_LayerStack){
            layer->onStart();
        }

        Uint64 deltaTicks {SDL_GetTicks64()};


        while (m_IsRunning){

            Uint64 currentTicks {SDL_GetTicks64()};

            double timestep {SDL_clamp(deltaTicks / 1000.0, 0.000001, 0.1)};

            SDL_Event e{};
            
            while (SDL_PollEvent(&e)){
                for (auto it {m_LayerStack.rbegin()}; it != m_LayerStack.rend(); it++){
                    if (it->get()->onEvent(e)){
                        break;
                    }
                }

                // Quit window
                switch (e.type)
                {
                case SDL_QUIT:
                    m_IsRunning = false;
                    break;
                }

            }


            for (auto& layer : m_LayerStack){
                layer->onUpdate(timestep);
            }

            SDL_SetRenderDrawColor(&GET_APPLICATION().getWindow().getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(&Core::Application::Get().getWindow().getRenderer());

            for (auto& layer : m_LayerStack){
                layer->onRender();
            }

            SDL_RenderPresent(&m_Window->getRenderer());

            deltaTicks = SDL_GetTicks64() - currentTicks;


        }
    }

    Application& Application::Get(){
        return *s_Application;
    }

}