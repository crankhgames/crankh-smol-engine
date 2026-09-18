#pragma once

#include <string>
#include <memory>

#include "Math/Math.h"

#include "SDL2/SDL.h"
#include "SDL_Pointers.h"

namespace Core
{
    struct WindowSpecification{
        std::string title{};
        int width{1920};
        int height{1080};
        bool isFullScreen{false};
    };

    class Window{
        private:
            WindowSpecification m_Specification{};
            
            WindowPtr m_Window{};
            RendererPtr m_Renderer{};

        public:
            Window(const WindowSpecification& specification);
            ~Window();

            void init();

            SDL_Window& getWindow() const {return *m_Window;}
            SDL_Renderer& getRenderer() const {return *m_Renderer;}

            int getWidth() const {return m_Specification.width;}
            int getHeight() const {return m_Specification.height;}

            Math::Vec2 getWindowSize() const { 
                return Math::Vec2 {static_cast<double>(m_Specification.width), static_cast<double>(m_Specification.height)};
            }


    };
}
