#include "UiElement.h"
#include "Core/App.h"

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
        if (background){

            SDL_SetRenderDrawColor(&GET_APPLICATION().getWindow().getRenderer(), 230, 230, 230, 100);
            SDL_Rect rect {
                m_GlobalPosition.getX(), m_GlobalPosition.getY(), m_Scale.getX(), m_Scale.getY()
            };

            SDL_RenderFillRect(&GET_APPLICATION().getWindow().getRenderer(), &rect);
        }

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

    UiElement* UiElement::getElementById(std::string_view id){
        if (m_Id == id){
            return this;
        }

        for (auto& child : m_Children){
            auto resultElement {child->getElementById(id)};

            if (resultElement){
                return resultElement;
            }
        }

        return nullptr;
    }

    bool UiElement::onEvent(const SDL_Event& event){

        bool executedEvent {false};

        switch (event.type){
        case SDL_MOUSEBUTTONDOWN:
            executedEvent |= onUserClick(event);
            if ((m_GlobalPosition.getX() <= event.button.x && event.button.x <= m_GlobalPosition.getX() + m_Scale.getX()) 
                && (m_GlobalPosition.getY() <= event.button.y && event.button.y <= m_GlobalPosition.getY() + m_Scale.getY()) 
            ){
                dragging = true;
                dragPoint = Math::Vec2Int{event.button.x, event.button.y} - m_GlobalPosition;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            dragging = false;
            break;
        case SDL_MOUSEMOTION:
            if (dragging){
                executedEvent |= onUserDrag(event);
            }
            break;
        case SDL_KEYDOWN:
            executedEvent |= onUserKeyboardPress(event);
            break;
        case SDL_TEXTINPUT:
            executedEvent |= onUserInputText(event);
            break;
        }

        for (auto it = m_Children.begin(); it != m_Children.end(); it++){
            executedEvent |= (*it)->onEvent(event);
        }

        return executedEvent;
    }
};