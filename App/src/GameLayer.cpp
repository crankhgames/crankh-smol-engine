#include "GameLayer.h"

#include "Core/App.h"
#include "Input/Input.h"
#include "Renderer/Renderer.h"
#include "Random/Random.h"
#include "ECS/Scene.h"
#include "Animation/Interpolation.h"
#include "Animation/Animation.h"

#include <iostream>
#include <print>
#include <functional>

#include "Virus.h"


namespace Variables {
    Core::ECS::Entity playerEntity {};
    constexpr double playerSpeed {3.5};
}

void GameLayer::onStart(){
    using namespace Core::ECS::Components;

    gameScene.registerComponents<TransformComponent, TagComponent, SpriteComponent, CameraComponent, AnimatorComponent, RigidbodyComponent, VirusComponent>();

    //Variables::player = &gameScene.createEntity();
    //Variables::player->addComponent<TransformComponent>(Core::Math::Vec2{0.0, 0.0}, Core::Math::Vec2{200.0, 200.0});
    //Variables::player->addComponent<SpriteComponent>("assets/sprites/mario.jpg");

    
    Core::ECS::Entity cameraEntity {gameScene.createEntity()};
    std::println("Adding component camera...");
    cameraEntity.addComponent<CameraComponent>(Core::Math::Vec2{4.0, 3.0}, 1.0, true);
    std::println("Adding component transform...");
    cameraEntity.addComponent<TransformComponent>();
    gameScene.setMainCamera();

    std::println("Creating entity...");

    Variables::playerEntity  = gameScene.createEntity();
    Variables::playerEntity.addComponent<TransformComponent>(Core::Math::Vec2{}, Core::Math::Vec2{.5, .5});
    Variables::playerEntity.addComponent<RigidbodyComponent>(Core::Math::Vec2{});
    Variables::playerEntity.addComponent<SpriteComponent>("assets/sprites/player-1.png", AnchorPoint{AnchorX::center, AnchorY::down}, Core::Math::Vec2{0.0, 0.0});
    Variables::playerEntity.addComponent<TagComponent>("player");

    Variables::playerEntity.addComponent<AnimatorComponent>(
        Core::Animation::Animator{

            std::unordered_map<std::string, Core::Animation::Animation>{
                {"Walking",
                    { 
                        std::unordered_map<int, std::function<void(Core::ECS::Entity)>>{
                            {0, [](Core::ECS::Entity entity){
                                    entity.getComponent<TransformComponent>().m_Scale.setY(.6);
                                    entity.getComponent<SpriteComponent>().loadNewTexture("assets/sprites/player-1.png");
                                }
                            },
                            {1, [](Core::ECS::Entity entity){
                                    entity.getComponent<TransformComponent>().m_Scale.setY(.5);
                                    entity.getComponent<SpriteComponent>().loadNewTexture("assets/sprites/player.png");
                                }
                            },
                            {2, [](Core::ECS::Entity entity){
                                    entity.getComponent<TransformComponent>().m_Scale.setY(.6);
                                    entity.getComponent<SpriteComponent>().loadNewTexture("assets/sprites/player-2.png");
                                }
                            },
                            {3, [](Core::ECS::Entity entity){
                                    entity.getComponent<TransformComponent>().m_Scale.setY(.5);
                                    entity.getComponent<SpriteComponent>().loadNewTexture("assets/sprites/player.png");
                                }
                            },
                        },
                        4,
                        1.0,
                        true,
                        Variables::playerEntity
                    }
                },
                {"Idle",
                    { 
                        std::unordered_map<int, std::function<void(Core::ECS::Entity)>>{
                            {0, [](Core::ECS::Entity entity){
                                    entity.getComponent<TransformComponent>().m_Scale.setY(.6);
                                    entity.getComponent<SpriteComponent>().loadNewTexture("assets/sprites/player.png");
                                }
                            },
                            {2, [](Core::ECS::Entity entity){
                                    entity.getComponent<TransformComponent>().m_Scale.setY(.45);
                                    entity.getComponent<SpriteComponent>().loadNewTexture("assets/sprites/player.png");
                                }
                            },
                        },
                        4,
                        1.0,
                        true,
                        Variables::playerEntity
                    }
                },
            },
            "Walking"

        }

    );

    std::println("Creating trojan hrose...");

    Core::ECS::Entity trojanHorse  = gameScene.createEntity();
    trojanHorse.addComponent<TransformComponent>(Core::Math::Vec2{4.0, 3.0}, Core::Math::Vec2{1.0, 1.0});
    trojanHorse.addComponent<SpriteComponent>("assets/sprites/trojan-horse.png", AnchorPoint{AnchorX::center, AnchorY::down}, Core::Math::Vec2{0.0, 0.0});
    trojanHorse.addComponent<TagComponent>("horsey");


    for (int i{}; i < 5; ++i){
        Core::ECS::Entity ent {gameScene.createEntity()};

        double size {0.5};
        Core::Math::Vec2 position {Core::Random::getRandomDouble(size - 4.0, 4.0 - size), Core::Random::getRandomDouble(size - 3.0, 3.0 - size)};

        ent.addComponent<TransformComponent>(
            position,
            Core::Math::Vec2{size, size}
        );

        ent.addComponent<SpriteComponent>("assets/sprites/virus.png", AnchorPoint {AnchorX::center, AnchorY::center}, Core::Math::Vec2{0.0, 0.0});
        ent.addComponent<TagComponent>("virus");
        ent.addComponent<VirusComponent>(
            Core::Math::Vec2{Core::Random::getRandomDouble(-3.5, 3.5), Core::Random::getRandomDouble(-3.5, 3.5)},
            Core::Math::Vec2{Core::Random::getRandomDouble(-3.5, 3.5), Core::Random::getRandomDouble(-3.5, 3.5)},
            2.0
        );
    }

    std::cout << "Entity count: " << gameScene.getEntityCount() << '\n';
}

