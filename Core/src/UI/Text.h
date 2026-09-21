#pragma once

#include "SDL2/SDL_ttf.h"
#include "SDL_Pointers.h"
#include "UIElement.h"

#include <memory>
#include <string>
#include <string_view>
#include <print>

namespace Core::UI{
    class Text : public UIElement {
    private:
        FontPtr m_Font {};
        SDL_Color m_Color {};
        std::string m_Content {};

    public:
        Text(Math::Vec2Int m_Position, Math::Vec2Int m_Scale, std::string_view content, int ptSize, const char* filename, SDL_Color color) : 
            UIElement{m_Position, m_Scale},  m_Font {TTF_OpenFont(filename, ptSize)}, m_Color{color}, m_Content{content}
        {
            if (m_Font.get()){
                std::println("Good font loaded !");
            }
            else {
                std::println("Error, font not loaded");
            }
        };

        ~Text() {};

        void render();
    };
}