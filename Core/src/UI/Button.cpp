#include "Button.h"
#include "Core/App.h"

namespace Core::UI {
    bool Button::onUserClick(const SDL_Event& event){
        if ((event.button.x < m_Position.getX() + m_Scale.getX() && event.button.x > m_Position.getX())
            && (event.button.y < m_Position.getY() + m_Scale.getY() && event.button.y > m_Position.getY())){

            m_ClickEvent();
            return true;
        }

        return false;
    }

    void Button::render(){
        SDL_SetRenderDrawColor(&GET_APPLICATION().getWindow().getRenderer(), m_Color.r, m_Color.g, m_Color.b, m_Color.a);
        SDL_Rect destRect {
            m_GlobalPosition.getX(), m_GlobalPosition.getY(), m_Scale.getX(), m_Scale.getY()
        };

        SDL_RenderFillRect(&GET_APPLICATION().getWindow().getRenderer(), &destRect);
    }
}