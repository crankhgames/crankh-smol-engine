#include "App.h"

#include <iostream>
#include <print>
#include <bitset>
#include "Renderer/Renderer.h"

namespace Core{

    static Application* s_Application {nullptr};
    SDL_Texture* tex{};

    Application::Application(const ApplicationSpecification& specification):
        m_Specification{specification}
    {
        s_Application = this;

        SDL_Init(SDL_INIT_EVERYTHING);

        m_Window = std::make_shared<Window>(specification.windowSpecification);
        m_Window->init();



    }

    Application::~Application(){
        s_Application = nullptr;
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
                for (auto& layer : m_LayerStack){
                    layer->onEvent(e);
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
            for (auto& layer : m_LayerStack){
                layer->onRender();
            }

            SDL_RenderPresent(m_Window->getRenderer());

            deltaTicks = SDL_GetTicks64() - currentTicks;


        }
    }

    Application& Application::Get(){
        return *s_Application;
    }

}