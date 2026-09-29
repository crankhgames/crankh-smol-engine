#include "EditorLayer.h"
#include "Core/App.h"
#include "Input/Input.h"
#include "Camera/Camera.h"

#include "UI/Text.h"
#include "UI/UiContainer.h"
#include "UI/UiManager.h"
#include "UI/Button.h"
#include "UI/UiParser.h"

#include <print>
#include <functional>
#include <format>
#include "GameLayer.h"


namespace Variables {
    //Core::UI::Text text {"Hello world", 20, "assets/fonts/Roboto-Medium.ttf", SDL_Color {255, 0, 255, SDL_ALPHA_OPAQUE}};
    std::unique_ptr<Core::UI::UiElement> document {std::make_unique<Core::UI::UiElement>()};
    Core::ECS::Entity selectedEntity{};

    constexpr bool showColliders{false};
};


void EditorLayer::onStart(){

    Variables::document->setScale(GET_APPLICATION().getWindow().getWindowSizeInt());

    std::println("Created UI tree!");
    std::filesystem::path uiConfigurations {"assets/ui/ui-editor.txt"};
    std::unique_ptr<Core::UI::UiElement> uiRoot {std::move(Core::UI::UiParser::createUiTree(uiConfigurations))};
    std::println("Created UI tree!");
    Variables::document->add(std::move(uiRoot), Core::UI::UiAnchorHorizontal::left, Core::UI::UiAnchorVertical::top);


    //Core::UI::attachUiElement<Core::UI::Text>(Variables::uiContainer.get(), Core::UI::UiAnchorPoint{},
        //"Entity Info:",
        //30,
        //"assets/fonts/Roboto-Medium.ttf"
    //);

    //Core::UI::attachUiElement<Core::UI::Text>(Variables::uiContainer.get(), Core::UI::UiAnchorPoint{},
        //"ID: NONE",
        //15,
        //"assets/fonts/Roboto-Medium.ttf"
    //);

    //Core::UI::attachUiElement<Core::UI::Text>(Variables::uiContainer.get(),Core::UI::UiAnchorPoint{},
        //"Position: NONE",
        //15,
        //"assets/fonts/Roboto-Medium.ttf"
    //);

    //Core::UI::attachUiElement<Core::UI::Text>(Variables::uiContainer.get(),Core::UI::UiAnchorPoint{},
        //"Scale: NONE",
        //15,
        //"assets/fonts/Roboto-Medium.ttf"
    //);

    //Core::UI::attachUiElement<Core::UI::Button>(Variables::uiContainer.get(),Core::UI::UiAnchorPoint{},
        //Core::Math::Vec2Int {150, 40},
        //SDL_Color {0xA0, 0xA0, 0xA0, SDL_ALPHA_OPAQUE},
        //[]{
            //std::println("Hello world!");
        //}
    //);

    //Core::UI::attachUiElement<Core::UI::Text>(Variables::uiContainer->getChild(4),Core::UI::UiAnchorPoint{Core::UI::UiAnchorHorizontal::center, Core::UI::UiAnchorVertical::center},
        //"Printing something...",
        //15,
        //"assets/fonts/Roboto-Medium.ttf"
    //);

    std::println("Editor started...");
}