void GameLayer::onUpdate(double ts){
    

    using namespace Core::ECS::Components;


    auto velocityVec {gameScene.getAllEntitiesWith<TransformComponent, RigidbodyComponent>()};

    std::for_each(velocityVec.begin(), velocityVec.end(), 
        [&](Core::ECS::Entity entity){
            TransformComponent& transform {entity.getComponent<TransformComponent>()};
            RigidbodyComponent& rigidbody {entity.getComponent<RigidbodyComponent>()};

            transform.m_Position += ts * rigidbody.m_Velocity;
        }
    );

    TransformComponent& playerTransform {Variables::playerEntity.getComponent<TransformComponent>()};
    RigidbodyComponent& playerRigidbody {Variables::playerEntity.getComponent<RigidbodyComponent>()};

    AnimatorComponent& animComp {Variables::playerEntity.getComponent<Core::ECS::Components::AnimatorComponent>()};

    if (playerRigidbody.m_Velocity.magnitudeSquared() < 0.001 && animComp.m_Animator.getCurrentAnimation() != "Idle"){
        animComp.m_Animator.switchAnimation("Idle");
    }
    else if (playerRigidbody.m_Velocity.magnitudeSquared() > 0.001 && animComp.m_Animator.getCurrentAnimation() != "Walking"){
        animComp.m_Animator.switchAnimation("Walking");
    }

    // Locks camera position to player

    gameScene.getMainCameraEntity().getComponent<TransformComponent>().m_Position = playerTransform.m_Position;

    auto vec {gameScene.getAllEntitiesWithTag("virus")};
    for (Core::ECS::Entity virus : vec){
        TransformComponent& virusTransform {virus.getComponent<TransformComponent>()};
        VirusComponent& virusComponent {virus.getComponent<VirusComponent>()};

        virusComponent.m_CurrentPosition.increment(ts);

        virusTransform.m_Position = virusComponent.m_CurrentPosition;

        if (virusComponent.m_CurrentPosition.hasEnded()){
            virusComponent.m_IsGoingFromStartToEnd = !virusComponent.m_IsGoingFromStartToEnd;
            if (virusComponent.m_IsGoingFromStartToEnd){
                virusComponent.m_CurrentPosition.setTarget(virusComponent.m_End);
            }
            else{
                virusComponent.m_CurrentPosition.setTarget(virusComponent.m_Start);
            }
        }
    }


    auto animationVec {gameScene.getAllEntitiesWith<AnimatorComponent>()};
    std::for_each(animationVec.begin(), animationVec.end(),
        [&](Core::ECS::Entity entity){
            AnimatorComponent& anim {entity.getComponent<AnimatorComponent>()};
            anim.m_Animator.update(ts);
        }
    );


    gameScene.updateEntitiesAndComponentsState();

}

