#pragma once

#include <vector>
#include <memory>

#include "UiElement.h"
#include "SDL2/SDL.h"

namespace Core::UI {

    class UiContainer : public UiElement {
    private:
        std::vector<std::unique_ptr<UiElement>> m_Elements {};
        bool m_IsVertical {true};

        int m_GapSize {0};

    public:
        UiContainer(bool isVertical=true, int gapSize=0):
            m_IsVertical{isVertical}, m_GapSize{gapSize}
        {};

        ~UiContainer() {};

        void add(std::unique_ptr<UiElement> element);
        void setPosition(const Math::Vec2Int& position) override;
        bool onEvent(const SDL_Event& event) override;
        void render() override;
    };
}


