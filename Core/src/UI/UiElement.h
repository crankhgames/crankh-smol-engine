#pragma once

#include "Math/Math.h"
#include "SDL2/SDL.h"

#include <vector>
#include <memory>
#include <print>

namespace Core::UI {
    
    class UiElement {
    protected:
        Math::Vec2Int m_Position {};
        Math::Vec2Int m_Scale {};

        Math::Vec2Int m_GlobalPosition {};

    public:
        UiElement():
            m_Position{}, m_Scale{}
        {}

        UiElement(Math::Vec2Int position, Math::Vec2Int scale):
            m_Position{position}, m_Scale{scale}, m_GlobalPosition{position}
        {}

        ~UiElement(){};


        Math::Vec2Int getPosition() const {return m_Position;}
        Math::Vec2Int getScale() const {return m_Scale;}

        virtual void setPosition(const Math::Vec2Int& position){
            m_GlobalPosition += position - m_Position;
            m_Position = position;
        }
        void setScale(const Math::Vec2& scale){
            m_Scale = scale;
        }

        virtual bool onUserClick(const SDL_Event& event) { return false; }

        virtual bool onEvent(const SDL_Event& event) {
            switch (event.type){
            case SDL_MOUSEBUTTONDOWN:
                return onUserClick(event);
            }

            return false;
        }

        virtual void render() {
            std::println("Rendering UI Element...");
        }

    };

};