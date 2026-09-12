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
    constexpr double playerJumpForce {4.0};
}

void GameLayer::onStart(){
    using namespace Core::ECS::Components;

    gameScene.registerComponents<TransformComponent, TagComponent, SpriteComponent, CameraComponent, AnimatorComponent, RigidbodyComponent, ActorColliderComponent, SolidColliderComponent, VirusComponent>();

    //Variables::player = &gameScene.createEntity();
    //Variables::player->addComponent<TransformComponent>(Core::Math::Vec2{0.0, 0.0}, Core::Math::Vec2{200.0, 200.0});
    //Variables::player->addComponent<SpriteComponent>("assets/sprites/mario.jpg");

    
    Core::ECS::Entity cameraEntity {gameScene.createEntity()};
    cameraEntity.addComponent<CameraComponent>(Core::Math::Vec2{4.0, 3.0}, 1.0, true);
    cameraEntity.addComponent<TransformComponent>();
    gameScene.setMainCamera();

    std::println("Creating entity...");

    Variables::playerEntity  = gameScene.createEntity();
    Variables::playerEntity.addComponent<TransformComponent>(Core::Math::Vec2{}, Core::Math::Vec2{30.0, 30.0});
    Variables::playerEntity.addComponent<RigidbodyComponent>(Core::Math::Vec2{});
    Variables::playerEntity.addComponent<SpriteComponent>("assets/sprites/idle/f-01.png", AnchorPoint{AnchorX::center, AnchorY::down}, Core::Math::Vec2{0.0, 0.0});
    Variables::playerEntity.addComponent<TagComponent>("player");

    Variables::playerEntity.addComponent<AnimatorComponent>(
        Core::Animation::Animator{

            std::unordered_map<std::string, Core::Animation::Animation>{
                {"Walking",
                    { 
                        std::unordered_map<int, std::function<void(Core::ECS::Entity)>>{
                            {0, [](Core::ECS::Entity entity){
                                    entity.getComponent<SpriteComponent>().loadNewTexture("assets/sprites/run/f-01.png");
                                }
                            },
                            {1, [](Core::ECS::Entity entity){
                                    entity.getComponent<SpriteComponent>().loadNewTexture("assets/sprites/run/f-02.png");
                                }
                            },
                            {2, [](Core::ECS::Entity entity){
                                    entity.getComponent<SpriteComponent>().loadNewTexture("assets/sprites/run/f-03.png");
                                }
                            },
                            {3, [](Core::ECS::Entity entity){
                                    entity.getComponent<SpriteComponent>().loadNewTexture("assets/sprites/run/f-04.png");
                                }
                            },
                            {4, [](Core::ECS::Entity entity){
                                    entity.getComponent<SpriteComponent>().loadNewTexture("assets/sprites/run/f-05.png");
                                }
                            },
                            {5, [](Core::ECS::Entity entity){
                                    entity.getComponent<SpriteComponent>().loadNewTexture("assets/sprites/run/f-06.png");
                                }
                            }
                        },
                        6,
                        1.0,
                        true,
                        Variables::playerEntity
                    }
                },
                {"Idle",
                    { 
                        std::unordered_map<int, std::function<void(Core::ECS::Entity)>>{
                            {0, [](Core::ECS::Entity entity){
                                    entity.getComponent<SpriteComponent>().loadNewTexture("assets/sprites/idle/f-01.png");
                                }
                            },
                            {1, [](Core::ECS::Entity entity){
                                    entity.getComponent<SpriteComponent>().loadNewTexture("assets/sprites/idle/f-02.png");
                                }
                            },
                            {2, [](Core::ECS::Entity entity){
                                    entity.getComponent<SpriteComponent>().loadNewTexture("assets/sprites/idle/f-03.png");
                                }
                            },
                            {3, [](Core::ECS::Entity entity){
                                    entity.getComponent<SpriteComponent>().loadNewTexture("assets/sprites/idle/f-04.png");
                                }
                            },
                        },
                        4,
                        1.0,
                        true,
                        Variables::playerEntity
                    }
                },
                {"Jumping",
                    { 
                        std::unordered_map<int, std::function<void(Core::ECS::Entity)>>{
                            {0, [](Core::ECS::Entity entity){
                                    entity.getComponent<SpriteComponent>().loadNewTexture("assets/sprites/jump/f-01.png");
                                    if (entity.getComponent<RigidbodyComponent>().m_Velocity.getY() >= 0){
                                        entity.getComponent<AnimatorComponent>().m_Animator.switchAnimation("Falling");
                                    }
                                }
                            },
                        },
                        1,
                        0.1,
                        true,
                        Variables::playerEntity
                    }
                },
                {"Falling",
                    { 
                        std::unordered_map<int, std::function<void(Core::ECS::Entity)>>{
                            {0, [](Core::ECS::Entity entity){
                                    entity.getComponent<SpriteComponent>().loadNewTexture("assets/sprites/jump/f-02.png");
                                }
                            },
                            {1, [](Core::ECS::Entity entity){
                                    entity.getComponent<AnimatorComponent>().m_Animator.switchAnimation("Idle");
                                }
                            },
                        },
                        2,
                        1.0,
                        false,
                        Variables::playerEntity
                    }
                },
            },
            //std::unordered_map<std::string, std::vector<std::pair<std::function<bool()>, std::string>>> { {
                    //"Walk",
                    //{
                        //{
                            //"Idle",
                            //[&]
                        //}
                    //}
                //}
            //},
            "Idle"

        }

    );

    Variables::playerEntity.addComponent<ActorColliderComponent>(Core::Math::Vec2{0.5, 0.6}, Core::Math::Vec2{-.3, -0.6});

    
    Core::ECS::Entity platformEntity {gameScene.createEntity()};
    platformEntity.addComponent<TransformComponent>(Core::Math::Vec2{-1.0, 1.5});
    platformEntity.addComponent<SolidColliderComponent>(Core::Math::Vec2{5.0, 0.5}, Core::Math::Vec2{});

    Core::ECS::Entity floorEntity {gameScene.createEntity()};
    floorEntity.addComponent<TransformComponent>(Core::Math::Vec2{-4.0, 2.0});
    floorEntity.addComponent<SolidColliderComponent>(Core::Math::Vec2{10.0, 1.0}, Core::Math::Vec2{});

    Core::ECS::Entity platformEntity1 {gameScene.createEntity()};
    platformEntity1.addComponent<TransformComponent>(Core::Math::Vec2{-4.0, -2.0});
    platformEntity1.addComponent<SolidColliderComponent>(Core::Math::Vec2{3.0, 0.5}, Core::Math::Vec2{});

    Core::ECS::Entity platformEntity2 {gameScene.createEntity()};
    platformEntity2.addComponent<TransformComponent>(Core::Math::Vec2{3.0, -1.0});
    platformEntity2.addComponent<SolidColliderComponent>(Core::Math::Vec2{3.0, 0.5}, Core::Math::Vec2{});

    Core::ECS::Entity platformEntity3 {gameScene.createEntity()};
    platformEntity3.addComponent<TransformComponent>(Core::Math::Vec2{2.0, -0.1});
    platformEntity3.addComponent<SolidColliderComponent>(Core::Math::Vec2{0.5, 0.5}, Core::Math::Vec2{});

    Core::ECS::Entity platformEntity4 {gameScene.createEntity()};
    platformEntity4.addComponent<TransformComponent>(Core::Math::Vec2{1.5, 0.4});
    platformEntity4.addComponent<SolidColliderComponent>(Core::Math::Vec2{0.5, 0.5}, Core::Math::Vec2{});

    Core::ECS::Entity platformEntity5 {gameScene.createEntity()};
    platformEntity5.addComponent<TransformComponent>(Core::Math::Vec2{0.5, -2.0});
    platformEntity5.addComponent<SolidColliderComponent>(Core::Math::Vec2{0.5, 0.5}, Core::Math::Vec2{});

    std::cout << "Entity count: " << gameScene.getEntityCount() << '\n';
}

