#pragma once
#include <nlohmann/json.hpp>
#include <filesystem>

#include "ECS/Scene.h"

namespace Core::Renderer {
    ECS::Entity loadTilemap(std::filesystem::path tilemapFile, ECS::Scene& scene);
}

