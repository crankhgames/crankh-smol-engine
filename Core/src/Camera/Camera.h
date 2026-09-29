#pragma once
#include "Core/App.h"
#include "ECS/Scene.h"
#include "ECS/Components.h"
#include "Math/Math.h"

namespace Core::Camera{

    Math::Vec2 screenToWorld(ECS::Entity cameraEntity, const Math::Vec2Int& screenPosition);
    Math::Vec2Int worldToScreen(ECS::Entity cameraEntity, const Math::Vec2& worldPosition);
}