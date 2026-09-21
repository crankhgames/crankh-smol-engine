#include "Scene.h"
#include "Random/Random.h"
#include "Math/Math.h"

#include <limits>
#include <iostream>
#include <print>

namespace Core::ECS{
    
    Scene::Scene():
        m_Registry{}
    {}

    Entity Scene::createEntity(){
        Entity entity {m_Registry.queryUnusedId(), this};
        m_Registry.addEntity(entity);
        return m_Registry.getEntity(entity.getId());
    }

    void Scene::destroyEntity(Entity entity){
        m_Registry.queueDestroyedEntity(entity);
    }

    void Scene::updateEntitiesAndComponentsState(){
        m_Registry.clearQueuedDestroyedEntities();
    }

    std::vector<Entity> Scene::getAllEntitiesWithTag(std::string_view tagName){
        std::vector<Entity> entityWithTags {getAllEntitiesWith<Components::TagComponent>()};
        std::vector<Entity> result {};
        
        for (Entity& ent : entityWithTags){
            if (ent.getComponent<Components::TagComponent>().m_TagName == tagName){
                result.push_back(ent);
            }
        }

        return result;
        
    }

    EntityRegistry::EntityRegistry(){
    }


    EntityId EntityRegistry::queryUnusedId(){
        EntityId result {};

        do {
            result = Core::Random::getRandomInt(0, std::numeric_limits<int>::max());
        }
        while (m_UsedIds.find(result) != m_UsedIds.end());

        m_UsedIds.insert(result);

        return result;
        
    }

    void EntityRegistry::addEntity(Entity entity){
        m_EntitiesInfo[m_CurrentEntityCount] = {entity, ComponentBitset()};
        m_EntityIdToArrayIndex.insert({entity.getId(), m_CurrentEntityCount});
        ++m_CurrentEntityCount;
        //std::println("Entity Count: {}", m_CurrentEntityCount);
    }

    Entity& EntityRegistry::getEntity(EntityId entityId) {
        return m_EntitiesInfo[m_EntityIdToArrayIndex.at(entityId)].entity;
    }

    ComponentBitset& EntityRegistry::getComponentBitset(EntityId entityId) {
        return m_EntitiesInfo[m_EntityIdToArrayIndex.at(entityId)].componentBitset;
    }
    
    void EntityRegistry::destroyEntity(Entity entity){
        
        // Need to destroy every related component of entity
        for (int componentType{}; componentType < m_CurrentComponentTypeCount; ++componentType){

            auto componentArray {m_ComponentArrays[componentType]};

            if (hasComponent(entity, componentType)){
                componentArray->destroyComponent(entity.getId());
            }

        }

        int entityIdArrayIndex {m_EntityIdToArrayIndex[entity.getId()]};
        --m_CurrentEntityCount;

        std::swap(m_EntitiesInfo[entityIdArrayIndex], m_EntitiesInfo[m_CurrentEntityCount]);

        m_EntityIdToArrayIndex[m_EntitiesInfo[entityIdArrayIndex].entity.getId()] = entityIdArrayIndex;
        m_EntityIdToArrayIndex.erase(entity.getId());
        m_UsedIds.erase(entity.getId());

        // Clears destroyed entity
        m_EntitiesInfo[m_CurrentEntityCount].entity = Entity{};
        m_EntitiesInfo[m_CurrentEntityCount].componentBitset.reset();

        std::println("Entity count: {}", m_CurrentEntityCount);

    }

    void EntityRegistry::queueDestroyedEntity(Entity entity){
        queuedDestroyedEntities.push(entity);
    }

    void EntityRegistry::clearQueuedDestroyedEntities(){
        for (; !queuedDestroyedEntities.empty(); queuedDestroyedEntities.pop()){
            destroyEntity(queuedDestroyedEntities.front());
        }
    }

}