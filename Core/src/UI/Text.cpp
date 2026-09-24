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

        SDL_SetRenderDrawColor(&GET_APPLICATION().getWindow().getRenderer(), m_Color.r, m_Color.g, m_Color.b, m_Color.a);
        Renderer::draw(m_FontTexture.get(), destRect);
    }
}