#include "UiContainer.h"

namespace Core::UI {
    void UiContainer::add(std::unique_ptr<UiElement> element){
        if (!m_Elements.empty()){
            
            if (m_IsVertical){
                element->setPosition((*(m_Elements.end()-1))->getPosition() + Math::Vec2Int{0, (*(m_Elements.end()-1))->getScale().getY()});
            }
            else{
                element->setPosition((*(m_Elements.end()-1))->getPosition() + Math::Vec2Int{(*(m_Elements.end()-1))->getScale().getX(), 0});
            }
        }
        else{
            element->setPosition(m_Position);
        }
        m_Elements.push_back(std::move(element));
    }

    void UiContainer::render(){
        for (auto it = m_Elements.begin(); it != m_Elements.end(); it++){
            (*it)->render();
        }
    }

}