bool EditorLayer::onEvent(const SDL_Event& event){
    bool clicked {false};
    switch (event.type){
    case SDL_MOUSEBUTTONDOWN:
        Core::ECS::Scene& scene {GET_APPLICATION().getLayer<GameLayer>()->getScene()};
        using namespace Core::ECS::Components;
        auto entities {scene.getAllEntitiesWith<TransformComponent>()};

        Core::Math::Vec2 worldMousePosition {Core::Camera::screenToWorld(scene.getMainCameraEntity(), Core::Input::getMousePosition())};


        for (Core::ECS::Entity entity : entities){
            TransformComponent& transform {entity.getComponent<TransformComponent>()};
            if (entity.hasComponent<ActorColliderComponent>()){
                ActorColliderComponent& actorCollider {entity.getComponent<ActorColliderComponent>()};
                Core::Math::Vec2 topLeft {transform.m_Position + actorCollider.m_Offset};
                Core::Math::Vec2 bottomRight {topLeft + actorCollider.m_Bounds};
                if (topLeft.getX() <= worldMousePosition.getX() && worldMousePosition.getX() <= bottomRight.getX() && topLeft.getY() <= worldMousePosition.getY() && worldMousePosition.getY() <= bottomRight.getY()){
                    Variables::selectedEntity = entity;
                    break;
                }
            }
            else if (entity.hasComponent<SolidColliderComponent>()){
                SolidColliderComponent& solidCollider {entity.getComponent<SolidColliderComponent>()};
                Core::Math::Vec2 topLeft {transform.m_Position + solidCollider.m_Offset};
                Core::Math::Vec2 bottomRight {topLeft + solidCollider.m_Bounds};
                if (topLeft.getX() <= worldMousePosition.getX() && worldMousePosition.getX() <= bottomRight.getX() && topLeft.getY() <= worldMousePosition.getY() && worldMousePosition.getY() <= bottomRight.getY()){
                    Variables::selectedEntity = entity;
                    break;
                }

            }
        }



        clicked = true;
        break;
    //case SDL_KEYDOWN:
        //return true;
    }

    return Variables::document->onEvent(event) || clicked;
}

void EditorLayer::onUpdate(double ts){

    using Core::ECS::Components::TransformComponent;

    //if (Variables::selectedEntity.getId() != -1){

        //dynamic_cast<Core::UI::Text*>(Variables::uiContainer->getChild(1))->setContent(std::format("ID: {}", Variables::selectedEntity.getId()));
        //TransformComponent& minEntTransform {Variables::selectedEntity.getComponent<TransformComponent>()};
        //dynamic_cast<Core::UI::Text*>(Variables::uiContainer->getChild(2))->setContent(std::format("Position: {:.3f}, {:.3f}", minEntTransform.m_Position.getX(), minEntTransform.m_Position.getY()));
        //dynamic_cast<Core::UI::Text*>(Variables::uiContainer->getChild(3))->setContent(std::format("Scale: {:.3f}, {:.3f}", minEntTransform.m_Scale.getX(), minEntTransform.m_Scale.getY()));
    //}

}

