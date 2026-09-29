#pragma once

#include "Math/Math.h"
#include "SDL2/SDL.h"

#include <vector>
#include <memory>
#include <print>

namespace Core::UI {

    enum class UiAnchorHorizontal {
        left,
        center,
        right
    };

    enum class UiAnchorVertical {
        top,
        center,
        bottom
    };

    //struct UiStylingOptions {
        //SDL_Color color{0x000000FF};
        //SDL_Color backgroundColor{0xFFFFFFFF};

        //double marginLeft {};
        //double marginRight {};
        //double marginTop {};
        //double marginBottom {};
    //};
    
    class UiElement {
    protected:
        Math::Vec2Int m_Position {};
        Math::Vec2Int m_Scale {};

        Math::Vec2Int m_GlobalPosition {};

        std::vector<std::unique_ptr<UiElement>> m_Children {};


    public:
        UiElement():
            m_Position{}, m_Scale{}
        {}

        UiElement(Math::Vec2Int position, Math::Vec2Int scale):
            m_Position{position}, m_Scale{scale}, m_GlobalPosition{position}
        {}

        ~UiElement(){};

        virtual void add(std::unique_ptr<UiElement> uiElement, UiAnchorHorizontal anchorHorizontal=UiAnchorHorizontal::left, UiAnchorVertical anchorVertical=UiAnchorVertical::top);


        Math::Vec2Int getPosition() const {return m_Position;}
        Math::Vec2Int getScale() const {return m_Scale;}

        void setPosition(const Math::Vec2Int& position);

        void setScale(const Math::Vec2& scale){
            m_Scale = scale;
        }

        virtual bool onUserClick(const SDL_Event& event) { return false; }

        virtual bool onEvent(const SDL_Event& event) {

            bool executedEvent {false};

            switch (event.type){
            case SDL_MOUSEBUTTONDOWN:
                executedEvent |= onUserClick(event);
                break;
            }

            for (auto it = m_Children.begin(); it != m_Children.end(); it++){
                executedEvent |= (*it)->onEvent(event);
            }

            return executedEvent;
        }


        virtual void render();

        UiElement* getChild(int index);

    };

};