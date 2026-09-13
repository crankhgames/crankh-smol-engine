#pragma once
#include "Math/Math.h"

namespace Core::Renderer{
    struct Tile {
        Math::Vec2Int srcPosition {};
        Math::Vec2Int srcTileSize {};
        Math::Vec2Int gridPosition {};
    };


}