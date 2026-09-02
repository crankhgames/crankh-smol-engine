#pragma once
    
#include <bitset>

namespace Core::ECS {

    using EntityId = int;
    using ComponentBitset = std::bitset<8>;

    class Scene;
    

    class Entity{
    private:
        EntityId m_Id{};

        Scene* m_Scene {nullptr};


    public:
        Entity():
            m_Id{-1}, m_Scene{nullptr}
        {};

        Entity(Scene* scene):
            m_Id{-1}, m_Scene{scene}
        {};

        Entity(EntityId id, Scene* scene):
            m_Id{id}, m_Scene{scene}
        {};

        EntityId getId() const {return m_Id;}
        
        template <typename T>
        void addComponent(const T& component){
            m_Scene->template onComponentAdded<T>(*this, component);
        }

        //template <typename T>
        //void addComponent(T&& component){
            //m_Scene->onComponentAdded<T>(*this, std::move(component));
        //}

        template <typename T, typename... Args>
        void addComponent(Args&&... args){
            m_Scene->template onComponentAdded<T>(*this, T{std::forward<Args>(args)...});
        }

        template <typename T>
        T& getComponent() const {
            return m_Scene->template getComponent<T>(*this);
        }

        template <typename T>
        void destroyComponent() {
            m_Scene->template onComponentDestroyed<T>(*this);
        }

        template <typename T>
        constexpr bool hasComponent() const {
            return m_Scene->template hasComponent<T>(*this);
        }



        friend class EntityRegistry;
    };

}