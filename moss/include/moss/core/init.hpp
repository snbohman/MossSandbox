#pragma once

#include <moss/includes.hpp>
#include <moss/components/components.hpp>


// Component input moss::Component
#define FILL_COMPONENT_DATA(component) { \
    #component, \
    [&registry](entt::entity entity, const json& data) { \
        registry.emplace<component>(entity, data.get<component>()); \
    } \
}

#define MAP_COMPONENT(componentMap, component) componentMap[#component] = \
    [&registry](entt::entity entity, const json& data) { \
        registry.emplace<component>(entity, data.get<component>()); \
    }

#define MAP_TAG(componentMap, component) componentMap[#component] = \
    [&registry](entt::entity entity, const json& data) { \
        registry.emplace<component>(entity); \
    }


namespace moss {

using ComponentMap = std::unordered_map<std::string, std::function<void(entt::entity, const json&)>>;

void initRaylib(const json& gameConfig);
void initEntt(const json& gameConfig, entt::registry& registry, const ComponentMap& componentMap = {0, 0});

void buildComponentMap(entt::registry& registry, ComponentMap& componentMap);


} // moss
