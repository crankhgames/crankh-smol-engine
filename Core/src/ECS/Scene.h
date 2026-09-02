#pragma once

#include <algorithm>
#include <array>
#include <vector>
#include <unordered_map>
#include <set>
#include <bitset>
#include <queue>
#include <string_view>

#include "Components.h"
#include "Entity.h"


namespace Core::ECS
{

    using EntityId = int;
    using ComponentBitset = std::bitset<8>;


    namespace {
        constexpr int maxEntityCount {500};
        constexpr int maxComponentCount {32};

    }

    template <typename T>
    constexpr int getComponentType() {
        return T::componentTypeId;
    }

    template <typename... Components>
    ComponentBitset getComponentSignature(){
        ComponentBitset bitset{};
        (bitset.set(static_cast<size_t>(getComponentType<Components>()), true), ...);
        return bitset;
    }

    class IComponentArray{
    public:
        virtual void destroyComponent(EntityId entityId) = 0;

        IComponentArray() = default;
        ~IComponentArray() = default;
    };

    template <typename T>
    class ComponentArray : public IComponentArray{
    private:
        std::array<T, 500> m_ComponentArray {};
        std::array<EntityId, 500> m_EntityIds {};
        std::unordered_map<EntityId, int> m_EntityIdToArrayIndex {};

        int currentComponentCount{0};

    public:

        //T& addComponent(const Entity& entity, T&& component){
            //m_ComponentArray[currentComponentCount] = std::move(component);
            //m_EntityIds[currentComponentCount] = entity.getId();
            //return m_ComponentArray[currentComponentCount++];
        //}
        

        T& addComponent(EntityId entityId, const T& component){
            m_ComponentArray[currentComponentCount] = component;
            m_EntityIds[currentComponentCount] = entityId;
            m_EntityIdToArrayIndex[entityId] = currentComponentCount;
            return m_ComponentArray[currentComponentCount++];
        }


        T& getComponent(EntityId entityId){
            return m_ComponentArray[m_EntityIdToArrayIndex[entityId]];
        }

        void destroyComponent(EntityId entityId) override{

            int entityArrayIndex {m_EntityIdToArrayIndex[entityId]};
            --currentComponentCount;

            // Swap last component and to be destroyed component
            std::swap(m_ComponentArray[currentComponentCount], m_ComponentArray[entityArrayIndex]);
            

            // Update entityId
            m_EntityIds[entityArrayIndex] = m_EntityIds[currentComponentCount];

            m_EntityIdToArrayIndex[m_EntityIds[entityArrayIndex]] = entityArrayIndex;
            m_EntityIdToArrayIndex.erase(entityId);

            // Clears destroyed component
            m_ComponentArray[currentComponentCount] = T{};
        }
    };



    struct EntityInfo {
        Entity entity {};
        ComponentBitset componentBitset{};
    };


    class EntityRegistry{
    private:
        //std::array<Entity, maxEntityCount> m_Entities {};
        //std::array<ComponentBitset, maxEntityCount> m_ComponentBitsets {};

        std::array<EntityInfo, maxEntityCount> m_EntitiesInfo {};

        std::unordered_map<EntityId, int> m_EntityIdToArrayIndex {};

        std::set<EntityId> m_UsedIds {};
        
        int m_CurrentEntityCount{0};
        int m_CurrentComponentTypeCount{0};

        std::array<std::shared_ptr<IComponentArray>, maxComponentCount> m_ComponentArrays{};

        
        std::queue<Entity> queuedDestroyedEntities{};

    private:

        template <typename T>
        std::shared_ptr<ComponentArray<T>> getComponentArray(){
            return static_pointer_cast<ComponentArray<T>>(m_ComponentArrays[getComponentType<T>()]);
        }



    public:

        EntityRegistry();

        template <typename T>
        void registerComponent(){
            std::cout << "Registering component " << typeid(T).name() << '\n';
            m_ComponentArrays[getComponentType<T>()] = std::make_shared<ComponentArray<T>>();
            ++m_CurrentComponentTypeCount;
        }