bool hasLanded {false};

bool isColliding(Core::Math::Vec2 topLeftA, Core::Math::Vec2 bottomRightA, Core::Math::Vec2 topLeftB, Core::Math::Vec2 bottomRightB){
    return (bottomRightA.getX() >= topLeftB.getX()) && (bottomRightB.getX() >= topLeftA.getX()) && (bottomRightA.getY() >= topLeftB.getY()) && (bottomRightB.getY() >= topLeftA.getY());
}

bool isOverlapping(Core::Math::Vec2 point, Core::Math::Vec2 topLeft, Core::Math::Vec2 bottomRight){
    return (topLeft.getX() < point.getX() && point.getX() < bottomRight.getX()) && (topLeft.getY() < point.getY() && point.getY() < bottomRight.getY());
}


void GameLayer::onUpdate(double ts){
    

    using namespace Core::ECS::Components;

    auto velocityVec {gameScene.getAllEntitiesWith<TransformComponent, RigidbodyComponent>()};

    std::for_each(velocityVec.begin(), velocityVec.end(), 
        [&](Core::ECS::Entity entity){
            TransformComponent& transform {entity.getComponent<TransformComponent>()};
            RigidbodyComponent& rigidbody {entity.getComponent<RigidbodyComponent>()};

            Core::Math::Vec2 acceleration {};
            if (entity.getComponent<TagComponent>().m_TagName == "player"){
                if (rigidbody.m_Velocity.getY() < 0){
                    acceleration.setY(7);
                }
                else{
                    acceleration.setY(12);
                }
            }

            rigidbody.m_Velocity += ts * acceleration;

            transform.m_Position += ts * rigidbody.m_Velocity;

        }
    );

    TransformComponent& playerTransform {Variables::playerEntity.getComponent<TransformComponent>()};
    RigidbodyComponent& playerRigidbody {Variables::playerEntity.getComponent<RigidbodyComponent>()};
    SpriteComponent& playerSprite {Variables::playerEntity.getComponent<SpriteComponent>()};


    AnimatorComponent& animComp {Variables::playerEntity.getComponent<Core::ECS::Components::AnimatorComponent>()};

    if (playerRigidbody.m_Velocity.magnitudeSquared() < 0.001 && animComp.m_Animator.getCurrentAnimation() != "Idle" && hasLanded){
        animComp.m_Animator.switchAnimation("Idle");
    }
    else if (playerRigidbody.m_Velocity.magnitudeSquared() > 0.001 && animComp.m_Animator.getCurrentAnimation() != "Walking" && hasLanded){
        animComp.m_Animator.switchAnimation("Walking");
    }
        
    if (playerRigidbody.m_Velocity.magnitudeSquared() > 0.001){
        playerSprite.m_FlipX = playerRigidbody.m_Velocity.getX() < 0;
    }

    // Locks camera position to player
    //gameScene.getMainCameraEntity().getComponent<TransformComponent>().m_Position = playerTransform.m_Position;

    auto actorColliders {gameScene.getAllEntitiesWith<ActorColliderComponent>()};
    auto solidColliders {gameScene.getAllEntitiesWith<SolidColliderComponent>()};

    for (Core::ECS::Entity actorEntity : actorColliders) {

        TransformComponent& actorTransform {actorEntity.getComponent<TransformComponent>()};
        ActorColliderComponent& actorCollider {actorEntity.getComponent<ActorColliderComponent>()};

        Core::Math::Vec2 actorTopLeft {actorTransform.m_Position + actorCollider.m_Offset};
        Core::Math::Vec2 actorBottomRight {actorTopLeft + actorCollider.m_Bounds};

        Core::Math::Vec2 actorCenter {(actorTopLeft + actorBottomRight) / 2.0};

        for (Core::ECS::Entity solidEntity : solidColliders){
            
            TransformComponent& solidTransform {solidEntity.getComponent<TransformComponent>()};
            SolidColliderComponent& solidCollider {solidEntity.getComponent<SolidColliderComponent>()};

            Core::Math::Vec2 solidTopLeft {solidTransform.m_Position + solidCollider.m_Offset};
            Core::Math::Vec2 solidBottomRight {solidTopLeft + solidCollider.m_Bounds};


            if (!isColliding(actorTopLeft, actorBottomRight, solidTopLeft, solidBottomRight)){
                continue;
            }

            Core::Math::Vec2 intersectionAreaDimensions {};
            
            double interX1 {std::max(actorTopLeft.getX(), solidTopLeft.getX())};
            double interX2 {std::min(actorBottomRight.getX(), solidBottomRight.getX())};
            double interY1 {std::max(actorTopLeft.getY(), solidTopLeft.getY())};
            double interY2 {std::min(actorBottomRight.getY(), solidBottomRight.getY())};

            intersectionAreaDimensions.set(interX2 - interX1, interY2 - interY1);

            if (intersectionAreaDimensions.getX() < intersectionAreaDimensions.getY()){
                if ((actorBottomRight.getX() - interX2) < 1e-6){
                    actorTransform.m_Position -= Core::Math::Vec2{actorBottomRight.getX() - interX1, 0.0};
                }
                else{
                    actorTransform.m_Position -= Core::Math::Vec2{actorTopLeft.getX() - interX2, 0.0};
                }
            }
            else{
                if ((actorBottomRight.getY() - interY2) < 1e-6){
                    actorTransform.m_Position -= Core::Math::Vec2{0.0, actorBottomRight.getY() - interY1};
                    hasLanded = true;
                    if (actorEntity.hasComponent<RigidbodyComponent>()){
                        actorEntity.getComponent<RigidbodyComponent>().m_Velocity.setY(0);
                    }
                }
                else{
                    actorTransform.m_Position -= Core::Math::Vec2{0.0, actorTopLeft.getY() - interY2};
                }
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
    


    SDL_SetRenderDrawColor(GET_APPLICATION().getWindow()->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);

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
            SDL_Rect entityDestRect {static_cast<int>(destPosition.getX()), static_cast<int>(destPosition.getY()), static_cast<int>(entityTransform.m_Scale.getX() * entitySprite.m_SourceSize.getX() * camera.m_Zoom / 10.0), static_cast<int>(entityTransform.m_Scale.getY() * entitySprite.m_SourceSize.getY() * camera.m_Zoom / 10.0)};


            Core::Renderer::draw(entitySprite.m_Texture.get(), entitySrcRect, entityDestRect, entitySprite.m_FlipX, false);

        }
    );

    SDL_SetRenderDrawColor(GET_APPLICATION().getWindow()->getRenderer(), 0xFF, 0, 0, SDL_ALPHA_OPAQUE);

    auto platformsVec {gameScene.getAllEntitiesWith<TransformComponent, SolidColliderComponent>()};
    auto actorsVec {gameScene.getAllEntitiesWith<TransformComponent, ActorColliderComponent>()};
    std::for_each(platformsVec.begin(), platformsVec.end(),
        [&](Core::ECS::Entity entity){
            TransformComponent& platformTransform {entity.getComponent<TransformComponent>()};
            SolidColliderComponent& platformCollider {entity.getComponent<SolidColliderComponent>()};

            Core::Math::Vec2 platformScreenPosition {(platformTransform.m_Position + platformCollider.m_Offset - cameraTransform.m_Position) * 100 * camera.m_Zoom + GET_APPLICATION().getWindow()->getWindowSize() / 2.0};

            SDL_Rect rect {
                platformScreenPosition.getX(),
                platformScreenPosition.getY(),
                platformCollider.m_Bounds.getX() * 100 * camera.m_Zoom,
                platformCollider.m_Bounds.getY() * 100 * camera.m_Zoom,
            };

            SDL_RenderFillRect(GET_APPLICATION().getWindow()->getRenderer(), &rect);

        }
    );

    //std::for_each(actorsVec.begin(), actorsVec.end(),
        //[&](Core::ECS::Entity entity){
            //TransformComponent& actorTransform {entity.getComponent<TransformComponent>()};
            //ActorColliderComponent& actorCollider {entity.getComponent<ActorColliderComponent>()};

            //Core::Math::Vec2 actorScreenPosition {(actorTransform.m_Position + actorCollider.m_Offset - cameraTransform.m_Position) * 100 * camera.m_Zoom + GET_APPLICATION().getWindow()->getWindowSize() / 2.0};

            //SDL_Rect rect {
                //actorScreenPosition.getX(),
                //actorScreenPosition.getY(),
                //actorCollider.m_Bounds.getX() * 100 * camera.m_Zoom,
                //actorCollider.m_Bounds.getY() * 100 * camera.m_Zoom,
            //};

            //SDL_RenderDrawRect(GET_APPLICATION().getWindow()->getRenderer(), &rect);

        //}
    //);

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

    auto& rigidbody = Variables::playerEntity.getComponent<Core::ECS::Components::RigidbodyComponent>();

    rigidbody.m_Velocity = Core::Math::Vec2{
        (static_cast<double>(Core::Input::getKeyPressed(SDL_SCANCODE_D)) - static_cast<double>(Core::Input::getKeyPressed(SDL_SCANCODE_A))) * Variables::playerSpeed,
        rigidbody.m_Velocity.getY()
        //(static_cast<double>(Core::Input::getKeyPressed(SDL_SCANCODE_S)) - static_cast<double>(Core::Input::getKeyPressed(SDL_SCANCODE_W)))
    };



    if (Core::Input::getKeyPressed(SDL_SCANCODE_SPACE) and hasLanded){
        rigidbody.m_Velocity.setY(-Variables::playerJumpForce);
        hasLanded = false;
        Variables::playerEntity.getComponent<Core::ECS::Components::AnimatorComponent>().m_Animator.switchAnimation("Jumping");
    }


}