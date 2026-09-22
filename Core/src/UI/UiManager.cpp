#include "UiManager.h"

namespace Core::UI{
    std::unique_ptr<UiContainer> createContainer(bool isVertical) {
        return std::make_unique<UiContainer>(isVertical);
    }
}