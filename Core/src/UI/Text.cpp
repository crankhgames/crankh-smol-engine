#include "Text.h"

#include "Core/App.h"
#include "Renderer/Renderer.h"
#include "SDL_Pointers.h"

namespace Core::UI {
    void Text::render(){

        SurfacePtr textSurface {
            TTF_RenderText_Solid(m_Font.get(), m_Content.c_str(), m_Color)
        };

        TexturePtr fontTexture {SDL_CreateTextureFromSurface(&GET_APPLICATION().getWindow().getRenderer(), textSurface.get())};

        SDL_Rect destRect { m_Position.getX(), m_Position.getY(), m_Scale.getX(), m_Scale.getY() };
        SDL_SetRenderDrawColor(&GET_APPLICATION().getWindow().getRenderer(), m_Color.r, m_Color.g, m_Color.b, m_Color.a);
        Renderer::draw(fontTexture.get(), destRect);
        //std::println("Rendering text... {}", m_Content);
        //std::println("at position {}, {}", m_Position.getX(), m_Position.getY());
        //std::println("at scale {}, {}", m_Scale.getX(), m_Scale.getY());
        //std::println("with color r={}, g={}, b={}, a={}", m_Color.r, m_Color.g, m_Color.b, m_Color.a);

    }
}