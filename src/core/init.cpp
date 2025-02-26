#include <includes.hpp>
#include <core/init.hpp>
#include <components/components.hpp>
#include <components/tags.hpp>
#include <components/loadComponents.hpp>
#include <fstream>


void init(entt::registry& registry) {
    json gameConfig = json::parse(std::ifstream("data/gameConfig.json"));
    initRaylib(gameConfig);
    initEntt(gameConfig, registry);
}

void initRaylib(const json& gameConfig) {
    raylib::SetTraceLogLevel(raylib::LOG_WARNING);
    raylib::InitWindow(
        gameConfig["core"]["windowDimensions"][0].get<glm::u16>(),
        gameConfig["core"]["windowDimensions"][1].get<glm::u16>(),
        gameConfig["core"]["title"].get<std::string>().c_str()
    );
    raylib::SetTargetFPS(gameConfig["core"]["targetFPS"].get<glm::u16>());
}

void initEntt(const json& gameConfig, entt::registry& registry) {
    for (const auto& [eName, components] : gameConfig["entities"].items()) {
        entt::entity entity = registry.create();

        if (eName == "Ball") { registry.emplace<BallTag>(entity); }
        if (eName == "Hex") { registry.emplace<HexTag>(entity); }

        for (const auto& [cName, cData] : components.items()) {
            if (cName == "RectTransform") {
                RectTransform transform;
                loadComponent(cData, transform);
                registry.emplace<RectTransform>(entity, transform);
            } else if (cName == "CircleTransform") {
                CircleTransform transform;
                loadComponent(cData, transform);
                registry.emplace<CircleTransform>(entity, transform);
            } else if (cName == "PolyTransform") {
                PolyTransform transform;
                loadComponent(cData, transform);
                registry.emplace<PolyTransform>(entity, transform);
            } else if (cName == "RegPolyTransform") {
                RegPolyTransform transform;
                loadComponent(cData, transform);
                registry.emplace<RegPolyTransform>(entity, transform);
            } else if (cName == "Physics") {
                Physics physics;
                loadComponent(cData, physics);
                registry.emplace<Physics>(entity, physics);
            } else if (cName == "Material") {
                Material material;
                loadComponent(cData, material);
                registry.emplace<Material>(entity, material);
            } else if (cName == "RotationDevice") {
                RotationDevice material;
                loadComponent(cData, material);
                registry.emplace<RotationDevice>(entity, material);
            }
        }
    }
}
