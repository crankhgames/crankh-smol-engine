#include "UIContainer.h"

namespace Core::UI {
    void UIContainer::add(std::unique_ptr<UIElement> element){
        if (!m_Elements.empty()){
            element->setPosition((*(m_Elements.end()-1))->getPosition() + Math::Vec2Int{0, (*(m_Elements.end()-1))->getScale().getY()});
        }
        else{
            element->setPosition(m_Position);
        }
        m_Elements.push_back(std::move(element));
    }

    void UIContainer::render(){
        for (auto it = m_Elements.begin(); it != m_Elements.end(); it++){
            (*it)->render();
        }
    }

}
