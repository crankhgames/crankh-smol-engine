#include "UiContainer.h"
#include "SDL2/SDL.h"
#include "Core/App.h"

namespace Core::UI {
    void UiContainer::add(std::unique_ptr<UiElement> element){
        if (!m_Elements.empty()){
            
            if (m_IsVertical){
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
        m_Elements.push_back(std::move(element));
    }

    void UiContainer::setPosition(const Math::Vec2Int& position){
        Math::Vec2Int diff {position - m_Position};
        for (auto it = m_Elements.begin(); it != m_Elements.end(); it++){
            (*it)->setPosition((*it)->getPosition() + diff);
        }
        m_GlobalPosition += position - m_Position;
        m_Position = position;
    }

    void UiContainer::render(){
        for (auto it = m_Elements.begin(); it != m_Elements.end(); it++){
            (*it)->render();
        }

        SDL_SetRenderDrawColor(&GET_APPLICATION().getWindow().getRenderer(), 0xFF, 0x00, 0x00, 0xFF);
        SDL_Rect boundingBox {m_GlobalPosition.getX(), m_GlobalPosition.getY(), m_Scale.getX(), m_Scale.getY()};
        SDL_RenderDrawRect(&GET_APPLICATION().getWindow().getRenderer(), &boundingBox);
    }

    bool UiContainer::onEvent(const SDL_Event& event){
        bool executedEvent {false};

        for (auto it = m_Elements.begin(); it != m_Elements.end(); it++){
            executedEvent |= (*it)->onEvent(event);
        }

        return executedEvent;
    }

}
