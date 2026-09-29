#include "UiElement.h"

namespace Core::UI {

    void UiElement::setPosition(const Math::Vec2Int& position){
        Math::Vec2Int diff {position - m_Position};
        for (auto it = m_Children.begin(); it != m_Children.end(); it++){
            (*it)->setPosition((*it)->getPosition() + diff);
        }
        m_GlobalPosition += position - m_Position;
        m_Position = position;
    }

    void UiElement::render() {
        for (auto it = m_Children.begin(); it != m_Children.end(); it++){
            (*it)->render();
        }
    }

    void UiElement::add(std::unique_ptr<UiElement> uiElement, UiAnchorHorizontal anchorHorizontal, UiAnchorVertical anchorVertical){
        Math::Vec2Int offset{};
        switch (anchorHorizontal){
        case UiAnchorHorizontal::left:
            break;
        case UiAnchorHorizontal::center:
            offset.setX((getScale().getX() - uiElement->getScale().getX()) / 2);
            break;
        case UiAnchorHorizontal::right:
            offset.setX(getScale().getX() - uiElement->getScale().getX());
            break;
        }

        switch (anchorVertical){
        case UiAnchorVertical::top:
            break;
        case UiAnchorVertical::center:
            offset.setY((getScale().getY() - uiElement->getScale().getY()) / 2);
            break;
        case UiAnchorVertical::bottom:
            offset.setY(getScale().getY() - uiElement->getScale().getY());
            break;
        }

        uiElement->setPosition(m_Position + offset);
        m_Children.push_back(std::move(uiElement));
    }

    UiElement* UiElement::getChild(int index){
        return m_Children[index].get();
    }
};