#pragma once

#include "UiContainer.h"
#include "UiElement.h"
#include "Text.h"

#include <vector>

namespace Core::UI
{

    namespace {
        std::unique_ptr<UiContainer> selectedContainer {};
    }

    std::unique_ptr<UiContainer> createContainer(bool isVertical, int gapSize);

    template <typename T>
    void attachUiElementToContainer(UiContainer* container, std::unique_ptr<T> uiElement){
        container->add(std::move(uiElement));
    }
    template <typename T, typename... Args>
    void attachUiElementToContainer(UiContainer* container, Args&&... args){
        container->add(std::make_unique<T>(std::forward<Args>(args)...));
    }

    static void selectContainer(UiContainer* uiContainer){
        selectedContainer.reset(uiContainer);
    }


}