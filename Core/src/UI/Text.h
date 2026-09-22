#pragma once

#include "SDL2/SDL_ttf.h"
#include "SDL_Pointers.h"
#include "UiElement.h"
#include "Core/App.h"

#include <memory>
#include <string>
#include <string_view>
#include <print>

namespace Core::UI{
    class Text : public UiElement {
    private:
        FontPtr m_Font {};
        SDL_Color m_Color {};
        std::string m_Content {};

        TexturePtr m_FontTexture {};

    public:
        Text(Math::Vec2Int position, Math::Vec2Int scale, std::string_view content, int ptSize, const char* filename, SDL_Color color) : 
            UiElement{position, scale},  m_Font {TTF_OpenFont(filename, ptSize)}, m_Color{color}, m_Content{content}
        {
            if (m_Font.get()){
                std::println("Good font loaded !");
            }
            else {
                std::println("Error, font not loaded");
            }

            SurfacePtr textSurface {
                TTF_RenderText_Solid(m_Font.get(), m_Content.c_str(), m_Color)
            };
            m_FontTexture.reset({SDL_CreateTextureFromSurface(&GET_APPLICATION().getWindow().getRenderer(), textSurface.get())});
        };

        Text(std::string_view content, int ptSize, const char* filename):
            UiElement{}, m_Font{TTF_OpenFont(filename, ptSize)}, m_Color{0x000000}, m_Content{content}
        {}

        ~Text() {};

        void render();

        void setScale (const Math::Vec2Int& scale) {
            m_Scale = scale;
        }

        void setColor(SDL_Color color){
            m_Color = color;
        }
        
        void setColor(int r, int g, int b, int a = SDL_ALPHA_OPAQUE){
            m_Color.r = r;
            m_Color.g = g;
            m_Color.b = b;
            m_Color.a = a;
        }
    };
}