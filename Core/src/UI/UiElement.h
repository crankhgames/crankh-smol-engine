#pragma once

#include "Math/Math.h"

#include <vector>
#include <memory>
#include <print>

namespace Core::UI {
    
    class UiElement {
    protected:
        Math::Vec2Int m_Position {};
        Math::Vec2Int m_Scale {};

    public:
        UiElement():
            m_Position{}, m_Scale{}
        {}

        UiElement(Math::Vec2Int position, Math::Vec2Int scale):
            m_Position{position}, m_Scale{scale}
        {}

        ~UiElement(){};


        Math::Vec2Int getPosition() const {return m_Position;}
        Math::Vec2Int getScale() const {return m_Scale;}

        void setPosition(const Math::Vec2& position){
            m_Position = position;
        }
        void setScale(const Math::Vec2& scale){
            m_Scale = scale;
        }

        virtual void render() {
            std::println("Rendering UI Element...");
        };

    };

};