void EditorLayer::onRender(){


    using Core::ECS::Components::ActorColliderComponent;
    using Core::ECS::Components::SolidColliderComponent;
    using Core::ECS::Components::TransformComponent;
    using Core::ECS::Components::CameraComponent;

    Core::ECS::Scene& scene {GET_APPLICATION().getLayer<GameLayer>()->getScene()};
    Core::ECS::Entity mainCameraEntity {scene.getMainCameraEntity()};
    CameraComponent& camera {mainCameraEntity.getComponent<CameraComponent>()};

    
    if (Variables::showColliders){

        // Display collision boxes

        auto platformsVec {scene.getAllEntitiesWith<TransformComponent, SolidColliderComponent>()};
        auto actorsVec {scene.getAllEntitiesWith<TransformComponent, ActorColliderComponent>()};

        SDL_SetRenderDrawColor(&GET_APPLICATION().getWindow().getRenderer(), 0x00, 0xFF, 0x00, SDL_ALPHA_OPAQUE);

        std::for_each(platformsVec.begin(), platformsVec.end(),
            [&](Core::ECS::Entity entity){
                TransformComponent& platformTransform {entity.getComponent<TransformComponent>()};
                SolidColliderComponent& platformCollider {entity.getComponent<SolidColliderComponent>()};

                Core::Math::Vec2 platformScreenPosition {Core::Camera::worldToScreen(mainCameraEntity, platformTransform.m_Position + platformCollider.m_Offset)};

                SDL_Rect rect {
                    static_cast<int>(platformScreenPosition.getX()),
                    static_cast<int>(platformScreenPosition.getY()),
                    static_cast<int>(platformCollider.m_Bounds.getX() * 100 * camera.m_Zoom),
                    static_cast<int>(platformCollider.m_Bounds.getY() * 100 * camera.m_Zoom),
                };

                SDL_RenderDrawRect(&GET_APPLICATION().getWindow().getRenderer(), &rect);

            }
        );

        std::for_each(actorsVec.begin(), actorsVec.end(),
            [&](Core::ECS::Entity entity){
                TransformComponent& actorTransform {entity.getComponent<TransformComponent>()};
                ActorColliderComponent& actorCollider {entity.getComponent<ActorColliderComponent>()};

                //Core::Math::Vec2 actorScreenPosition {(actorTransform.m_Position + actorCollider.m_Offset - cameraTransform.m_Position) * 100 * camera.m_Zoom + GET_APPLICATION().getWindow().getWindowSize() / 2.0};
                Core::Math::Vec2 actorScreenPosition {Core::Camera::worldToScreen(mainCameraEntity, actorTransform.m_Position + actorCollider.m_Offset)};

                SDL_Rect rect {
                    static_cast<int>(actorScreenPosition.getX()),
                    static_cast<int>(actorScreenPosition.getY()),
                    static_cast<int>(actorCollider.m_Bounds.getX() * 100 * camera.m_Zoom),
                    static_cast<int>(actorCollider.m_Bounds.getY() * 100 * camera.m_Zoom),
                };

                SDL_RenderDrawRect(&GET_APPLICATION().getWindow().getRenderer(), &rect);

            }
        );
        
    }

    SDL_SetRenderDrawColor(&GET_APPLICATION().getWindow().getRenderer(), 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    if (Variables::selectedEntity.getId() != -1){
        if (Variables::selectedEntity.hasComponent<ActorColliderComponent>() || Variables::selectedEntity.hasComponent<SolidColliderComponent>()){

            TransformComponent& selectedTransform {Variables::selectedEntity.getComponent<TransformComponent>()};

            if (Variables::selectedEntity.hasComponent<ActorColliderComponent>()){
                ActorColliderComponent& selectedActorCollider {Variables::selectedEntity.getComponent<ActorColliderComponent>()};
                Core::Math::Vec2 screenPosition {Core::Camera::worldToScreen(mainCameraEntity, selectedTransform.m_Position + selectedActorCollider.m_Offset)};
                double zoom {mainCameraEntity.getComponent<Core::ECS::Components::CameraComponent>().m_Zoom};
                SDL_Rect rect {
                    screenPosition.getX(),
                    screenPosition.getY(),
                    selectedActorCollider.m_Bounds.getX() * 100 * zoom,
                    selectedActorCollider.m_Bounds.getY() * 100 * zoom,
                };

                SDL_RenderDrawRect(&GET_APPLICATION().getWindow().getRenderer(), &rect);
            }
            else {

                SolidColliderComponent& selectedSolidCollider {Variables::selectedEntity.getComponent<SolidColliderComponent>()};
                Core::Math::Vec2 screenPosition {Core::Camera::worldToScreen(mainCameraEntity, selectedTransform.m_Position + selectedSolidCollider.m_Offset)};
                double zoom {mainCameraEntity.getComponent<Core::ECS::Components::CameraComponent>().m_Zoom};
                SDL_Rect rect {
                    screenPosition.getX(),
                    screenPosition.getY(),
                    selectedSolidCollider.m_Bounds.getX() * 100 * zoom,
                    selectedSolidCollider.m_Bounds.getY() * 100 * zoom,
                };

                SDL_RenderDrawRect(&GET_APPLICATION().getWindow().getRenderer(), &rect);
            }

        }

    }
    //SDL_Rect rect2 {
        //700, 300, 200, 200
    //};


    //SDL_RenderFillRect(&GET_APPLICATION().getWindow().getRenderer(), &rect);
    //SDL_SetRenderDrawColor(&GET_APPLICATION().getWindow().getRenderer(), 0x50, 0x50, 0x50, 50);
    //SDL_RenderFillRect(&GET_APPLICATION().getWindow().getRenderer(), &rect2);


    Variables::document->render();
}