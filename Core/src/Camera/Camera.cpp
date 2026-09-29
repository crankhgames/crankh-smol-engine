#include "Camera.h"

namespace Core::Camera {
    Math::Vec2 screenToWorld(ECS::Entity cameraEntity, const Math::Vec2Int& screenPosition){

        Math::Vec2Int windowSize {GET_APPLICATION().getWindow().getWindowSizeInt()};
        using ECS::Components::TransformComponent;
        using ECS::Components::CameraComponent;

        TransformComponent& cameraTransform {cameraEntity.getComponent<TransformComponent>()};
        CameraComponent& cameraComp {cameraEntity.getComponent<CameraComponent>()};
        Math::Vec2 cameraPosition {cameraTransform.m_Position};
        double cameraZoom {cameraComp.m_Zoom};
        
        return static_cast<Math::Vec2>(screenPosition - windowSize / 2) / (100.0 * cameraZoom) + cameraPosition;
    }

    Math::Vec2Int worldToScreen(ECS::Entity cameraEntity, const Math::Vec2& worldPosition){
        Math::Vec2Int windowSize {GET_APPLICATION().getWindow().getWindowSizeInt()};
        using ECS::Components::TransformComponent;
        using ECS::Components::CameraComponent;

        TransformComponent& cameraTransform {cameraEntity.getComponent<TransformComponent>()};
        CameraComponent& cameraComp {cameraEntity.getComponent<CameraComponent>()};
        Math::Vec2 cameraPosition {cameraTransform.m_Position};
        double cameraZoom {cameraComp.m_Zoom};

        return static_cast<Math::Vec2Int>((worldPosition - cameraPosition) * 100 * cameraZoom) + windowSize/2;
    }
}