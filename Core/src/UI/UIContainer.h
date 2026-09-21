#pragma once

#include <vector>
#include <memory>

#include "UIElement.h"

namespace Core::UI {

    class UIContainer : public UIElement {
    private:
        std::vector<std::unique_ptr<UIElement>> m_Elements {};
        bool m_IsVertical {true};

    public:
        UIContainer(bool isVertical=true):
            m_IsVertical{isVertical}
        {};

        ~UIContainer() {};

        void add(std::unique_ptr<UIElement> element);
        void render();
    };
}