        EntityId queryUnusedId();

        void addEntity(Entity entity);
        Entity& getEntity(EntityId entityId);
        ComponentBitset& getComponentBitset(EntityId entityId);
        void destroyEntity(Entity entity);

        void queueDestroyedEntity(Entity entity);
        
        template <typename T>
        T& addComponent(Entity entity, const T& component){
            getComponentBitset(entity.getId()).set(getComponentType<T>(), true);
            return getComponentArray<T>()->addComponent(entity.getId(), component);
        }

        //template <typename T>
        //T& addComponent(const Entity& entity, T&& component){
            //entity.m_ComponentBitset.set(static_cast<size_t>(getComponentType<T>()), true);
            //return getComponentArray<T>()->addComponent(entity, std::move(component));
        //}

        template <typename T>
        T& getComponent(Entity entity){
            return getComponentArray<T>()->getComponent(entity.getId());
        }

        template <typename T>
        void destroyComponent(Entity entity){
            getComponentBitset(entity.getId()).set(getComponentType<T>(), false);
            getComponentArray<T>()->destroyComponent(entity.getId());
        }

        constexpr bool hasComponent(Entity entity, int componentType) {
            return getComponentBitset(entity.getId()).test(componentType);
        }

        template <typename T>
        constexpr bool hasComponent(Entity entity) {
            return getComponentBitset(entity.getId()).test(getComponentType<T>());
        }


        template <typename... Components>
        std::vector<Entity> getAllEntitiesWith(){
            std::vector<Entity> entities {};
            ComponentBitset signature {getComponentSignature<Components...>()};

            
            for (int entityIndex{}; entityIndex < m_CurrentEntityCount; ++entityIndex){
                Entity entity {m_EntitiesInfo[entityIndex].entity};
                if ((getComponentBitset(entity.getId()) & signature) == signature) {
                    entities.push_back(entity);
                }
            }

            return entities;
        }

        void clearQueuedDestroyedEntities();

        int getEntityCount() const {return m_CurrentEntityCount;}

    };

    class Scene{
    private:
        EntityRegistry m_Registry{};

        Entity mainCameraEntity{};
        

    public:
        Scene();


        template <typename... T>
        void registerComponents(){
            (m_Registry.registerComponent<T>(), ...);
        }

        Entity createEntity();
        void destroyEntity(Entity entity);

        void updateEntitiesAndComponentsState();

        template <typename T>
        void onComponentAdded(Entity entity, const T& component){
            m_Registry.addComponent<T>(entity, component);
        }

        //template <typename T>
        //void onComponentAdded(const Entity& entity, T&& component){
            //m_Registry.addComponent<T>(entity, std::move(component));
        //}

        template <typename T>
        T& getComponent(Entity entity){
            return m_Registry.getComponent<T>(entity);
        }

        template <typename T>
        void onComponentDestroyed(Entity entity){
            m_Registry.destroyComponent<T>(entity);
        }

        constexpr bool hasComponent(Entity entity, int componentType) {
            return m_Registry.hasComponent(entity, componentType);
        }

        template <typename T>
        constexpr bool hasComponent(Entity entity) const{
            return m_Registry.hasComponent<T>(entity);
        }

        template <typename... Components>
        std::vector<Entity> getAllEntitiesWith(){
            return m_Registry.getAllEntitiesWith<Components...>();
        }

        std::vector<Entity> getAllEntitiesWithTag(std::string_view tagName);


        void setMainCamera(){
            std::vector<Entity> cameraEntities {getAllEntitiesWith<Components::CameraComponent>()};

            for (Entity cameraEntity : cameraEntities){
                Components::CameraComponent& camera {cameraEntity.getComponent<Components::CameraComponent>()};
                if (camera.m_IsMainCamera){
                    mainCameraEntity = cameraEntity;
                    return;
                }
            }
        }

        Entity getMainCameraEntity() {
            return mainCameraEntity;
        }

        int getEntityCount() const {
            return m_Registry.getEntityCount();
        }
    };
}
