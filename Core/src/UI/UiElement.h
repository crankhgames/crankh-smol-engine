#pragma once

#include "Math/Math.h"
#include "SDL2/SDL.h"
#include "SDL_Pointers.h"

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

    struct UiStylingOptions {
        SDL_Color color{0, 0, 0, 255};
        SDL_Color backgroundColor{0, 0, 0, 0};

        double marginLeft {};
        double marginRight {};
        double marginTop {};
        double marginBottom {};

        bool isDraggable {false};
        bool isVertical {false};

        Math::Vec2Int position{};
        Math::Vec2Int scale{};

        TexturePtr imageTexture {};
        FontPtr font {};
    };
    
    class UiElement {
    protected:
        Math::Vec2Int m_Position {};
        Math::Vec2Int m_Scale {};

        Math::Vec2Int m_GlobalPosition {};

        std::vector<std::unique_ptr<UiElement>> m_Children {};
        std::string m_Id{""};

        bool dragging{false};
        bool background{false};
        Math::Vec2Int dragPoint{};

    public:
        UiElement(std::string id=""):
            m_Position{}, m_Scale{}, m_Id{id}
        {}

        UiElement(Math::Vec2Int position, Math::Vec2Int scale, std::string id=""):
            m_Position{position}, m_Scale{scale}, m_GlobalPosition{position}, m_Id{id}
        {}

        ~UiElement(){};

        virtual void add(std::unique_ptr<UiElement> uiElement, UiAnchorHorizontal anchorHorizontal=UiAnchorHorizontal::left, UiAnchorVertical anchorVertical=UiAnchorVertical::top);


        Math::Vec2Int getPosition() const {return m_Position;}
        Math::Vec2Int getScale() const {return m_Scale;}
        UiElement* getChild(int index);
        std::string getId() {return m_Id;}

        UiElement* getElementById(std::string_view id);

        void setBackground(bool hasBackground) {background = hasBackground;}
        void setPosition(const Math::Vec2Int& position);
        void setScale(const Math::Vec2& scale){
            m_Scale = scale;
        }

        virtual bool onUserClick(const SDL_Event& event) { return false; }
        virtual bool onUserDrag(const SDL_Event& event) {return false;}

        virtual bool onEvent(const SDL_Event& event);


        virtual void render();


        

    };

};