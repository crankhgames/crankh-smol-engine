#include "Image.h"
#include "Renderer/Renderer.h"

namespace Core::UI {
    void Image::render(){
        SDL_Rect destRect {
            m_GlobalPosition.getX(), m_GlobalPosition.getY(), m_Scale.getX(), m_Scale.getY()
        };

        Renderer::draw(m_ImageTexture.get(), destRect);
        UiElement::render();
    }
}