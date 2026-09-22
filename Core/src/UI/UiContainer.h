#pragma once

#include <vector>
#include <memory>

#include "UiElement.h"

namespace Core::UI {

    class UiContainer : public UiElement {
    private:
        std::vector<std::unique_ptr<UiElement>> m_Elements {};
        bool m_IsVertical {true};

    public:
        UiContainer(bool isVertical=true):
            m_IsVertical{isVertical}
        {};

        ~UiContainer() {};

        void add(std::unique_ptr<UiElement> element);
        void render();
    };
}


