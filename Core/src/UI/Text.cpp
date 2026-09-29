#include "Text.h"

#include "Core/App.h"
#include "Renderer/Renderer.h"
#include "SDL_Pointers.h"

#include "Math/Math.h"

namespace Core::UI
{
    void Text::render()
    {
        SDL_Rect destRect{m_GlobalPosition.getX(), m_GlobalPosition.getY(), m_Scale.getX(), m_Scale.getY()};

        Renderer::draw(m_FontTexture.get(), destRect);

        UiElement::render();
    }

    void Text::setContent(std::string_view newContent){
        m_Content = newContent;
        
        SurfacePtr textSurface {
            TTF_RenderText_Solid(m_Font.get(), m_Content.c_str(), m_Color)
        };
        m_FontTexture.reset({SDL_CreateTextureFromSurface(&GET_APPLICATION().getWindow().getRenderer(), textSurface.get())});

        int textureWidth {};
        int textureHeight {};
        SDL_QueryTexture(m_FontTexture.get(), NULL, NULL, &textureWidth, &textureHeight);

        m_Scale.set(textureWidth, textureHeight);

    }
}