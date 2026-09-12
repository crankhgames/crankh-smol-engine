#pragma once

#include "Math/Math.h"
#include "Renderer/Renderer.h"
#include "Animation/Animation.h"
#include "Physics/CollisionDetection.h"

#include <bitset>
#include <memory>
#include <unordered_map>
#include <functional>


namespace Core::ECS{

    using ComponentBitset = std::bitset<8>;


    inline int retrieveNewComponentTypeId(){
        static int currentComponentTypeId {};
        return currentComponentTypeId++;
    }

    #define INIT_TYPE inline static int componentTypeId {retrieveNewComponentTypeId()}

    namespace Components{



        struct TagComponent {
            std::string m_TagName{};

            TagComponent():
                m_TagName {"None"}
            {};

            TagComponent(std::string_view tagName) {
                m_TagName = tagName;
            }

            INIT_TYPE;
        };

        struct TransformComponent {

            Math::Vec2 m_Position{};
            Math::Vec2 m_Scale{};

            TransformComponent(const Math::Vec2& position = {0.0, 0.0}, const Math::Vec2& scale = {1.0, 1.0}):
                m_Position{position}, m_Scale{scale}
            {}

            TransformComponent(const TransformComponent& other):
                m_Position{other.m_Position}, m_Scale{other.m_Scale}
            {}


            
            INIT_TYPE;

        };


        enum class AnchorX {
            left = 0,
            center,
            right,
        };

        enum class AnchorY {
            top = 0,
            center,
            down,
        };

        struct AnchorPoint {
            AnchorX anchorX {};
            AnchorY anchorY {};
        };

        struct SpriteComponent {
            std::shared_ptr<SDL_Texture> m_Texture{};
            Math::Vec2 m_SourcePos{};
            Math::Vec2 m_SourceSize{};

            AnchorPoint m_AnchorPoint {};


            bool m_FlipX {};

            SpriteComponent():
                m_Texture{nullptr}, m_SourcePos{0, 0}, m_SourceSize{0,0}, m_AnchorPoint {AnchorX::left, AnchorY::top}
            {};

            SpriteComponent(std::string_view textureName, AnchorPoint anchorPoint, Math::Vec2 sourcePos, bool flipX=false):
                m_Texture{Renderer::getTexture(textureName)}, m_SourcePos{sourcePos}, m_AnchorPoint{anchorPoint}, m_FlipX {flipX}
            {
                int width{};
                int height{};
                SDL_QueryTexture(m_Texture.get(), NULL, NULL, &width, &height);
                m_SourceSize.set(width, height);
            };

            SpriteComponent(std::string_view textureName, AnchorPoint anchorPoint, Math::Vec2 sourcePos, Math::Vec2 sourceSize, bool flipX=false):
                m_Texture{Renderer::getTexture(textureName)}, m_SourcePos{sourcePos}, m_SourceSize{sourceSize}, m_AnchorPoint{anchorPoint}, m_FlipX {flipX}
            {};
            
            void loadNewTexture(std::string_view textureName){
                m_Texture = Renderer::getTexture(textureName);
            }

            INIT_TYPE;
        };


        struct CameraComponent {
        
            Math::Vec2 m_AspectRatio{};
            double m_Zoom{1.0};

            bool m_IsMainCamera{false};

            CameraComponent():
                m_AspectRatio{16.0, 9.0}, m_Zoom{1.0}, m_IsMainCamera{false}
            {}

            CameraComponent(const Math::Vec2& aspectRatio, double zoom, bool isMainCamera = false):
                m_AspectRatio{aspectRatio}, m_Zoom{zoom}, m_IsMainCamera{isMainCamera}
            {}

            CameraComponent(const CameraComponent& other):
                m_AspectRatio{other.m_AspectRatio}, m_Zoom{other.m_Zoom}, m_IsMainCamera{false}
            {}
            
            INIT_TYPE;
        };


        struct AnimatorComponent {
            Animation::Animator m_Animator{};
            
            AnimatorComponent():
                m_Animator{}
            {}

            AnimatorComponent(const Core::Animation::Animator& animator):
                m_Animator{animator}
            {}

            INIT_TYPE;
        };

        struct RigidbodyComponent{
            Math::Vec2 m_Velocity {};

            RigidbodyComponent():
                m_Velocity{}
            {}

            RigidbodyComponent(const Math::Vec2& velocity):
                m_Velocity {velocity}
            {}

            INIT_TYPE;
        };

        struct ActorColliderComponent {
            Math::Vec2 m_Bounds {};
            Math::Vec2 m_Offset {};
            
            ActorColliderComponent():
                m_Bounds{}
            {}

            ActorColliderComponent(const Math::Vec2& bounds, const Math::Vec2& offset):
                m_Bounds{bounds}, m_Offset{offset}
            {}

            INIT_TYPE;
        };

        struct SolidColliderComponent{
            Math::Vec2 m_Bounds {};
            Math::Vec2 m_Offset {};

            SolidColliderComponent():
                m_Bounds{}
            {}

            SolidColliderComponent(const Math::Vec2& bounds, const Math::Vec2& offset):
                m_Bounds{bounds}, m_Offset{offset}
            {}

            INIT_TYPE;
        };

    }

}

