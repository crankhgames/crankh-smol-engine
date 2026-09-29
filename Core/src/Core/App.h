#pragma once

#include "Window.h"
#include "Layer.h"

#include <string>
#include <memory>
#include <vector>
#include <queue>

#include "SDL_Pointers.h"

namespace Core{

    struct ApplicationSpecification{
        std::string name{};
        WindowSpecification windowSpecification{};
    };
    
    class Application{

    private:
        ApplicationSpecification m_Specification;
        std::unique_ptr<Window> m_Window;

        std::vector<std::unique_ptr<Layer>> m_LayerStack{};

        bool m_IsRunning{};

    public:

        Application(const ApplicationSpecification& specification);
        ~Application();

        template<typename TLayer>
        requires(std::is_base_of_v<Layer, TLayer>)
        void pushLayer(){
            m_LayerStack.push_back(std::make_unique<TLayer>());
        }

        template<typename T>
        T* getLayer(){
            for (auto it {m_LayerStack.begin()}; it != m_LayerStack.end(); ++it){
                if (dynamic_cast<T*>(it->get())){
                    return dynamic_cast<T*>(it->get());
                }
            }

            return nullptr;
        }
        
        void run();

        static Application& Get();
        Window& getWindow() const {return *m_Window;}

        friend class Layer;

    };

    #define GET_APPLICATION() Core::Application::Get() 

}