void GameLayer::onRender(){
    


    SDL_SetRenderDrawColor(Core::Application::Get().getWindow()->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);

    SDL_RenderClear(Core::Application::Get().getWindow()->getRenderer());


    using namespace Core::ECS::Components;

    Core::ECS::Entity mainActiveCameraEntity {gameScene.getMainCameraEntity()};
    TransformComponent& cameraTransform {mainActiveCameraEntity.getComponent<TransformComponent>()};
    CameraComponent& camera {mainActiveCameraEntity.getComponent<CameraComponent>()};

    auto vec {gameScene.getAllEntitiesWith<TransformComponent, SpriteComponent>()};
    std::for_each(vec.begin(), vec.end(),
        [&](Core::ECS::Entity entity){

            SpriteComponent& entitySprite {entity.getComponent<SpriteComponent>()};
            TransformComponent& entityTransform {entity.getComponent<TransformComponent>()};
            
            //std::cout << "Entity " << entity->getId() << " position: " << entityTransform.m_Position << '\n';

            Core::Math::Vec2 destPosition {(entityTransform.m_Position - cameraTransform.m_Position) * 100 * camera.m_Zoom + GET_APPLICATION().getWindow()->getWindowSize() / 2.0};

            switch (entitySprite.m_AnchorPoint.anchorX){
            case AnchorX::left:
                break;
            case AnchorX::right:
                destPosition -= Core::Math::Vec2{entityTransform.m_Scale.getX() * entitySprite.m_SourceSize.getX() / 10.0, 0.0};
                break;
            case AnchorX::center:
                destPosition -= Core::Math::Vec2{entityTransform.m_Scale.getX() * entitySprite.m_SourceSize.getX() / 20.0, 0.0};
                break;
            }


            switch (entitySprite.m_AnchorPoint.anchorY){
            case AnchorY::top:
                break;
            case AnchorY::down:
                destPosition -= Core::Math::Vec2{0.0, entityTransform.m_Scale.getY() * entitySprite.m_SourceSize.getY() / 10.0};
                break;
            case AnchorY::center:
                destPosition -= Core::Math::Vec2{0.0, entityTransform.m_Scale.getY() * entitySprite.m_SourceSize.getY() / 20.0};
                break;
            }



            SDL_Rect entitySrcRect {static_cast<int>(entitySprite.m_SourcePos.getX()), static_cast<int>(entitySprite.m_SourcePos.getY()), static_cast<int>(entitySprite.m_SourceSize.getX()), static_cast<int>(entitySprite.m_SourceSize.getY())};
            SDL_Rect entityDestRect {static_cast<int>(destPosition.getX()), static_cast<int>(destPosition.getY()), static_cast<int>(entityTransform.m_Scale.getX() * entitySprite.m_SourceSize.getX() / 10.0), static_cast<int>(entityTransform.m_Scale.getY() * entitySprite.m_SourceSize.getY() / 10.0)};

            Core::Renderer::draw(entitySprite.m_Texture.get(), entitySrcRect, entityDestRect);

        }
    );

}

void GameLayer::onEvent(const SDL_Event& event){
    switch (event.type){
    case SDL_MOUSEBUTTONDOWN:
        onMouseClick(event);
        break;
    case SDL_KEYDOWN:
        onKeyboardPress(event);
        break;
    case SDL_KEYUP:
        onKeyboardPress(event);
    }
}

void GameLayer::onMouseClick(const SDL_Event& event){
    
    Core::Math::Vec2 mousePosition {Core::Input::getMousePosition()};
    
    std::println("Mouse position at: {}", Core::Input::getMousePosition());

    using Core::ECS::Components::TransformComponent;
    using Core::ECS::Components::SpriteComponent;

}


void GameLayer::onKeyboardPress(const SDL_Event& event){
    Core::ECS::Components::TransformComponent& playerTransform {Variables::playerEntity.getComponent<Core::ECS::Components::TransformComponent>()};

    Variables::playerEntity.getComponent<Core::ECS::Components::RigidbodyComponent>().m_Velocity = Core::Math::Vec2{
        (static_cast<double>(Core::Input::getKeyPressed(SDL_SCANCODE_D)) - static_cast<double>(Core::Input::getKeyPressed(SDL_SCANCODE_A))),
        (static_cast<double>(Core::Input::getKeyPressed(SDL_SCANCODE_S)) - static_cast<double>(Core::Input::getKeyPressed(SDL_SCANCODE_W)))
    }.normalized();


}