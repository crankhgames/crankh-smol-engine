#pragma once

#include "UiContainer.h"
#include "UiElement.h"
#include "Text.h"

#include <vector>

namespace Core::UI
{

    std::unique_ptr<UiContainer> createContainer(bool isVertical, int gapSize);

    struct UiAnchorPoint{
        UiAnchorHorizontal anchorX{};
        UiAnchorVertical anchorY{};
    };

    template <typename T>
    void attachUiElement(UiElement* parentElement, UiAnchorPoint anchorPoint, std::unique_ptr<T> uiElement){
        parentElement->add(std::move(uiElement), anchorPoint.anchorX, anchorPoint.anchorY);
    }
    template <typename T, typename... Args>
    void attachUiElement(UiElement* parentElement, UiAnchorPoint anchorPoint, Args&&... args){
        parentElement->add(std::make_unique<T>(std::forward<Args>(args)...), anchorPoint.anchorX, anchorPoint.anchorY);
    }

}