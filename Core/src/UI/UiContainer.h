#pragma once

#include <vector>
#include <memory>

#include "UiElement.h"
#include "SDL2/SDL.h"

namespace Core::UI {

    class UiContainer : public UiElement {
    private:
        bool m_IsVertical {true};
        int m_GapSize {0};

        bool m_IsDraggable {false};

    public:
        UiContainer(bool isVertical=true, int gapSize=0, bool isDraggable=false, std::string id=""):
            UiElement{id}, m_IsVertical{isVertical}, m_GapSize{gapSize}, m_IsDraggable{isDraggable}
        {};

        ~UiContainer() {};

        void add(std::unique_ptr<UiElement> element, UiAnchorHorizontal anchorHorizontal, UiAnchorVertical anchorVertical) override;
        void render() override;

        bool onUserDrag(const SDL_Event& event) override;

    };
}


