#include "Image.h"
#include "Renderer/Renderer.h"

namespace Core::UI {
    void Image::render(){
        SDL_Rect destRect {
            m_GlobalPosition.getX(), m_GlobalPosition.getY(), m_Scale.getX(), m_Scale.getY()
        };

        Renderer::draw(m_ImageTexture, destRect);
        UiElement::render();
    }

    void Image::changeTexture(std::string_view filename, double scaleFactor){
        m_ImageTexture = Renderer::getTexture(filename.data());

        //int width{};
        //int height{};

        //SDL_QueryTexture(m_ImageTexture, NULL, NULL, &width, &height);

        //m_Scale.set(static_cast<int>(width*scaleFactor), static_cast<int>(height*scaleFactor));
    }
}