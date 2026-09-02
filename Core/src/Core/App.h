#pragma once

#include "Window.h"
#include "Layer.h"

#include <string>
#include <memory>
#include <vector>


namespace Core{

    struct ApplicationSpecification{
        std::string name{};
        WindowSpecification windowSpecification{};
    };
    
    class Application{

    private:
        ApplicationSpecification m_Specification;
        std::shared_ptr<Window> m_Window;

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
        
        void run();

        static Application& Get();
        std::shared_ptr<Window> getWindow() const {return m_Window;}

        friend class Layer;

    };

    #define GET_APPLICATION() Core::Application::Get() 

}