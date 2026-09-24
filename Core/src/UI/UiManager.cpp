#include "UiManager.h"

namespace Core::UI{
    std::unique_ptr<UiContainer> createContainer(bool isVertical, int gapSize) {
        return std::make_unique<UiContainer>(isVertical, gapSize);
    }
}