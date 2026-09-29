#pragma once

#include <filesystem>
#include <memory>


#include "UiElement.h"

namespace Core::UI::UiParser{
    std::unique_ptr<UiElement> createUiElementFromTag(std::string_view tag);
    std::unique_ptr<UiElement> createUiTree(std::filesystem::path uiConfigurations);
    std::vector<std::string> loadUiConfigurationFile(std::filesystem::path uiConfigurations);
}