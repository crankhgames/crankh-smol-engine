#include "UiContainer.h"
#include "SDL2/SDL.h"
#include "Core/App.h"

namespace Core::UI {
    void UiContainer::add(std::unique_ptr<UiElement> element, UiAnchorHorizontal anchorHorizontal, UiAnchorVertical anchorVertical){
        
        if (!m_Children.empty()){
            
            if (m_IsVertical){
                Math::Vec2Int offset {};
                element->setPosition(m_Position + Math::Vec2Int{0, m_GapSize + m_Scale.getY()});
                m_Scale += Math::Vec2Int{0, m_GapSize + element->getScale().getY()};
                m_Scale.setX(std::max(m_Scale.getX(), element->getScale().getX()));
            }
            else{
                element->setPosition(m_Position + Math::Vec2Int{m_GapSize + m_Scale.getX(), 0});
                m_Scale += Math::Vec2Int{m_GapSize + element->getScale().getX(), 0};
                m_Scale.setY(std::max(m_Scale.getY(), element->getScale().getY()));
            }
        }
        else{
            element->setPosition(m_Position);
            m_Scale = element->getScale();
        }
        m_Children.push_back(std::move(element));
    }

    void UiContainer::render(){
        SDL_SetRenderDrawColor(&GET_APPLICATION().getWindow().getRenderer(), 0xFF, 0x00, 0x00, 0xFF);
        SDL_Rect boundingBox {m_GlobalPosition.getX(), m_GlobalPosition.getY(), m_Scale.getX(), m_Scale.getY()};
        SDL_RenderDrawRect(&GET_APPLICATION().getWindow().getRenderer(), &boundingBox);

        UiElement::render();
    }


}
