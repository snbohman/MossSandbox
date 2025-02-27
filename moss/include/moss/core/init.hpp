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

namespace moss {

using ComponentRegistry = std::unordered_map<std::string, std::function<void(entt::entity, const json&)>>;

template<typename T>
inline void registerComponent(entt::registry& registry, moss::ComponentRegistry& componentRegistry, const char* name) {
    componentRegistry[name] = [&registry] (entt::entity entity, const json& data) {
        registry.emplace<T>(entity, data.get<T>());
    };
}

template<typename T>
inline void registerTag(entt::registry& registry, moss::ComponentRegistry& componentRegistry, const char* name) {
    componentRegistry[name] = [&registry] (entt::entity entity, const json& data) {
        registry.emplace<T>(entity);
    };
}

void initRaylib(const json& gameConfig);
void initEntt(const json& gameConfig, entt::registry& registry, const ComponentRegistry& componentMap = {0, 0});

void buildComponentRegistry(entt::registry& registry, ComponentRegistry& componentMap);


} // moss
