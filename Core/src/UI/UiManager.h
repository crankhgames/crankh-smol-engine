#pragma once

#include "UiContainer.h"
#include "Text.h"

#include <vector>

namespace Core::UI
{


    std::unique_ptr<UiContainer> createContainer(bool isVertical);

    template <typename T, typename... Args>
    void attachUiElementToContainer(UiContainer* container, Args&&... args){
        container->add(std::make_unique<T>(std::forward<Args>(args)...));
    }
}